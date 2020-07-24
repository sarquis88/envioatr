 
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
    cout << endl << "INTERRUPTION: some part of the transmission has been interrupted" << endl;;
}