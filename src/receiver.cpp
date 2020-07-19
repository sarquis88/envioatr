#include "../include/receiver.h"

using namespace std;

int main()
{
    string file_name;

    cout << "Looking for sender..." << endl;
    connect_to_sender();

    if( receive_message( &file_name ) == FAILURE )
    {
        cout << endl << "ERROR: something went wrong" << endl;;
        perror("");
        exit_rutine();
        return FAILURE;
    }

    cout << "Receiving " << file_name << " from sender..." << endl;
    if( receive_from_sender( file_name ) == FAILURE )
    {
        cout << endl << "ERROR: something went wrong" << endl;;
        perror("");
        exit_rutine();
        return FAILURE;
    }
    else
    {
        cout << "File received" << endl;
        close_connection();
        return SUCCES;
    }
}