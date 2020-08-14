#include "functions.h"

int main(void) {
  int ready=1;

  getcwd(PWD,max_lines);

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
    memset(command,'\0',max_lines);
    scanf(" %[^\n]s",command);

    if( strlen(command) > 0 ){
      int paramsLen = parseCommand();
      // printf("%s",command);

      if(strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0 || strcmp(command, "logout") == 0 || strcmp(command, "!q") == 0) {
        ready = 0;
      } else if( strcmp(command, "help") == 0 || strcmp(command, "!h") == 0 ) {
        showHelp();
      } else if( strcmp(command, "credits") == 0 || strcmp(command, "!c") == 0 ) {
        showCredits();
      } else if(strcmp(command, "!x") == 0){
        continue;
      }else{
        if (strcmp(args[paramsLen - 1], "&") == 0) executeCommand(1); else executeCommand(0);
      }
    }

  } while (ready);
  return 0;
}