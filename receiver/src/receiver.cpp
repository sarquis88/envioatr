#include "../include/receiver.h"

using namespace std;

int 
main()
{
    /* Varbiales declaration */
    bool keep, no_error, no_interruption, no_timeout;
    int return_value;
    struct sigaction sa;

    /* Varbiales initialization */
    keep = false;
    no_error = true;
    sa.sa_handler = int_exit;

    /* SIGINT handler */
	sigaction(SIGINT, &sa,  NULL);

    do 
    {
        /* Varbiales declaration */
        string buffer_A, buffer_B;
        int size, code;

        /* Varbiales initialization */
        code = 0;
        no_interruption = true;
        no_timeout = true;

        /* Getting last sender ip */
        get_last_sender_address( &buffer_A );
        
        /* Input of sender address */
        if( no_error && no_interruption && no_timeout )
        {
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
        }

        /* Search of sender */
        if( no_error && no_interruption && no_timeout  )
        {
            cout << "Looking for sender..." << endl;
            code = connect_to_sender( buffer_B );
            if( code != SUCCES )
            {
                if( code == INTERRUPTION )
                    no_interruption = false;
                else if( code == FAILURE )
                    no_error = false;
                else if( code == TIMEOUT )
                    no_timeout = false;
            }
        }

        /* Waiting for sender's reply */
        if( no_error && no_interruption && no_timeout  )
        {
            code = receive_message_from_sender( &buffer_A );
            if( code != SUCCES )
            {
                if( code == INTERRUPTION )
                    no_interruption = false;
                else if( code == FAILURE )
                    no_error = false;
            }
            else
                cout << "Sender founded" << endl;
        }

        /* Reception of file name */
        if( no_error && no_interruption && no_timeout  )
        {
            cout << "Receiving metadata..." << endl;
            code = receive_message_from_sender( &buffer_A );    // file name reception
            if( code != SUCCES )
            {
                if( code == INTERRUPTION )
                    no_interruption = false;
                else if( code == FAILURE )
                    no_error = false;
            }
        }

        /* Reception of file size */
        if( no_error && no_interruption && no_timeout  )
        {
            send_ack_to_sender();
            code = receive_message_from_sender( &buffer_B );    // file size reception
            if( code != SUCCES )
            {
                if( code == INTERRUPTION )
                    no_interruption = false;
                else if( code == FAILURE )
                    no_error = false;
            }
            else
            {
                send_ack_to_sender();
                cout << "Metadata received" << endl;
            }
        }

        /* Confirmation of reception */
        if( no_error && no_interruption && no_timeout  )
        {
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
                        {
                            delete_corrupt_file( &buffer_A );
                            no_interruption = false;
                        }
                        else if( code == FAILURE )
                            no_error = false;
                    }
                    else
                    {
                        cout << "File received" << endl;
                    }
                }
                break;
            }
        }

        /* Check for interruptions */  
        if( !no_interruption )
            interruption_routine();

        /* Check for timeouts */  
        if( !no_timeout )
            timeout_routine();
        
        /* Ask for continuing */
        if( no_error )
        {
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
        }

        /* Check for errors */
        if( !no_error )
            break;

    } while( keep );

    /* Exit routines */
    close_receiver_connection();
    if( !no_error )
    {
        error_routine();
        return_value = FAILURE;
    }
    else
        return_value = SUCCES;
    exit_routine();
    
    return return_value;
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

void
int_exit( int sig ) 
{
	if( sig > 0 ) 
    {
        exit_routine();
        exit(SUCCES);
	}
}