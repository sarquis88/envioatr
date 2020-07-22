#include "../include/sender.h"

using namespace std;

int
main() 
{   /* Variables declarations */
    bool keep;
    struct sigaction sa;
    string buffer_A, buffer_B;

    /* Variables initialization */
    sa.sa_handler = int_exit;
	sigaction(SIGINT, &sa,  NULL);
    keep = false;
    
    /* Configuring connection */
    cout << "Establishing connection..." << endl;
    if( setup_connection( &buffer_A ) == SUCCES )
        cout << "Connection established in " << buffer_A << endl;
    else
    {
        error_routine();
        return FAILURE;
    }

    /* Program loop initialization */
    do
    {
        /* Variables declarations */
        ssize_t size;
        int code;

        /* Connected and waiting for receiver */
        cout << "Waiting for receiver in..." << endl;
        buffer_A = listen();
        
        /* Connection established with receiver */
        cout << "Receiver founded: " << buffer_A << endl;
        send_ack_to_receiver();

        /* File selection and name transmission */
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
        {
            error_routine();
            return FAILURE;
        }
        receive_message_from_receiver( &buffer_B );
        
        /* Files size transmission */
        size = get_file_size( buffer_A );
        buffer_B = to_string( size );
        if( size <= 0 )
        {
            error_routine();
            return FAILURE;
        }
        else if( send_message_to_receiver( &buffer_B ) == FAILURE )
        {
            error_routine();
            return FAILURE;
        }
        receive_message_from_receiver( &buffer_B );

        /* Waits for acceptation */
        cout << "Waiting for confirmation from receiver..." << endl;
        code = receive_message_from_receiver( &buffer_B );
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
            if( buffer_B.at(0) == POSITIVE_MSG )
            {
                /* File transmission */
                cout << "Sending file..." << endl;
                if( send_file_to_receiver( buffer_A ) == FAILURE )
                {
                    error_routine();
                    return FAILURE;
                }
                else
                    cout << "File has been sended" << endl;
            }
            else if( buffer_B.at(0) == NEGATIVE_MSG )
            {
                cout << "Receiver has declined the file" << endl;
            }
        }

        /* Ask for continuing */
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
        
    } while( keep );

    /* End of sender program */
    close_sender_connection();
    exit_routine();

    return SUCCES;
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

void
int_exit( int sig ) 
{
	if( sig > 0 ) 
    {
        string buffer = string( 1, INT_MSG );
		send_message_to_receiver( &buffer );
	}
    close_sender_connection();
    exit_routine();
	exit(SUCCES);
}

bool
file_exists( string file_path )
{
    struct stat stat_struct;
    return ( stat( file_path.c_str(), &stat_struct) == 0 ); 
}