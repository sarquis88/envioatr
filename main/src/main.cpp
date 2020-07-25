#include "../include/main.h"

using namespace std;

int
main( int argc, char *argv[] ) 
{
    string input;
    struct sigaction sa;
    bool keep;
    int ret;

    /* Argument handlers for zenity launch */
    if( argc > 1 )
    {
        input = string( argv[1] );
        if( input.compare("-s") == 0 )
        {
            if( execv( SENDER_BIN, argv ) < 0 )
                error_routine();
        }
        else if( input.compare("-r") == 0 )
        {
            if( execv( RECEIVER_BIN, argv ) < 0 )
                error_routine();
        }
        else if( input.compare("-c") == 0 )
        {
            if( clean_reception_folder() )
                cout << "Reception directory cleaned" << endl;
            else
                cout << "Empty directory" << endl;
        }
        else if( input.compare("-u") == 0 )
        {
            string new_name = string( argv[2] );
            set_host_name ( &new_name );
            cout << "Username changed succesfully" << endl;
        }
        else
            cout << "Unrecognized argument" << endl;
        return SUCCES;
    }

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
                        << EXIT_CODE        << "\t Exit" << endl;
        user_input( &input );

        switch ( input[0] )
        {
            case SENDER_CODE:
                if( execv( SENDER_BIN, argv ) < 0 )
                    error_routine();
                break;
            case RECEIVER_CODE:
                if( execv( RECEIVER_BIN, argv ) < 0 )
                    error_routine();
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

    path = RECEPTIONS_DIR;
    
    for (const auto & entry : filesystem::directory_iterator( path ) )
    {
        string gitignore;

        gitignore = RECEPTIONS_DIR + string(".gitignore");
        path = entry.path().c_str();

        if( path.compare( gitignore ) != 0)
        {
            filesystem::remove( entry.path() );
            clean = true;
        }
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