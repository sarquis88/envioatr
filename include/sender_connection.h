#include "commons.h"

#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

#define IP_SERVER   "192.168.100.3"
#define PORT        20000

#define BUFFER_SIZE     16

int setup_connection( ); 
void listen();
int send_to_receiver( string );
void close_connection();