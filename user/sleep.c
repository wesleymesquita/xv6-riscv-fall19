#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
//#include "kernel/syscall.h"

int
main(int argc, char *argv[]){
	uint nmsec;
	if(argc < 2){
		printf("Error: usage : slee <num>");
		exit();	
	}
	nmsec = atoi(argv[1]);
	sleep(nmsec);		

	exit();
}

