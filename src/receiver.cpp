#include "../include/receiver.h"

using namespace std;

int main()
{
    string file_name, file_size, buffer;
    int size;

    cout << "Looking for sender..." << endl;
    connect_to_sender();
    if( receive_message( &buffer ) == FAILURE )
    {
        cout << endl << "ERROR: something went wrong" << endl;;
        perror("");
        exit_rutine();
        return FAILURE;
    }
    cout << "Sender founded" << endl;

    cout << "Receiving metadata..." << endl;
    if( receive_message( &file_name ) == FAILURE )
    {
        cout << endl << "ERROR: something went wrong" << endl;;
        perror("");
        exit_rutine();
        return FAILURE;
    }
    if( receive_message( &file_size ) == FAILURE )
    {
        cout << endl << "ERROR: something went wrong" << endl;;
        perror("");
        exit_rutine();
        return FAILURE;
    }
    cout << "Metadata received" << endl;

    size = stoi( file_size );
    cout << "Receiving " << file_name << " " << get_size_message( size ) << " from sender..." << endl;
    if( receive_from_sender( &file_name, size ) == FAILURE )
    {
        cout << endl << "ERROR: something went wrong" << endl;;
        perror("");
        exit_rutine();
        return FAILURE;
    }
    else
    {
        cout << "File received" << endl;
        close_receiver_connection();
        exit_rutine();
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