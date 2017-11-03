#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <signal.h>
#include <string.h>


void hd1(int sig){
	signal(SIGQUIT, SIG_DFL);
}


int main(){
	sigset_t new_set;
	sigset_t int_set;

	sigemptyset(&int_set);
	sigaddset(&int_set, SIGQUIT);

	sigemptyset(&new_set);
	sigaddset(&new_set, SIGINT);
	sigaddset(&new_set, SIGQUIT);

	sigprocmask(SIG_BLOCK, &new_set, NULL);

	for(int i = 1; i <= 5; i++){
		printf("%d\n", i);
		sleep(1);
	}

	signal(SIGINT, hd1);
	signal(SIGQUIT, hd1);

	sigprocmask(SIG_UNBLOCK, &new_set, NULL);
	
	sigdelset(&new_set, SIGQUIT);


	for(int i = 1; i <= 5; i++){
		printf("%d\n", i);
		sleep(1);
	}
}