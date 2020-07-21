#include "../include/receiver.h"

using namespace std;

// TODO: aceptar archiv

int main()
{
    bool keep;

    keep = false;

    do 
    {
        /* Varbiales declaration */
        string file_name, file_size, buffer, sender_ip, last_sender_ip;
        int size, code;

        /* Getting last sender ip */
        get_last_sender_address( &last_sender_ip );
        
        /* Search of sender */
        cout << "Sender's IP:" << "(enter 'd' for " << last_sender_ip << ")" << endl;
        do
        {
            user_input( &sender_ip );
            if( sender_ip.at(0) == 'd' )
            {
                sender_ip = last_sender_ip;
                break;
            }
        } while( !validate_address( &sender_ip ) );

        set_last_sender_address( sender_ip );

        cout << "Looking for sender..." << endl;
        connect_to_sender( &sender_ip );
        code = receive_message_from_sender( &buffer );
        if( code == FAILURE )
        {
            error_routine();
            return FAILURE;
        }
        cout << "Sender founded" << endl;

        /* Reception of file metadata */
        cout << "Receiving metadata..." << endl;
        code = receive_message_from_sender( &file_name );
        if( code == FAILURE )
        {
            error_routine();
            return FAILURE;
        }
        else if( code == INTERRUPTION )
        {
            interruption_routine();
            return SUCCES;
        }
        send_message_to_sender( string(1, HANDSHAKE_MSG ) );
        code = receive_message_from_sender( &file_size );
        if( code == FAILURE )
        {
            error_routine();
            return FAILURE;
        }
        else if( code == INTERRUPTION )
        {
            interruption_routine();
            return SUCCES;
        }
        send_message_to_sender( string(1, HANDSHAKE_MSG ) );
        cout << "Metadata received" << endl;

        /* Confirmation of reception */
        size = stoi( file_size );
        cout << "Donwload file " << '"' << file_name << '"' << " (" << 
                get_size_message( size ) << ")?[y/n]" << endl;
        while( true ) 
        {
            user_input( &buffer );
            if( buffer[0] == 'n' )
            {
                send_message_to_sender( string(1, NEGATIVE_MSG) );
            }
            else if( buffer[0] == 'y' )
            {
                /* Reception of file */
                send_message_to_sender( string(1, POSITIVE_MSG) );
                cout << "Receiving " << '"' << file_name << '"' << " from sender..." << endl;
                code = receive_file_from_sender( &file_name, size );
                if( code == FAILURE )
                {
                    error_routine();
                    return FAILURE;
                }
                else if( code == INTERRUPTION )
                {
                    interruption_routine();
                    return SUCCES;
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
            user_input( &buffer );
            if( buffer[0] == 'y' )
            {
                keep = true;
                break;
            }
            else if( buffer[0] == 'n' )
            {
                keep = false;
                break;
            }
        }
    } while( keep );

    /* End of receiver program */
    close_receiver_connection();
    exit_routine();
    
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
set_last_sender_address( string address )
{
    ofstream file;
    
    file.open( LAST_SENDER_ADDRESS_FILE );
    file << address << endl;
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