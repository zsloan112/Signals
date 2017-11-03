#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

static int alarm_fired = 0;

void ding(int sig){
	alarm_fired = 1;
}

int main(){
	pid_t pid;
	sigset_t new_set;
	sigset_t old_set;
	struct sigaction act;

	memset(&act, 0, sizeof(act));

	act.sa_handler = ding;

	if(sigaction(SIGALRM, &act, 0)){
		perror("Sigaction error");
	}

	sigemptyset(&new_set);
	sigaddset(&new_set, SIGALRM);
	printf("Alarm application starting!\n");

	pid = fork();
	switch(pid){
		case -1:
			perror("Fork Falied");
			exit(1);
		case 0: //Child Process
			sleep(5);
			kill(pid, SIGALRM);
			exit(0);
	}


	printf("Waiting for alarm to go off\n");

	pause();
	if(alarm_fired)
		printf("Ding!\n");

	printf("Done..\n");
	exit(0);


}