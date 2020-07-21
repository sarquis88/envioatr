#include "commons.h"
#include "sender_connection.h"

using namespace std;

#define FILE_NAME_SIZE  32

#define EXIT_MSG        "exit"

/*
    Parse file's name by path
    @param  path of the file
            length of the path
    @return file's name in string format
*/
string get_file_name    ( string, size_t );

/*
    File's size getter
    @param  path to the file
    @return file's size in ssize_t format
*/
ssize_t get_file_size   ( string * );

/*
    Interruption routine
    @param  (unknown, to keep the compiler happy)
*/
void int_exit           ( int );

/*
    Check file existance
    @param  file path in string format
    @return true if exists
            false if not
*/
bool file_exists        ( string * );