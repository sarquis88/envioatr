#include "../include/receiver_connection.h"

using namespace std;

int r_sock_sender;
struct sockaddr_in r_sender_addr;
struct hostent *r_sender_hostent;

int
connect_to_sender() 
{
    r_sender_hostent = gethostbyname( IP_SERVER );
	r_sock_sender = socket( AF_INET, SOCK_STREAM, 0 );
	memset( (char *) &r_sender_addr, '0', sizeof(r_sender_addr) );
	r_sender_addr.sin_family = AF_INET;
	bcopy( (char *)r_sender_hostent->h_addr, (char *)&r_sender_addr.sin_addr.s_addr, (size_t )r_sender_hostent->h_length );
	r_sender_addr.sin_port = htons( (uint16_t) PORT );

	if ( connect( r_sock_sender, (struct sockaddr *)&r_sender_addr, sizeof(r_sender_addr ) ) < 0 )
		return FAILURE;
    else
        return SUCCES;
}

int
receive_from_sender( string *file_name, ssize_t file_size ) 
{
    string path;
    FILE *file;
    char *buffer;
    ssize_t n, partial_size;

    path = "./resources/" + *file_name;
	file = fopen( path.c_str(), "wb" );
    n = 0;
    partial_size = 0;

    if( file != NULL ) 
    {
        buffer = (char*)malloc( BUFFER_SIZE * sizeof(char) );

        while( partial_size < file_size )
        {
            n = recv( r_sock_sender, buffer, 1, 0);
            if( n < 0 )
                break;
            partial_size += n;

            fwrite( buffer, sizeof(char), (size_t) n, file );
        }

        free( buffer );
        fclose( file );
        return SUCCES;
    }
	else 
        return FAILURE;
}

void
close_receiver_connection()
{
    close( r_sock_sender );
}

int
receive_message( string * message_buffer ) 
{
    char * buffer;
    int n;

	buffer = (char*)malloc( BUFFER_SIZE * sizeof(char) );
	n = (int) recv( r_sock_sender, buffer, BUFFER_SIZE, 0 );
	if ( n < 0 )
        return FAILURE;

    *message_buffer = string(buffer);
    free( buffer );

    return SUCCES;
}