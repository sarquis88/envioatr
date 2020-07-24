#include "commons.h"

using namespace std;

#define LOG         1

#define TTL         8

#define LOAD_PANE_SIZE  50

#define BYTES_IN_KILO   1024
#define BYTES_IN_MEGA   1048576
#define BYTES_IN_GIGA   1073741824

/*
    Try to connect to the sender part
    @param  sender's ip direction
    @return SUCCES on a succesfully connection
            FAILURE on case of an error
*/
int connect_to_sender           ( string ); 

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

/*
    Validate the address passed
    @param string containing the address
    @return true in case of a correct address
            false in case of not
*/
bool validate_address           ( string * );

/*
    Send message to sender
*/
int send_message_to_sender      ( string * );

/*
    Reception of message from the sender
*/
int receive_message_from_sender ( string * );

/*
    Wrapper from send_message_to_sender. Sends ACK message
*/
int send_ack_to_sender          ( void );

/*
    Prints load pane
    @param  percentage of loading ( 0 - 0.99 )
*/
void print_load_pane            ( double );