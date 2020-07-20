#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

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
