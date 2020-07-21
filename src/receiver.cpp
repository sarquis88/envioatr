#include "../include/receiver.h"

using namespace std;

// TODO: aceptar archiv

int main()
{
    /* Varbiales declaration */
    string file_name, file_size, buffer, sender_ip;
    int size, code;

    /* Search of sender */
    cout << "Sender's IP:" << endl;
    do
    {
        user_input( &sender_ip );
    } while( !validate_address( &sender_ip ) );

    cout << "Looking for sender..." << endl;
    connect_to_sender( &sender_ip );
    code = receive_message_from_sender( &buffer );
    if( code == FAILURE )
    {
        error_routine();
        return FAILURE;
    }
    cout << "Sender founded" << endl;

    /* Reception of file metadata */
    cout << "Receiving metadata..." << endl;
    code = receive_message_from_sender( &file_name );
    if( code == FAILURE )
    {
        error_routine();
        return FAILURE;
    }
    else if( code == INTERRUPTION )
    {
        interruption_routine();
        return SUCCES;
    }
    code = receive_message_from_sender( &file_size );
    if( code == FAILURE )
    {
        error_routine();
        return FAILURE;
    }
    else if( code == INTERRUPTION )
    {
        interruption_routine();
        return SUCCES;
    }
    cout << "Metadata received" << endl;

    /* Reception of file */
    size = stoi( file_size );
    cout << "Donwload file " << '"' << file_name << '"' << " (" << 
            get_size_message( size ) << ")?[y/n]" << endl;
    while( true ) 
    {
        user_input( &buffer );
        if( buffer[0] == 'n' )
        {
            send_message_to_sender( string(1, NEGATIVE_MSG) );
            exit_routine();
            return SUCCES;
        }
        else if( buffer[0] == 'y' )
        {
            send_message_to_sender( string(1, POSITIVE_MSG) );
            break;
        }
    }
    cout << "Receiving " << '"' << file_name << '"' << " from sender..." << endl;
    code = receive_file_from_sender( &file_name, size );
    if( code == FAILURE )
    {
        error_routine();
        return FAILURE;
    }
    else if( code == INTERRUPTION )
    {
        interruption_routine();
        return SUCCES;
    }
    else
    {
        cout << "File received" << endl;
        close_receiver_connection();
        exit_routine();
        return SUCCES;
    }
}

string
get_size_message( int size )
{
    string message;

    if( size < 1024 )
        message = to_string( ( size ) ) + "[b]";
    else if( size < BYTES_IN_MEGA )
        message = to_string( (double) size / BYTES_IN_KILO ) + "[Kb]";
    else if ( size < BYTES_IN_GIGA )
        message = to_string( (double) size / BYTES_IN_MEGA ) + "[Mb]";
    else
        message = to_string( (double) size / BYTES_IN_GIGA ) + "[Gb]";

    return message;
}