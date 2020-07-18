#include "../include/receiver_connection.h"

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
receive_from_sender() 
{
	FILE* file = fopen( PATH_TO_RECEIVE, "wb" );
    size_t n;
    char *buffer;

    buffer = (char*)malloc( BUFFER_SIZE * sizeof(char) );

    if(file != NULL) 
    {
        while( ( n = recv( sock_sender, buffer, 1, 0) ) > 0 )
            fwrite( buffer, sizeof(char), (size_t) n, file );

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