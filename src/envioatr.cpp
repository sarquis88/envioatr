#include "../include/envioatr.h"

using namespace std;

void file_name_input( char * );
int move_file( char *, char * );
void set_target_path( char *, char *, size_t );

int
main() 
{
    char *source_path, *target_path;
    
    source_path = (char*) malloc( FILE_NAME_SIZE * sizeof(char) );
    target_path = (char*) malloc( FILE_NAME_SIZE * sizeof(char) );
    file_name_input( source_path );
    set_target_path( target_path, source_path, strlen( source_path ) );

    if( move_file( source_path, target_path ) == FAILURE )
    {
        cout << endl << "ERROR: something went wrong" << endl;
        free( source_path );
        return FAILURE;        
    }

    free( source_path );
}

void
file_name_input( char *file_name )
{
    cout << endl << "File name to transfer:" << endl << ">> ";
    cin >> file_name;
}

int
move_file( char * source_path, char * target_path )
{
    FILE *source_file, *target_file;
    char *buffer = (char*) malloc( BUFFER_SIZE * sizeof( char ) );
    size_t end = 1;

    source_file = fopen( source_path, "rb" );
    if( source_file == NULL )
        return FAILURE;

    target_file = fopen( target_path, "wb" );
    if( target_file == NULL )
        return FAILURE;
    
    while( end > 0 )
    {
        end = fread( (void*) buffer, sizeof( char ), 1, source_file ); 
        fwrite( buffer, sizeof( char ), 1, target_file ); 
    }

    fclose( source_file );
    fclose( target_file );
    return SUCCES;
}

void
set_target_path( char *target_path, char *source_path, size_t len )
{
    int i, j, new_len;

    for( i = len - 1; i >= 0; i-- )
    {
        if( source_path[i] == '/' )
            break;
    }

    new_len = len - i;

    char aux[ new_len ];
    for( j = 0; j < new_len; j++ )
    {
        aux[j] = source_path[ (i + 1) + j ];
    }

    sprintf( target_path, "./resources/%s", aux);
}
