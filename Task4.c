#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>


void sig_handler(int signum){
	if(signum == SIGUSR1){
		printf("Hi Honey! Anything wrong?\n");
	}else if(signum == SIGUSR2){
		printf("Do you make trouble again?\n");
	}
}


int main(){
	pid_t pid;
	pid_t pid2;
	int status;
	pid = fork();
	signal(SIGUSR1, sig_handler);

	signal(SIGUSR2, sig_handler);

	if(pid != 0){
		//Parent
		
	}else{
		pid2 = fork();

		if(pid2 != 0){
			//Child 1
			
			//printf("Child #1\n");
			//waitpid(pid2, NULL, 0);
			kill(pid2, SIGUSR1);
			
		}else{
			//Child2
			waitpid(pid2, NULL, 0);
			//printf("Child #2\n");
			kill(pid2, SIGUSR2);
		}
	}
}