#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/syscall.h"

int
main(int argc, char *argv[]){
	
	printf("Ticks from uptime %d\n", uptime());

	exit();
}
