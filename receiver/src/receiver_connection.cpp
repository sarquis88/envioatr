#include "../include/receiver_connection.h"

using namespace std;

int r_sock_sender;
struct sockaddr_in r_sender_addr;
struct hostent *r_sender_hostent;

int
connect_to_sender( string sender_ip) 
{
    int err, c;

    r_sender_hostent = gethostbyname( sender_ip.c_str() );
	r_sock_sender = socket( AF_INET, SOCK_STREAM, 0 );
	memset( (char *) &r_sender_addr, '0', sizeof(r_sender_addr) );
	r_sender_addr.sin_family = AF_INET;
	bcopy( (char *)r_sender_hostent->h_addr, (char *)&r_sender_addr.sin_addr.s_addr, (size_t )r_sender_hostent->h_length );
	r_sender_addr.sin_port = htons( (uint16_t) PORT );

    c = 0;
    while( true )
    {
        if ( connect( r_sock_sender, (struct sockaddr *)&r_sender_addr, sizeof(r_sender_addr ) ) == 0 )
		    return SUCCES;
        else 
        {
            err = errno;
            if( err == ECONNREFUSED )   // sender is not connected -> keep waiting
            {
                sleep(1);
                c++;
                if( c == TTL )
                    return TIMEOUT;
            }
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

    path = RECEPTIONS_DIR + *file_name;
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
                if( c % 150 == 0 )   // print once in 150 times
                    print_load_pane( (double)partial_size / (double)file_size );
                c++;
            #endif
        }
        #if (LOG == 1)
            cout << '\r' << "                                                       " << flush;
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

bool
validate_address( string * address )
{
    regex e;

    e = ("(.*)\\.(.*)\\.(.*)\\.(.*)");

    if( regex_match( address->c_str(), e ) )
    {
        int i;
        
        for( i = 1; i < 5; i++ )
        {
            string group, result;
            long value;
            size_t j;

            group = "$" + to_string(i);
            result = regex_replace( address->c_str(), e, group.c_str() );

            for( j = 0; j < result.length(); j++ )
            {
                if( result[j] < 48 || result[j] > 57 )
                    return false;
            }

            value = strtol( result.c_str(), NULL, 10 );

            if( value > 255 || value < 0 )
                return false;
        }
        return true;
    }
    else 
        return false;
}

int
send_message_to_sender( string * message )
{
	return send_message( message, r_sock_sender );
}

int
receive_message_from_sender( string * buffer )
{
	return receive_message( buffer, r_sock_sender );
}

int
send_ack_to_sender()
{
    string buffer = string(1, ACK_MSG );
    return send_message_to_sender( &buffer );
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
