#include "../include/sender.h"

using namespace std;

int
main() 
{
    string source_path, target_path, keep_str;
    ssize_t file_size;
    bool keep;
    
    keep = false;
    
    cout << "Establishing connection..." << endl;
    if( setup_connection() == SUCCES )
        cout << "Connection established" << endl;
    else
    {
        cout << "ERROR: something went wrong" << endl;;
        perror("");
        exit_rutine();
        return FAILURE;
    }

    do
    {
        cout << "Waiting for receiver..." << endl;
        listen();
        
        cout << "Receiver founded" << endl;
        if( send_message( HANDSHAKE_MSG ) == FAILURE )
        {
            cout << "ERROR: something went wrong" << endl;;
            perror("");
            exit_rutine();
            return FAILURE;
        }

        cout << "File name to transfer:" << endl;
        user_input( &source_path );

        if( send_message( get_file_name( source_path, source_path.length() ) ) == FAILURE )
        {
            cout << "ERROR: something went wrong" << endl;;
            perror("");
            exit_rutine();
            return FAILURE;
        }
        
        file_size = get_file_size( &source_path );
        if( file_size <= 0 )
        {
            cout << "ERROR: something went wrong" << endl;;
            perror("");
            exit_rutine();
            return FAILURE;
        }
        else if( send_message( to_string( file_size ) ) == FAILURE )
        {
            cout << "ERROR: something went wrong" << endl;;
            perror("");
            exit_rutine();
            return FAILURE;
        }
        

        if( send_to_receiver( source_path ) == FAILURE )
        {
            cout << "ERROR: something went wrong" << endl;;
            perror("");
            exit_rutine();
            return FAILURE;
        }
        else
            cout << "File has been sended" << endl;

        while( true )
        {
            cout << endl << "Do you want to send more files?[y/n]" << endl;
            user_input( &keep_str );
            if( keep_str[0] == 'y' )
            {
                keep = true;
                break;
            }
            else if( keep_str[0] == 'n' )
            {
                keep = false;
                break;
            }
        }
        
    } while( keep );

    close_sender_connection();

    exit_rutine();

    return SUCCES;
}

void
user_input( string *input_buffer )
{
    do
    {
        cout << ">> ";  
        getline( cin, *input_buffer );
    } while( input_buffer->empty() );
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
get_file_size( string *file_path )
{
    FILE* file;
    ssize_t size;

    file = fopen( file_path->c_str(), "rb" );
    size = 0;

    if( file != NULL ) 
    {
        fseek( file, 0L, SEEK_END);
        size = ftell(file);
        fclose(file);
    }

    return size;
}