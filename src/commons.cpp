#include "../include/commons.h"

using namespace std;

void
exit_routine()
{
    cout << endl << "Bye!" << endl << endl;
}

void
error_routine()
{
    cout << endl << "ERROR: something went wrong" << endl;;
    perror("");
    exit_routine();
}

void
interruption_routine()
{
    cout << endl << "INTERRUPTION: some part of the transmission has been disconnected" << endl;;
    exit_routine();
}