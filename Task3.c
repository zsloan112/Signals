#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
	pid_t pid;
	int foo = open("foo", O_RDWR | O_CREAT, 0666);
	char *message = "Hi, mom";
	int status;

	pid = fork();
	switch(pid){
		case -1:
			printf("Fork error\n");
			exit(1);
		case 0:
			//printf("Child Process..\n");
			//printf("Writing to foo\n");
			write(foo, message, 7);
			break;
		default:
			pid = wait(&status);
			lseek(foo, 0, SEEK_SET);
			
			char childMessage[7];
			//printf("Parent Process..\n");
				
			
			read(foo, childMessage, 7);
			printf("My son said %s\n", childMessage);
			
			break;

	}

	exit(0);
}