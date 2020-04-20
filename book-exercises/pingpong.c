#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<sys/wait.h>
#include<sys/timeb.h>
#include<stdlib.h>

// #define DEBUG

int main(int argc, char *argv[]){

  char ball;
  pid_t child_pid;
  int loops = 16;
  int i;
  int pipefd_p[2];
  int pipefd_c[2];
  struct timeb tb_ini, tb_end;

  if(argc == 2){
    loops = atoi(argv[1]);
  }

  if(pipe(pipefd_p) == -1){
    perror(NULL);
    return -1;
  }

  if(pipe(pipefd_c) == -1){
    perror(NULL);
    return -1;
  }

  child_pid = fork();
  if(child_pid == 0){
    close(pipefd_p[1]);
    close(pipefd_c[0]);
    ftime(&tb_ini);
    i = loops;
    for(;i-->0;){
        ball = 'p';
        write(pipefd_c[1], &ball, 1);
        read(pipefd_p[0], &ball, 1);
 #ifdef DEBUG
        fprintf(stderr, "On parent, got: %c\n", ball);
 #endif
    }
    wait(NULL);
    ftime(&tb_end);
    printf("Took %ldms for %d exchanges\n",
           (long)((tb_end.time-tb_ini.time)*1000 + (tb_end.millitm - tb_ini.millitm)), loops);
    close(pipefd_c[1]);
    close(pipefd_p[0]);
  }else{
    close(pipefd_c[1]);
    close(pipefd_p[0]);
    for(;loops-->0;){
        read(pipefd_c[0], &ball, 1);
 #ifdef DEBUG
        fprintf(stderr, "On child, got: %c\n", ball);
 #endif
        ball = 'c';
        write(pipefd_p[1], &ball, 1);
    }
    close(pipefd_p[1]);
    close(pipefd_c[0]);
  }
  return 0;
}
