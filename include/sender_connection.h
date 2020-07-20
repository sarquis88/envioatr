#include "commons.h"

#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

#define IP_SERVER   "192.168.100.3"
#define PORT        20000

#define BUFFER_SIZE     16

/*
    Configuration of the local socket
    @return SUCCES on a succesfully operation
            FAILURE on case of an error
*/
int setup_connection            ( void ); 

/*
    Waiting for the receiver
*/
void listen                     ( void );

/*
    Sent of file to receiver part
    @param  path of the file
    @return SUCCES on a succesfully sent
            FAILURE on case of an error
*/
int send_to_receiver            ( string );

/*
    Close sockets connection
*/
void close_sender_connection    ( void );

/*
    Sent of message to the receiver part
    @param  message in string format
    @return SUCCES on a succesfully download
            FAILURE on case of an error
            INTERRUPTION on case of an interruptio
*/
int send_message                ( string );