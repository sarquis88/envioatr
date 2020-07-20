#include "../include/receiver.h"

using namespace std;

int main()
{
    /* Varbiales declaration */
    string file_name, file_size, buffer;
    int size, code;

    /* Search of sender */
    cout << "Looking for sender..." << endl;
    connect_to_sender();
    code = receive_message( &buffer );
    if( code == FAILURE )
    {
        error_routine();
        return FAILURE;
    }
    cout << "Sender founded" << endl;

    /* Reception of file metadata */
    cout << "Receiving metadata..." << endl;
    code = receive_message( &file_name );
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
    code = receive_message( &file_size );
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
    cout << "Metadata received" << endl;

    /* Reception of file */
    size = stoi( file_size );
    cout << "Receiving " << '"' << file_name << '"' << " " << 
            get_size_message( size ) << " from sender..." << endl;
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
        close_receiver_connection();
        exit_routine();
        return SUCCES;
    }
}

string
get_size_message( int size )
{
    string message;

    if( size < 1024 )
        message = to_string( size ) + "[b]";
    else if( size < 1048576 )
        message = to_string( size / 1024 ) + "[Kb]";
    else
        message = to_string( size / 1048576 ) + "[Mb]";

    return message;
}