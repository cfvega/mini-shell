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
char *const envParms[2] = {"STEPLIB=SASC.V6.LINKLIB", NULL};


int parseCommand(){
  int i;
  for(i=0;i<(max_args-1);i++) args[i]=NULL;
  strtok(comando," "), i=0;
  args[i]=comando;
  while((args[++i]=strtok(NULL," "))!=NULL && i<(max_args-2));
  return i;
}

void executeCommand( int background ){
  int pid = 0;
  char buffer[100]="";

  pid = fork();
  // printf("%s",); 
  if( strchr(comando,'.') == NULL ) {char buffer[100]="/bin";} else {char buffer[100]="";}
  // printf("%d", pid);
  strcat(buffer,comando);
  if( pid == 0 ) {
    execv(buffer,args);
    // wait(getppid());
    // if( !execvp(buffer,args) ){
    //   exit(1);
    // }
  // getcwd(PWD,maxln_Com_Amb);

  } else {
    wait(NULL);
  }


}


int main(void){
  int ready=1;


  strcpy(PATH,getenv("PATH"));
  getcwd(PWD,maxln_Com_Amb);

  uid_t uid = geteuid();
  struct passwd *pw = getpwuid(uid);
  strcpy(USER,pw->pw_name);
  
  do {
    printf(" %s: %s> ", USER, PWD);
    fflush(stdin);
    memset(comando,'\0',maxln_Com_Amb);
    scanf(" %[^\n]s",comando);

    if( strlen(comando) > 0 ){
      int params = parseCommand();
      if(strcmp(comando, "quit") == 0) {
        ready = 0;
      } else {
      if (strcmp(args[params - 1], "&") == 0) executeCommand(1); else executeCommand(0);
        
      }
    }


  } while (ready);
  return 0;
}