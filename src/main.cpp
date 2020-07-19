#include "../include/main.h"

using namespace std;

int
main( int argc, char *argv[] ) 
{
    string input;

    if( argc > 1)
        cout << "No input argument is considered" << endl;

    cout << endl << "Are your a sender or a receiver?[s/r]";
    getline( cin, input );

    if( input[0] == 's' )
        input = SENDER_BIN;
    else if( input[0] == 'r' )
        input = RECEIVER_BIN;
    else
    {
        cout << "Bad answer" << endl;
        exit_rutine();
        return FAILURE;
    }

    if( execv( input.c_str(), argv ) == -1 ) 
    {
        cout << endl << "ERROR: something went wrong" << endl;;
        perror("");
        exit_rutine();
        return FAILURE;
    }
}
