#include "../include/sender.h"

using namespace std;

int
main() 
{
    string source_path, target_path;
    
    cout << "Establishing connection...";
    if( setup_connection() == SUCCES )
        cout << endl << "Connection established" << endl;
    else
    {
        cout << endl << "ERROR: something went wrong" << endl;;
        perror("");
        exit_rutine();
        return FAILURE;
    }

    cout << "Waiting for receiver..." << endl;
    listen();
    cout << endl << "Receiver founded" << endl;

    file_name_input( &source_path );
    if( source_path.compare( EXIT_MSG ) == 0 )
    {
        exit_rutine();
        return SUCCES;
    }        

    if( send_to_receiver( source_path ) == FAILURE )
    {
        cout << endl << "ERROR: something went wrong" << endl;;
        perror("");
        exit_rutine();
        return FAILURE;
    }
    else
        cout << endl << "File has been sended" << endl;

    close_connection();

    exit_rutine();

    return SUCCES;
}

void
file_name_input( string *file_name )
{
    cout << endl << "File name to transfer:" << endl;
    do
    {
        cout << ">> ";  
        getline( cin, *file_name );
    } while( file_name->empty() );
}