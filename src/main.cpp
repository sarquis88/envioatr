#include "../include/main.h"

using namespace std;

int
main( int argc, char *argv[] ) 
{
    string input;
    struct sigaction sa;
    bool keep, fork;

    fork = false;
    keep = false;

    sa.sa_handler = int_exit;
	sigaction(SIGINT, &sa,  NULL);

    if( get_host_name( &input ) == FAILURE )
    {
        error_routine();
        exit_routine();
        return FAILURE;
    }

    cout << endl << "Hello " << input << endl;

    if( argc > 1)
        cout << "No input argument is considered" << endl;

    do 
    {
        cout << endl    << "Choose an option:" << endl 
                        << SENDER_CODE      << "\t Send file"     << endl
                        << RECEIVER_CODE    << "\t Receive file"  << endl
                        << CLEAN_CODE       << "\t Clean reception folder" << endl
                        << NAME_CODE        << "\t Change username" << endl
                        << EXIT_CODE        << "\t Exit" << endl;
        user_input( &input );

        switch ( input[0] )
        {
            case SENDER_CODE:
                input = SENDER_BIN;
                keep = false;
                fork = true;
                break;
            case RECEIVER_CODE:
                input = RECEIVER_BIN;
                keep = false;
                fork = true;
                break;
            case CLEAN_CODE:
                if( clean_reception_folder() )
                    cout << endl << "Reception directory cleaned" << endl;
                else
                    cout << endl << "Empty directory" << endl;
                exit_routine();
                keep = false;
                break;
            case NAME_CODE:
                cout << endl << "Enter new username: (one word)" << endl;
                user_input( &input );
                if( set_host_name( &input ) == FAILURE )
                {
                    error_routine();
                    exit_routine();
                    return FAILURE;
                }
                cout << "Username has been changed to " << input << endl;
                keep = true;
                break;
            case EXIT_CODE:
                exit_routine();
                keep = false;
                break;
            default:
                cout << "Bad answer" << endl;
                keep = true;
                break;
        }
    } while( keep );

    if( fork )
    {
        cout << endl;
        if( execv( input.c_str(), argv ) == -1 ) 
        {
            error_routine();
            exit_routine();
            return FAILURE;
        }
    }

    return SUCCES;
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