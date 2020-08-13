#ifndef _TAREA4_H_
#define _TAREA4_H_

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <string.h>

#include <pwd.h>
#define maxln_Com_Amb 105
#define max_args 10

char comando[maxln_Com_Amb];
char *args[max_args];

char PWD[maxln_Com_Amb];
char PATH[maxln_Com_Amb];
char USER[maxln_Com_Amb];

int parseCommand();
int checkPath();
void executeCommand( int background );
void showHelp();
void showCredits();

#endif //_TAREA4_H_