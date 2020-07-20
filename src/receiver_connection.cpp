#include "../include/receiver_connection.h"

using namespace std;

int r_sock_sender;
struct sockaddr_in r_sender_addr;
struct hostent *r_sender_hostent;

int
connect_to_sender() 
{
    int err;

    r_sender_hostent = gethostbyname( IP_SERVER );
	r_sock_sender = socket( AF_INET, SOCK_STREAM, 0 );
	memset( (char *) &r_sender_addr, '0', sizeof(r_sender_addr) );
	r_sender_addr.sin_family = AF_INET;
	bcopy( (char *)r_sender_hostent->h_addr, (char *)&r_sender_addr.sin_addr.s_addr, (size_t )r_sender_hostent->h_length );
	r_sender_addr.sin_port = htons( (uint16_t) PORT );

    while( true )
    {
        if ( connect( r_sock_sender, (struct sockaddr *)&r_sender_addr, sizeof(r_sender_addr ) ) == 0 )
		    return SUCCES;
        else 
        {
            err = errno;
            if( err == ECONNREFUSED )   // sender is not connected -> keep waiting
                sleep(1);
            else
                return FAILURE;         // another error
        }
    }
}

int
receive_file_from_sender( string *file_name, ssize_t file_size ) 
{
    string path;
    FILE *file;

    path = "./resources/" + *file_name;
	file = fopen( path.c_str(), "wb" );

    if( file != NULL ) 
    {
        ssize_t partial_size = 0;
        char *buffer = (char*)malloc( BUFFER_SIZE * sizeof(char) );
        #if (LOG == 1)
            int c = 0;
        #endif

        while( partial_size < file_size )
        {
            ssize_t n = recv( r_sock_sender, buffer, 1, 0);
            if( n <= 0 && partial_size < file_size )
                return INTERRUPTION;
                
            partial_size += n;

            fwrite( buffer, sizeof(char), (size_t) n, file );
            
            #if (LOG == 1)
                double percentage = ( (double)partial_size / (double)file_size ) * 100;
                if( c % 150 == 0 )   // print once in 150 times
                    cout << '\r' << fixed << setprecision(0) << "Downloading... " <<
                        round(percentage) << "%" << flush;
                c++;
            #endif
        }
        #if (LOG == 1)
            cout << '\r' << "                    " << flush;
            cout << '\r' << "Downloaded 100%" << flush;
        cout << endl;
        #endif

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

    if( message_buffer->compare( INT_MSG ) == 0 )
        return INTERRUPTION;
    else
        return SUCCES;
}