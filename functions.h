#ifndef _TAREA4_H_
#define _TAREA4_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <pwd.h>
#include <sys/wait.h>

#define max_lines 150
#define max_args 15

char command[max_lines];
char *args[max_args];

char PWD[max_lines];
char USER[max_lines];

int parseCommand();
int checkPath();
void executeCommand( int background );
void showHelp();
void showCredits();

#endif //_TAREA4_H_