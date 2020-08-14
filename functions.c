#include "functions.h"

int parseCommand() {
  int i;
  char *token = strtok(command, " ");
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
  for(int i = 0; i<strlen(command) ;i++) {
    char *r_position_ptr = strrchr("^/", command[i]);
    if(r_position_ptr != NULL) {
      ok = 0;
      break;
    }
  }
  return ok;
}
void showHelp(){
    printf("###### HELP #####\n");
    printf("---------------\n");
    printf("\033[1;36m");
    printf("!q, exit, logout, quit: ");
    printf("\033[0;36m");
    printf("Cerrar Mini-Shell\n");
    printf("\033[1;36m");
    printf("!x: ");
    printf("\033[0;36m");
    printf("Saltar una linea en consola\n");
    printf("\033[1;36m");
    printf("!h, help: ");
    printf("\033[0;36m");
    printf("Opciones disponibles\n");
    // printf("HELP\n");
}

void showCredits(){
    printf("\033[1;31m");
    printf("Mini-Shell\n");
    printf("\033[0;36m");
    printf("Tarea Nro. 2 para Sistemas Operativos INF 246\n");
    printf("Semestre Otoño 2020 \n");
    printf("Prof. Dr. Hdr. Xavier Bonnaire\n");
    printf("--------------------------\n");
    printf("\033[1;36m");
    printf("Claudio Vega Lagos\n");
    printf("201673070-2\n");
    printf("claudiov.lagos@gmail.com\n");
    printf("\033[0;36m");
}

void executeCommand( int background ) {
  int pid = 0;
  char buffer[100]="";
  pid = fork();

  if( checkPath() ) {
    strcat(buffer,"/bin/");
  }
  strcat(buffer,command);

  if( pid == 0 ) {
    if( execv(buffer,args) == -1 ){
      printf("%s: command not found. plz Wake Up!\n", command);
      exit(1);
    }
    // printf("\n");
    // getcwd(PWD,maxln_Com_Amb);
  } else {
    if( background ) {
      printf("[PID] %d\n",pid);
      printf("\033[1;31m");
      printf("After execute, enter crl\n");
      printf("\033[0;36m");
    } else {
      wait(NULL);
    }
  }
}