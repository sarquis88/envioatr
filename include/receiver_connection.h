#include "commons.h"

using namespace std;

#define IP_SERVER   "192.168.100.3"
#define PORT        20000

#define LOG         1

#define BUFFER_SIZE 32

/*
    Try to connect to the sender part
    @return SUCCES on a succesfully connection
            FAILURE on case of an error
*/
int connect_to_sender           ( void ); 

/*
    Reception of file from sender part
    @param  path to store the file in string format
            size of the file received by the sender
    @return SUCCES on a succesfully download
            FAILURE on case of an error
            INTERRUPTION on case of an interruption
*/
int receive_file_from_sender         ( string *, ssize_t );

/*
    Close the sender socket connection
*/
void close_receiver_connection  ( void );

/*
    Reception of a message from sender part
    @param  buffer to store the receiving message
    @return SUCCES on a succesfully download
            FAILURE on case of an error
            INTERRUPTION on case of an interruption
*/
int receive_message             ( string * );