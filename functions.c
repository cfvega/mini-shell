#include "functions.h"

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
void showHelp(){
    printf("HELP\n");
    printf("!q, exit, logout, quit: Cerrar Mini-Shell\n");
    printf("help: Opciones disponibles\n");
    // printf("HELP\n");
}

void showCredits(){
    printf("Mini-Shell\n");
    printf("Tarea Nro. 2 para Sistemas Operativos INF 246\n");
    printf("Semestre Otoño 2020 \n");
    printf("Prof. Dr. Hdr. Xavier Bonnaire\n");
    printf("--------------------------\n");
    printf("Claudio Vega Lagos\n");
    printf("201673070-2\n");
    printf("claudiov.lagos@gmail.com\n");
    // printf("HELP\n");
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