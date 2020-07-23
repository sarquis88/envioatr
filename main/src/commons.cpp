#include "../include/commons.h"

using namespace std;

void
user_input( string *input_buffer )
{
    do
    {
        cout << ">> ";  
        getline( cin, *input_buffer );
    } while( input_buffer->empty() );
}

int
send_message( string * message , int socket )
{
	int n;

	n = (int) send( socket, message->c_str(), message->length(), 0 );
	if ( n < 0 ) 
		return FAILURE;
	else
		return SUCCES;
}

int
receive_message( string * message_buffer, int socket ) 
{
    char * buffer;
    int n;

	buffer = (char*)malloc( BUFFER_SIZE * sizeof(char) );
	n = (int) recv( socket, buffer, BUFFER_SIZE, 0 );
	if ( n <= 0 )
        return FAILURE;

    *message_buffer = string(buffer);
    free( buffer );

    if( message_buffer->at(0) == INT_MSG )
        return INTERRUPTION;
    else
        return SUCCES;
}

void
timeout_routine()
{
    cout << "Timeout" << endl;
}

void
print_load_pane( double factor )
{
    if( factor < 0 )
        return;

    char * pane;
    string pane_str;
    size_t i, percentage;

    percentage = ( size_t ) ( LOAD_PANE_SIZE * factor ) ;

    pane = (char*)malloc( LOAD_PANE_SIZE * sizeof(char) );

    for( i = 0; i < percentage; i++ )
        pane[i] = '#';
    for( ; i < LOAD_PANE_SIZE; i++ )
        pane[i] = '-';

    pane_str = string( pane );
    free( pane );

    cout << '\r' << "[" << pane_str << "]" << flush;
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