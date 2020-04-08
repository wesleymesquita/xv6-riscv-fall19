#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
	int p, n, i;
	int pp[2];
	int read_from;
	int write_to;
	p = 2;	
	read_from = -1;

	for(;;){
		if(p >= 35){
			exit();
		}
		printf("%d\n", p);
		pipe(pp);
		write_to = pp[1];
		int pid = fork();
		if(pid !=  0)	{
			//printf("---> PAI PID:%d READP:%d WRITEP:%d\n", getpid(), pp[0], pp[1]);
			if(p == 2){
				i = p;
				while(i++<=35){
					if(i%2 == 1)
						write(write_to, &i, sizeof(int));
				}
			}else{
				while(read(read_from, &n, sizeof(int)) > 0){
					if(n%p != 0){
						//printf("p == %d n == %d\n", p, n);
						write(write_to, &n, sizeof(int));
					}
				}
				close(read_from);
			}
			close(write_to);
			wait();
		}else{
			// printf("---> FILHO PID:%d READP:%d WRITEP:%d\n", getpid(), pp[0], pp[1]);
			read_from = pp[0];
			if(read(read_from, &p, sizeof(int)) == 0){
				exit();
			}
		}
	}
}
