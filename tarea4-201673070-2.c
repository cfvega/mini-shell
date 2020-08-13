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


int parseCommand() {
  int i;
  for(i = 0; i < (max_args - 1); i++) args[i] = NULL;
  strtok(comando," "), i = 0;
  args[i] = comando;
  while((args[++i] = strtok(NULL," ")) != NULL && i < (max_args - 2));
  return i;
}

int checkPath() {
  int ok = 0;
  for(int i = 0; i<strlen(comando) ;i++) {
    char *r_position_ptr = strrchr("^/", comando[i]);
    if(r_position_ptr != NULL) {
      ok = 1;
      break;
    }
  }
  return ok;
}

void executeCommand( int background ) {
  int pid = 0;
  char buffer[100]="";
  pid = fork();

  if( checkPath() == 0 ) {
    strcat(buffer,"/bin/");
  }
  strcat(buffer,comando);

  if( pid == 0 ) {
    if( execv(buffer,args) == -1 ){
      printf("%s: command not found. plz Wake Up!\n", comando);
      exit(1);
    }
    // getcwd(PWD,maxln_Com_Amb);
  } else {
    if( background ) {
      printf("[PID] %d\n",pid);
    } else {
      wait(NULL);
      printf("\n");
    }
  }
}


int main(void) {
  int ready=1;

  strcpy(PATH,getenv("PATH"));
  getcwd(PWD,maxln_Com_Amb);

  uid_t uid = geteuid();
  struct passwd *pw = getpwuid(uid);
  strcpy(USER,pw->pw_name);
  
  do {
    printf("\033[0;31m");
    printf("%s", USER);
    printf("\033[0;36m");
    printf(": %s> ", PWD);
    printf("\033[0m");
    fflush(stdin);
    memset(comando,'\0',maxln_Com_Amb);
    scanf(" %[^\n]s",comando);

    if( strlen(comando) > 0 ){
      int paramsLen = parseCommand();

      if(strcmp(comando, "quit") == 0) {
        ready = 0;
      } else {
      if (strcmp(args[paramsLen - 1], "&") == 0) executeCommand(1); else executeCommand(0);
        
      }
    }

  } while (ready);
  return 0;
}