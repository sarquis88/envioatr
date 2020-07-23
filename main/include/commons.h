#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>

#include <regex>

#include <cstring>
#include <cerrno>
#include <cstdio>
#include <csignal>
#include <cmath>

#include <arpa/inet.h>
#include <netdb.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h> 

#include <unistd.h>

#define SUCCES          0
#define FAILURE         1
#define INTERRUPTION    2
#define TIMEOUT         3

#define RECEPTION_DIR   "./receptions/"
#define HOST_NAME_FILE  "./resources/host_name.txt"

#define ACK_MSG         ( (char) 'A' )
#define INT_MSG         ( (char) 'B' )
#define POSITIVE_MSG    ( (char) 'C' )
#define NEGATIVE_MSG    ( (char) 'D' )

#define PORT            2000

#define BUFFER_SIZE     64

#define LOAD_PANE_SIZE  50

#define BYTES_IN_KILO   1024
#define BYTES_IN_MEGA   1048576
#define BYTES_IN_GIGA   1073741824

using namespace std;

/*
    Routine for handle timeouts in the program
*/
void timeout_routine        ( void );

/*
    Input stream for the user
    @param  buffer to store de input string
*/
void user_input             ( string * );

/*
    Sent of message to the socket
    @param  message in string format
    @param  socket from destiny
    @return SUCCES on a succesfully download
            FAILURE on case of an error
            INTERRUPTION on case of an interruptio
*/
int send_message                ( string *, int );

/*
    Reception of message from the socket
    @param  buffer to store the message
    @param  socket from destiny
    @return SUCCES on a succesfully download
            FAILURE on case of an error
            INTERRUPTION on case of an interruptio
*/
int receive_message             ( string *, int );

/*
    Prints load pane
    @param  percentage of loading ( 0 - 0.99 )
*/
void print_load_pane            ( double );


/*
    Interruption routine
    @param  (unknown, to keep the compiler happy)
*/
void int_exit               ( int );

/*
    Remove all files in ./receptions/
    @return true for succes
            false if the dir is empty
*/
bool clean_reception_folder ( void );

/*
    Get host name from host_name.txt
*/
int get_host_name           ( string * );

/*
    Set host name to host_name.txt
*/
int set_host_name           ( string * );

/* 
    Routine for exiting the program 
*/
void exit_routine            ( void );

/* 
    Routine for handle errors in the program 
*/
void error_routine           ( void );

/*
    Routine for handle interruptions in the program
*/
void interruption_routine    ( void );
