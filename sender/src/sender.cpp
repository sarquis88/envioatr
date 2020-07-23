#include "../include/sender.h"

using namespace std;

int
main() 
{   
    /* Variables declarations */
    bool keep, no_error;
    int return_value;
    struct sigaction sa;
    string buffer_A, buffer_B;

    /* Variables initialization */
    keep = false;
    no_error = true;
    sa.sa_handler = int_exit;

    /* SIGINT handler */
	sigaction(SIGINT, &sa,  NULL);
    
    /* Configuring connection */
    cout << endl << "Establishing connection..." << endl;
    if( setup_connection( &buffer_A ) == SUCCES )
        cout << "Connection established in " << buffer_A << endl;
    else
        no_error = false;

    do
    {
        /* Variables declarations */
        ssize_t size;
        int code;

        /* Connected and waiting for receiver */
        if( no_error )
        {
            cout << "Waiting for receiver..." << endl;
            buffer_A = listen();
            cout << "Receiver founded: " << buffer_A << endl;
            send_ack_to_receiver();
        }   

        /* File selection and name transmission */
        if( no_error )
        {
            cout << "File name to transfer:" << endl;
            while( true )
            {
                user_input( &buffer_A );
                if( file_exists( buffer_A ) )
                    break;
                else
                    cout << "File doesn't exists, try again:" << endl;
            }
            buffer_B = get_file_name( buffer_A, buffer_A.length() );
            if( send_message_to_receiver( &buffer_B ) == FAILURE )
                no_error = false;
            else
                receive_message_from_receiver( &buffer_B );
        }
        
        /* Files size transmission */
        if( no_error )
        {
            size = get_file_size( buffer_A );
            buffer_B = to_string( size );
            if( size <= 0 )
                no_error = false;
            else if( send_message_to_receiver( &buffer_B ) == FAILURE )
                no_error = false;
            else
                receive_message_from_receiver( &buffer_B );
        }

        /* Waits for acceptation */
        if( no_error )
        {
            cout << "Waiting for confirmation from receiver..." << endl;
            code = receive_message_from_receiver( &buffer_B );
            if( code != SUCCES )
            {
                if( code == INTERRUPTION )
                    interruption_routine();
                no_error = false;
            }
            else
            {
                if( buffer_B.at(0) == POSITIVE_MSG )
                {
                    /* File transmission */
                    cout << "Sending file..." << endl;
                    if( send_file_to_receiver( buffer_A ) == FAILURE )
                        return FAILURE;
                    else
                        cout << "File has been sended" << endl;
                }
                else if( buffer_B.at(0) == NEGATIVE_MSG )
                {
                    cout << "Receiver has declined the file" << endl;
                }
            }
        }

        /* Ask for continuing */
        if( no_error )
        {
            while( true )
            {
                cout << endl << "Do you want to send more files?[y/n]" << endl;
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
    close_sender_connection();
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
get_file_name( string path_to_file, size_t len )
{
    int i;
    bool slash = false;

    for( i = (int)len - 1; i >= 0; i-- )
    {
        if( path_to_file[i] == '/' )
        {
            slash = true;
            break;
        }
    }
    
    if( slash )
        return path_to_file.substr( i + 1 );
    else
        return path_to_file;
}

ssize_t
get_file_size( string file_path )
{
    FILE* file;
    ssize_t size;

    file = fopen( file_path.c_str(), "rb" );
    size = 0;

    if( file != NULL ) 
    {
        fseek( file, 0L, SEEK_END);
        size = ftell(file);
        fclose(file);
    }

    return size;
}

bool
file_exists( string file_path )
{
    struct stat stat_struct;
    return ( stat( file_path.c_str(), &stat_struct) == 0 ); 
}

void
int_exit( int sig ) 
{
	if( sig > 0 ) 
    {
        string buffer = string(1, INT_MSG );
	    send_message_to_receiver( &buffer );
        exit_routine();
        exit(SUCCES);
	}
}