#include "commons.h"

#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;

#define IP_SERVER   "192.168.100.3"
#define PORT        20000

#define BUFFER_SIZE     16

#define PATH_TO_RECEIVE "./resources/received_file"

int connect_to_sender( ); 
int receive_from_sender();
void close_connection();