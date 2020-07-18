#include "../include/receiver.h"

using namespace std;

int main()
{
    cout << "Looking for sender..." << endl;
    connect_to_sender();

    cout << "Receiving from sender..." << endl;
    if( receive_from_sender() == FAILURE )
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