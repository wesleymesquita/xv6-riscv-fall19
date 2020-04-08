#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int
main(int argc, char *argv[]){
    int pid, i;
    char cmd[16];
    char *arg[MAXARG];
    int default_cmd = 1;
    if(argc == 1){
        strcpy(cmd, "echo");
        default_cmd = 0;
    }
    else{
        strcpy(cmd, argv[1]);
    }
    arg[0] = malloc(strlen(cmd)+1);
    strcpy(arg[0], cmd);
    for(i=default_cmd+1; i<argc; i++){
      arg[i-default_cmd] = (char*)malloc(strlen(argv[i])+1);
      strcpy(arg[i-default_cmd], argv[i]);
    }

    pid = fork();
    if(pid == 0){
      printf("[DEBUG] : On child and will execute %s\n", cmd);
      for(i=0; i<argc-default_cmd-1; i++){
        printf("[DEBUG] arg %d == %s\n", i, arg[i]);
      }
      exec(cmd, arg);
    }
    else{
      printf("[DEBUG] : On parent and waiting \n");
      wait();
      printf("[DEBUG] : On parent and waited \n");
    }

    exit();
}
