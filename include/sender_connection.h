#include "commons.h"

using namespace std;

#define IP_SERVER   "192.168.100.3"

/*
    Configuration of the local socket
    @param  string buffer to store the sender address
    @return SUCCES on a succesfully operation
            FAILURE on case of an error
*/
int setup_connection            ( string * ); 

/*
    Waiting for the receiver
    @return address of the receiver founded
*/
string listen                   ( void );

/*
    Sent of file to receiver part
    @param  path of the file
    @return SUCCES on a succesfully sent
            FAILURE on case of an error
*/
int send_file_to_receiver       ( string );

/*
    Close sockets connection
*/
void close_sender_connection    ( void );

/*
    Send message to the receiver
*/
int send_message_to_receiver    ( string * );

/*
    Reception of message from the receiver
*/
int receive_message_from_receiver   ( string * );

/*
    Wrapper of send_message_to_receiver. Send ACK message
*/
int send_ack_to_receiver            ( void );