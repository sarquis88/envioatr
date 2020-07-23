#include "../include/main.h"

using namespace std;

int
main( ) 
{
    string input;
    struct sigaction sa;
    bool keep;
    int code, ret;

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
                code = launch_sender();
                if( code == FAILURE )
                {
                    keep = false;
                    ret = FAILURE;
                }
                else if( code == INTERRUPTION )
                    interruption_routine();
                break;
            case RECEIVER_CODE:
                code = launch_receiver();
                if( code == FAILURE )
                {
                    keep = false;
                    ret = FAILURE;
                }
                else if( code == INTERRUPTION )
                    interruption_routine();
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

void
int_exit( int sig ) 
{
	if( sig > 0 ) 
    {
        exit_routine();
        exit(SUCCES);
	}
}

bool
clean_reception_folder()
{
    string path;
    bool clean = false;

    path = RECEPTION_DIR;
    
    for (const auto & entry : filesystem::directory_iterator( path ) )
    {
        clean = true;
        filesystem::remove( entry.path() );
    }

    return clean;
}

int 
set_host_name( string * name )
{
    ofstream file;
    
    file.open( HOST_NAME_FILE );
    file << *name << endl;
    file.close();

    return SUCCES;
}

int 
get_host_name( string * buffer )
{
    ifstream file;
    char *aux;

    aux = (char*)malloc( BUFFER_SIZE * sizeof(char) );
    
    file.open( HOST_NAME_FILE );
    file >> aux;
    file.close();

    *buffer = string( aux );

    free( aux );
    return SUCCES;
}

void
exit_routine()
{
    cout << endl << "Bye!" << endl << endl;
}

void
error_routine()
{
    cout << endl;
    perror("ERROR: something went wrong");
}

void
interruption_routine()
{
    cout << endl << "INTERRUPTION: some part of the transmission has been disconnected" << endl;;
}