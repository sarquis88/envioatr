#include "commons.h"
#include "receiver_connection.h"

using namespace std;

#define LAST_SENDER_ADDRESS_FILE    "./resources/last_sender_address.txt"

/* 
    Create a message for printing the size of a file 
    @param size of the file in int format   
*/
string get_size_message     ( int );

/*
    Returns the last sender address used
    @param  buffer to store the address
    @param  SUCCES on succes operation
            FAILURE in other case
*/
int get_last_sender_address ( string * buffer );

/*
    Set the last sender address used
    @param  address to set
    @param  SUCCES on succes operation
            FAILURE in other case
*/
int set_last_sender_address ( string address );