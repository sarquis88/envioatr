#include "../include/sender_connection.h"

using namespace std;

int sock_sender, sock_receiver;
uint receiver_len;
struct sockaddr_in sender_addr;
struct sockaddr_in receiver_addr;

int
setup_connection() 
{
	sock_sender = socket( AF_INET, SOCK_STREAM, 0);
	memset( (char *) &sender_addr, 0, sizeof( sender_addr ) );

	sender_addr.sin_family = AF_INET;
	sender_addr.sin_addr.s_addr = inet_addr( IP_SERVER );
	sender_addr.sin_port = htons( (uint16_t) PORT );
	if ( bind( sock_sender, ( struct sockaddr *) &sender_addr, sizeof( sender_addr ) ) < 0 )
		return FAILURE;
    else
        return SUCCES;
}

void
listen()
{
    listen( sock_sender, 5 );
	receiver_len = sizeof( receiver_addr );
	sock_receiver = accept( sock_sender, (struct sockaddr *) &receiver_addr, &receiver_len );
}

int 
send_to_receiver( string file_path ) 
{
	char * buffer;
	FILE* file = fopen( file_path.c_str(), "rb" );

	if ( file != NULL ) 
	{
		buffer = (char *)malloc( BUFFER_SIZE * sizeof( char ) );

		while( fread( buffer, sizeof(char), 1, file) > 0 )
			send( sock_receiver, buffer, 1, 0);

		fclose( file );
		free( buffer );
		return SUCCES;
	}
	else
		return FAILURE;
}

void
close_connection()
{
    close( sock_receiver );
    close( sock_sender );
}

int
send_message( string message )
{
	int n;

	n = (int) send( sock_receiver, message.c_str(), message.length(), 0 );
	if ( n < 0 ) 
		return FAILURE;
	else
		return SUCCES;
}