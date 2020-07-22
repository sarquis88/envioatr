#include "commons.h"

#define SENDER_BIN      "./bin/sender.o"
#define RECEIVER_BIN    "./bin/receiver.o"

#define RECEPTION_DIR   "./receptions/"
#define HOST_NAME_FILE  "./resources/host_name.txt"

#define SENDER_CODE     '0'
#define RECEIVER_CODE   '1'
#define CLEAN_CODE      '2'
#define NAME_CODE       '3'
#define EXIT_CODE       '4'

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
