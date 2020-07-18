#include "commons.h"

#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define IP_SERVER   "192.168.100.3"
#define PORT        20000

int setup_connection();
int configure_socket( int *, struct sockaddr_in *, string, int ); 