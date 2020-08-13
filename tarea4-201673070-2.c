#include "functions.h"

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
      } else if( strcmp(comando, "help") == 0 || strcmp(comando, "!h") == 0 ) {
        showHelp();
      } else if( strcmp(comando, "credits") == 0 || strcmp(comando, "!c") == 0 ) {
        showCredits();
      } else{
        if (strcmp(args[paramsLen - 1], "&") == 0) executeCommand(1); else executeCommand(0);
      }
    }

  } while (ready);
  return 0;
}