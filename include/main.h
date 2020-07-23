#include "commons.h"
#include "receiver.h"
#include "sender.h"

#define SENDER_BIN      "./bin/sender.o"
#define RECEIVER_BIN    "./bin/receiver.o"

#define RECEPTION_DIR   "./receptions/"
#define HOST_NAME_FILE  "./resources/host_name.txt"

#define SENDER_CODE     '0'
#define RECEIVER_CODE   '1'
#define CLEAN_CODE      '2'
#define NAME_CODE       '3'
#define CHAT_CODE       '4'
#define EXIT_CODE       '5'

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