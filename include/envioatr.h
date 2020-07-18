#include <iostream>
#include <cstring>

#define SUCCES          0
#define FAILURE         1

#define FILE_NAME_SIZE  32
#define BUFFER_SIZE     16

#define EXIT_MSG        "exit"

using namespace std;

void file_name_input    ( string *                  );
void set_target_path    ( string *, string, size_t  );
void exit_rutine        (                           );
int move_file           ( string, string            );