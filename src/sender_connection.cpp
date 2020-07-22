#include "../include/sender_connection.h"

using namespace std;

int s_sock_sender, s_sock_receiver;
uint s_receiver_len;
struct sockaddr_in s_sender_addr;
struct sockaddr_in s_receiver_addr;

int
setup_connection( string *address ) 
{
	s_sock_sender = socket( AF_INET, SOCK_STREAM, 0);
	memset( (char *) &s_sender_addr, 0, sizeof( s_sender_addr ) );

	s_sender_addr.sin_family = AF_INET;
	s_sender_addr.sin_addr.s_addr = INADDR_ANY;
	s_sender_addr.sin_port = htons( (uint16_t) PORT );
	if ( bind( s_sock_sender, ( struct sockaddr *) &s_sender_addr, sizeof( s_sender_addr ) ) < 0 )
		return FAILURE;
    else
	{
		*address = inet_ntoa( s_sender_addr.sin_addr );
		return SUCCES;
	}        
}

string
listen()
{
    listen( s_sock_sender, 5 );
	s_receiver_len = sizeof( s_receiver_addr );
	s_sock_receiver = accept( s_sock_sender, (struct sockaddr *) &s_receiver_addr, &s_receiver_len );

	return ( inet_ntoa( s_receiver_addr.sin_addr ) );
}

int 
send_file_to_receiver( string file_path ) 
{
	FILE* file = fopen( file_path.c_str(), "rb" );

	if ( file != NULL ) 
	{
		char *buffer = (char *)malloc( BUFFER_SIZE * sizeof( char ) );

		while( fread( buffer, sizeof(char), 1, file) > 0 )
			send( s_sock_receiver, buffer, 1, 0);

		fclose( file );
		free( buffer );
		return SUCCES;
	}
	else
		return FAILURE;
}

void
close_sender_connection()
{
    close( s_sock_receiver );
    close( s_sock_sender );
}

int
send_message_to_receiver( string message )
{
	return send_message( message, s_sock_receiver );
}

int
receive_message_from_receiver( string * buffer )
{
	return receive_message( buffer, s_sock_receiver );
}