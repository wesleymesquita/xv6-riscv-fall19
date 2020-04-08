#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/syscall.h"

int
main(int argc, char *argv[]){
	int p[2];
	pipe(p);
	
	int pid = fork();	
	char buf[4];

	if(pid > 0){
		strcpy(buf, "ping");
		write(p[1], buf, 4);
		sleep(50);
		read(p[0], buf, 4);
		printf("%d : received  on parent %s\n", getpid(), buf);
	}else if(pid == 0){
		read(p[0], buf, 4);
		printf("%d: received on child %s\n", getpid(), buf);
		strcpy(buf, "pong");
		write(p[1], buf, 4);
	}else{
		printf("Error. Could not fork\n");
	}

	exit();
}
