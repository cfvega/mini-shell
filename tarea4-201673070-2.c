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
  char *token = strtok(comando, " ");
  for(i = 0; i < (max_args - 1); i++) args[i] = NULL;
  
  i=0;
  while(token != NULL && i < (max_args - 2)) {
    args[i] = token;
    i++;
    token = strtok(NULL, " ");
  }
  return i;
}

int checkPath() {
  int ok = 1;
  for(int i = 0; i<strlen(comando) ;i++) {
    char *r_position_ptr = strrchr("^/", comando[i]);
    if(r_position_ptr != NULL) {
      ok = 0;
      break;
    }
  }
  return ok;
}

void executeCommand( int background ) {
  int pid = 0;
  char buffer[100]="";
  pid = fork();

  if( checkPath() ) {
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
  printf("Mini-Shell INF246 2020-1\n");
  printf("(c) Claudio Vega Lagos. Tarea 2\n\n");
  
  do {
    printf("\033[1;32m");
    printf("%s", USER);
    printf("\033[0;33m");
    printf(": %s> ", PWD);
    printf("\033[0;36m");
    fflush(stdin);
    memset(comando,'\0',maxln_Com_Amb);
    scanf(" %[^\n]s",comando);

    if( strlen(comando) > 0 ){
      int paramsLen = parseCommand();

      if(strcmp(comando, "quit") == 0 || strcmp(comando, "exit") == 0 || strcmp(comando, "logout") == 0 || strcmp(comando, "!q") == 0) {
        ready = 0;
      } else {
        if (strcmp(args[paramsLen - 1], "&") == 0) executeCommand(1); else executeCommand(0);
      }
    }

  } while (ready);
  return 0;
}