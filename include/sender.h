#include "commons.h"
#include "sender_connection.h"

using namespace std;

#define FILE_NAME_SIZE  32
#define BUFFER_SIZE     16

#define EXIT_MSG        "exit"

void user_input         ( string *                  );
string get_file_name    ( string, size_t );
ssize_t get_file_size ( string * );