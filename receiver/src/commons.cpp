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