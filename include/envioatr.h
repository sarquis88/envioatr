#include "commons.h"
#include "connection.h"

using namespace std;

#define FILE_NAME_SIZE  32
#define BUFFER_SIZE     16

#define EXIT_MSG        "exit"

void file_name_input    ( string *                  );
void set_target_path    ( string *, string, size_t  );
void exit_rutine        (                           );
int move_file           ( string, string            );