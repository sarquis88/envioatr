#include "../include/sender.h"

using namespace std;

int
main() 
{
    string source_path, target_path;
    
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

    cout << "Waiting for receiver..." << endl;
    listen();
    cout << "Receiver founded" << endl;

    file_name_input( &source_path );
    if( source_path.compare( EXIT_MSG ) == 0 )
    {
        exit_rutine();
        return SUCCES;
    }        

    if( send_message( get_file_name( source_path, source_path.length() ) ) == FAILURE )
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

    close_connection();

    exit_rutine();

    return SUCCES;
}

void
file_name_input( string *file_name )
{
    cout << "File name to transfer:" << endl;
    do
    {
        cout << ">> ";  
        getline( cin, *file_name );
    } while( file_name->empty() );
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
        return path_to_file.substr(i);
    else
        return path_to_file;
}