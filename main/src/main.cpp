#include "../include/main.h"

using namespace std;

int
main( int argc, char *argv[] ) 
{
    string input;
    struct sigaction sa;
    bool keep;
    int ret;

    if( argc > 1 )
        cout << endl << "We don't use any argument" << endl;

    keep = true;
    ret = SUCCES;

    sa.sa_handler = int_exit;
	sigaction(SIGINT, &sa,  NULL);

    if( get_host_name( &input ) == FAILURE )
    {
        error_routine();
        exit_routine();
        return FAILURE;
    }

    cout << endl << "Hello " << input << endl;

    do 
    {
        cout << endl    << "Choose an option:" << endl 
                        << SENDER_CODE      << "\t Send file"     << endl
                        << RECEIVER_CODE    << "\t Receive file"  << endl
                        << CLEAN_CODE       << "\t Clean reception folder" << endl
                        << NAME_CODE        << "\t Change username" << endl
                        << CHAT_CODE        << "\t Chat" << endl
                        << EXIT_CODE        << "\t Exit" << endl;
        user_input( &input );

        switch ( input[0] )
        {
            case SENDER_CODE:
                execv( SENDER_BIN, argv );
                break;
            case RECEIVER_CODE:
                execv( RECEIVER_BIN, argv );
                break;
            case CLEAN_CODE:
                if( clean_reception_folder() )
                    cout << endl << "Reception directory cleaned" << endl;
                else
                    cout << endl << "Empty directory" << endl;
                break;
            case NAME_CODE:
                cout << endl << "Enter new username: (one word)" << endl;
                user_input( &input );
                if( set_host_name( &input ) == FAILURE )
                {
                    ret = FAILURE;
                    keep = false;
                }
                else
                    cout << "Username has been changed to " << input << endl;
                break;
            case CHAT_CODE:
                cout << endl << "Not implemented yet, pal" << endl;
                break;
            case EXIT_CODE:
                keep = false;
                break;
            default:
                cout << "Bad answer" << endl;
                break;
        }
    } while( keep );

    if( ret == FAILURE )
        error_routine();

    exit_routine();

    return ret;
}