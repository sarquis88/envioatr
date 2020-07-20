#include <iostream>
#include <iomanip>
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

#define HANDSHAKE_MSG   "ACK"
#define INT_MSG         "INT"

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
