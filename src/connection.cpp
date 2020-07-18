#include "../include/connection.h"

using namespace std;

int
setup_connection()
{
    int sockfd;
    struct sockaddr_in serv_addr;

    return configure_socket( &sockfd, &serv_addr, IP_SERVER, PORT );
}

int
configure_socket(   int *sockfd, struct sockaddr_in *serv_addr, 
                    string direction, int port) 
{
	*sockfd = socket( AF_INET, SOCK_STREAM, 0);
	memset( (char *) serv_addr, 0, sizeof( *serv_addr ) );

	serv_addr->sin_family = AF_INET;
	serv_addr->sin_addr.s_addr = inet_addr( direction.c_str() );
	serv_addr->sin_port = htons( (uint16_t)port );
	if ( bind( *sockfd, ( struct sockaddr *) serv_addr, sizeof( *serv_addr ) ) < 0 )
		return FAILURE;
    else
        return SUCCES;
}