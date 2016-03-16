#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int main(int argc, char **argv){

	int fd = open("storage", O_RDWR, 0755); //open storage for read write
	char num[2]; //create an array of characters to read the number (ascii encoded) into

	if(read(fd, &num, sizeof(num)) != sizeof(num))
		printf("Read improper bytes from storage. Program still works.\n");

	int intnum = atoi(num); //convert num to integer so we can subtract it by 3
	intnum -= 3; //like this

	close(fd); //close the file, we will reopen it

	fd = open("storage", O_TRUNC | O_RDWR , 0755); //reopen the file, but this time we include the O_TRUNC instruction to overwrite
	sprintf(num, "%d", intnum); //sprintf converts integer to char

	if(write(fd, num, strlen(num)) != strlen(num)) //write back the number (ascii encoded)
		printf("Error writing number to file.\n");

	close(fd); //close the file, we are done

	int s;
	pid_t pid = fork();
	if(pid == 0){
		execl("/home/ishyfishyy/Documents/school/CS256/assignment3/producer", "./producer", (char *)0); //make the child run the producer bash script
			  //don't forget to change the location to where the producer script is located
	} else {
		waitpid(pid, &s, 0);
		exit(0);
	}

	exit(0);
}