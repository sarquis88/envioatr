#include "../include/receiver.h"

using namespace std;

int 
main()
{
    bool keep;

    keep = false;

    do 
    {
        /* Varbiales declaration */
        string buffer_A, buffer_B;
        int size, code;

        /* Getting last sender ip */
        get_last_sender_address( &buffer_A );
        
        /* Search of sender */
        cout << "Sender's IP:" << "(enter 'd' for " << buffer_A << ")" << endl;
        do
        {
            user_input( &buffer_B );
            if( buffer_B.at(0) == 'd' )
            {
                buffer_B = buffer_A;
                break;
            }
        } while( !validate_address( &buffer_B ) );

        set_last_sender_address( &buffer_B );

        cout << "Looking for sender..." << endl;
        code = connect_to_sender( buffer_B );
        if( code == FAILURE )
            return FAILURE;
        else if( code == TIMEOUT )
        {
            timeout_routine();
            return SUCCES;
        }
        code = receive_message_from_sender( &buffer_A );
        if( code == FAILURE )
            return FAILURE;
        cout << "Sender founded" << endl;

        /* Reception of file metadata */
        cout << "Receiving metadata..." << endl;
        code = receive_message_from_sender( &buffer_A );    // file name reception
        if( code != SUCCES )
            return code;
        send_ack_to_sender();
        code = receive_message_from_sender( &buffer_B );    // file size reception
        if( code != SUCCES )
            return code;
        send_ack_to_sender();
        cout << "Metadata received" << endl;

        /* Confirmation of reception */
        size = stoi( buffer_B );
        cout << "Donwload file " << '"' << buffer_A << '"' << " (" << 
                get_size_message( size ) << ")?[y/n]" << endl;
        while( true ) 
        {
            user_input( &buffer_B );
            if( buffer_B[0] == 'n' )
            {
                buffer_B = string( 1, NEGATIVE_MSG );
                send_message_to_sender( &buffer_B );
            }
            else if( buffer_B[0] == 'y' )
            {
                /* Reception of file */
                buffer_B = string( 1, POSITIVE_MSG );
                send_message_to_sender( &buffer_B );
                cout << "Receiving " << '"' << buffer_A << '"' << " from sender..." << endl;
                code = receive_file_from_sender( &buffer_A, size );
                if( code != SUCCES )
                {
                    if( code == INTERRUPTION )
                        delete_corrupt_file( &buffer_A );
                    return code;
                }
                else
                {
                    cout << "File received" << endl;
                }
            }
            break;
        }

        /* Ask for continuing */
        while( true )
        {
            cout << endl << "Do you want to receive more files?[y/n]" << endl;
            user_input( &buffer_A );
            if( buffer_A[0] == 'y' )
            {
                keep = true;
                break;
            }
            else if( buffer_A[0] == 'n' )
            {
                keep = false;
                break;
            }
        }
    } while( keep );

    /* End of receiver program */
    close_receiver_connection();
    
    return SUCCES;
}

string
get_size_message( int size )
{
    string message;

    if( size < 1024 )
        message = to_string( ( size ) ) + "[b]";
    else if( size < BYTES_IN_MEGA )
        message = to_string( (double) size / BYTES_IN_KILO ) + "[Kb]";
    else if ( size < BYTES_IN_GIGA )
        message = to_string( (double) size / BYTES_IN_MEGA ) + "[Mb]";
    else
        message = to_string( (double) size / BYTES_IN_GIGA ) + "[Gb]";

    return message;
}

int 
set_last_sender_address( string * address )
{
    ofstream file;
    
    file.open( LAST_SENDER_ADDRESS_FILE );
    file << *address << endl;
    file.close();

    return SUCCES;
}

int 
get_last_sender_address( string * buffer )
{
    ifstream file;
    char *aux;

    aux = (char*)malloc( BUFFER_SIZE * sizeof(char) );
    
    file.open( LAST_SENDER_ADDRESS_FILE );
    file >> aux;
    file.close();

    *buffer = string( aux );

    free( aux );
    return SUCCES;
}

void
delete_corrupt_file( string * path )
{   
    string file = "./receptions/" + *path;
    filesystem::remove( file );
}