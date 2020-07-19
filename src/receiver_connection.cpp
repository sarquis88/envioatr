#include "../include/receiver_connection.h"

using namespace std;

int sock_sender;
struct sockaddr_in sender_addr;
struct hostent *sender_hostent;

int
connect_to_sender() 
{
    sender_hostent = gethostbyname( IP_SERVER );
	sock_sender = socket( AF_INET, SOCK_STREAM, 0 );
	memset( (char *) &sender_addr, '0', sizeof(sender_addr) );
	sender_addr.sin_family = AF_INET;
	bcopy( (char *)sender_hostent->h_addr, (char *)&sender_addr.sin_addr.s_addr, (size_t )sender_hostent->h_length );
	sender_addr.sin_port = htons( (uint16_t) PORT );

	if ( connect( sock_sender, (struct sockaddr *)&sender_addr, sizeof(sender_addr ) ) < 0 )
		return FAILURE;
    else
        return SUCCES;
}

int
receive_from_sender( string file_name ) 
{
    string path;

    path = "./resources/" + file_name;

	FILE* file = fopen( path.c_str(), "wb" );
    size_t n;
    char *buffer;

    if(file != NULL) 
    {
        buffer = (char*)malloc( BUFFER_SIZE * sizeof(char) );

        while( ( n = recv( sock_sender, buffer, 1, 0) ) > 0 )
            fwrite( buffer, sizeof(char), (size_t) n, file );

        free( buffer );
        fclose( file );
        return SUCCES;
    }
	else 
        return FAILURE;
}

void
close_connection()
{
    close( sock_sender );
}

int
receive_message( string * message_buffer ) 
{
    char * buffer;
    int n;

	buffer = (char*)malloc( BUFFER_SIZE * sizeof(char) );
	n = (int) recv( sock_sender, buffer, BUFFER_SIZE, 0 );
	if ( n < 0 )
        return FAILURE;

    *message_buffer = string(buffer);
    free( buffer );

    return SUCCES;
}