#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

void alarm_handler(int signo){	printf("Received signal %d\n", signo);	}

void wait_for_signal(){
	signal(SIGALRM, alarm_handler);
	pause();
	printf("Continuing...\n");	
}

void provide_signal(){
		printf("Waiting for signal.\n");
		sleep(5);
		kill(getppid(), SIGALRM);
		exit(0);
}

int write_out(int i, int fd, char *buf[]){
	if(write(fd, buf[i], strlen(buf[i])) != strlen(buf[i])){
		printf("Write error in %d.\n", getpid());
		return -1;
	}
	printf("Just wrote %s", buf[i]);
	return 0;
}

int main(int argc, char **argv){
	char *buf[30];
	int i = 0;
	buf[i++] = "EXAM! EXAM! EXAM!\n";
	buf[i++] = "HELP! HELP! HELP!\n";
	buf[i++] = "STUDY! STUDY! STUDY!\n";
	int fd = open(argv[1], O_CREAT | O_RDWR, 0755);	
	for(i = 0; i < 2; i++){
		if(fork() == 0){
			write_out(i, fd, buf);
			provide_signal();
			exit(0);
		}
		wait_for_signal();
	}
	write_out(i, fd, buf);
	sleep(5);
    close(fd);     
return 0;
}