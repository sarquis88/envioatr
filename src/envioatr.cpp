#include "../include/envioatr.h"

using namespace std;

int
main() 
{
    string source_path, target_path;
    bool err;
    
    err = false;

    file_name_input( &source_path );
    if( source_path.compare( EXIT_MSG ) == 0 )
    {
        exit_rutine();
        return SUCCES;
    }        

    set_target_path( &target_path, source_path, source_path.length());

    if( move_file( source_path, target_path ) == FAILURE )
    {
        cout << endl << "ERROR: something went wrong" << endl;;
        perror("");
        err = true;      
    }
    else
    {
        cout << endl << "File has been moved succesfully" << endl;
    }

    exit_rutine();

    if( err )
        return FAILURE;
    else
        return SUCCES;
}

void
file_name_input( string *file_name )
{
    cout << endl << "File name to transfer:" << endl;
    
    do
    {
        cout << ">> ";  
        getline( cin, *file_name );
    } while( file_name->empty() );
}

int
move_file( string source_path, string target_path )
{
    FILE *source_file, *target_file;
    char *buffer; 
    size_t end;

    source_file = fopen( source_path.c_str(), "rb" );
    if( source_file == NULL )
        return FAILURE;

    target_file = fopen( target_path.c_str(), "wb" );
    if( target_file == NULL )
    {
        fclose( source_file );
        return FAILURE;
    }        
    
    buffer = (char*) malloc( BUFFER_SIZE * sizeof( char ) );
    end = 1;
    while( end > 0 )
    {
        end = fread( (void*) buffer, sizeof( char ), 1, source_file ); 
        fwrite( buffer, sizeof( char ), 1, target_file ); 
    }

    fclose( source_file );
    fclose( target_file );
    free(buffer);
    return SUCCES;
}

void
set_target_path( string *target_path, string source_path, size_t len )
{
    int i;
    bool slash = false;

    for( i = (int)len - 1; i >= 0; i-- )
    {
        if( source_path[i] == '/' )
        {
            slash = true;
            break;
        }
    }

    if( slash )
        target_path->assign( source_path, i, len - i);
    else
        target_path->assign( source_path );

    *target_path = "./resources/" + *target_path;
}

void
exit_rutine()
{
    cout << endl << "Bye!" << endl << endl;
}