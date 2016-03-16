#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

void player(char *, int *, int *);

int main(int argc, char ** argv){

	int fd1[2], fd2[2], fd3[2], fd4[2], fd5[2], fd6[2], fd7[2], fd8[2], fd9[2], fd10[2];
	char turn = 'T';

	printf("This is a 5 player game with a referee.\n");
	if(pipe(fd1) < 0)
		printf("Pipe error on fd1\n");
	if(pipe(fd2) < 0)
		printf("Pipe error on fd2\n");
	if(!fork())
		player("TOTO", fd1, fd2);
	close(fd1[0]); //close fd1 read channel, fd1 will write to fd2
	close(fd2[1]); //close fd2 write channel, fd2 will read from fd1

	if(pipe(fd3) < 0)
		printf("Pipe error on fd3\n");
	if(pipe(fd4) < 0)
		printf("Pipe error on fd4\n");
	if(!fork())
		player("TITI", fd3, fd4);
	close(fd3[0]); //close fd3 read channel, fd3 will write to fd4
	close(fd4[1]); //close fd4 write channel, fd4 will read from fd3	

	if(pipe(fd5) < 0)
		printf("Pipe error on fd5\n");
	if(pipe(fd6) < 0)
		printf("Pipe error on fd6\n");
	if(!fork())
		player("TATA", fd5, fd6);
	close(fd5[0]); //close fd3 read channel, fd3 will write to fd4
	close(fd6[1]); //close fd4 write channel, fd4 will read from fd3	

	if(pipe(fd7) < 0)
		printf("Pipe error on fd7\n");
	if(pipe(fd8) < 0)
		printf("Pipe error on fd8\n");
	if(!fork())
		player("TETE", fd7, fd8);
	close(fd7[0]); //close fd3 read channel, fd3 will write to fd4
	close(fd8[1]); //close fd4 write channel, fd4 will read from fd3	

	if(pipe(fd9) < 0)
		printf("Pipe error on fd9\n");
	if(pipe(fd10) < 0)
		printf("Pipe error on fd10\n");
	if(!fork())
		player("TUTU", fd9, fd10);
	close(fd9[0]); //close fd3 read channel, fd3 will write to fd4
	close(fd10[1]); //close fd4 write channel, fd4 will read from fd3	

	while(1){
		printf("\nReferee: TOTO plays\n\n");
		write(fd1[1], &turn, 1);
		read(fd2[0], &turn, 1);
		printf("\nReferee: TITI plays\n\n");
		write(fd3[1], &turn, 1);
		read(fd4[0], &turn, 1);
		printf("\nReferee: TATA plays\n\n");
		write(fd5[1], &turn, 1);
		read(fd6[0], &turn, 1);
		printf("\nReferee: TETE plays\n\n");
		write(fd7[1], &turn, 1);
		read(fd8[0], &turn, 1);
		printf("\nReferee: TUTU plays\n\n");
		write(fd9[1], &turn, 1);
		read(fd10[0], &turn, 1);
	}
return 0;
}

void player(char *s, int fd1[2], int fd2[2]){
	int points = 0;
	int dice;
	char turn;
	srand((unsigned) (time(NULL)+fd1[1]));

	close(fd1[1]);
	close(fd2[0]);
	while(1){
		read(fd1[0], &turn, 1);
		printf("%s: playing my dice\n", s);
		dice = rand() % 10 + 1;
		printf("%s: got %d points\n", s, dice);
		points += dice;
		printf("%s: total so far %d\n\n", s, points);
		if(points > 50){
			printf("%s: game over; I won\n", s);
			kill(0, SIGTERM);
		}
		sleep(1);
		write(fd2[1], &turn, 1);
	}
}