#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>

void player(char *, int *, int *);

int main(int argc, char ** argv){

	int fd[atoi(argv[1]) * 2][2];
	char turn = 'T';

	printf("This is a %s player game with a referee.\n", argv[1]);
	int i = 0;
	for(i = 0; i < atoi(argv[1]) * 2; i = i + 2){
		if(pipe(fd[i]) < 0)
			printf("Pipe error on fd[%d]\n", i);
		if(pipe(fd[i+1]) < 0)
			printf("Pipe error on fd[%d]\n", i+1);
		if(!fork()){
			char playername[20] = "Player ";
			char buf[3];
			int temp = (i / 2) + 1;
			sprintf(buf, "%d", temp);
			strcat(playername, buf);
			player(playername, fd[i], fd[i+1]);
		}
		close(fd[i][0]);
		close(fd[i+1][1]);
	}

	while(1){
		for(i = 0; i < atoi(argv[1]) * 2; i = i + 2){
			char playername[20] = "Player ";
			char buf[3];
			int temp = (i / 2) + 1;
			sprintf(buf, "%d", temp);
			strcat(playername, buf);
			printf("\nReferee: %s plays\n\n", playername);
			write(fd[i][1], &turn, 1);
			read(fd[i+1][0], &turn, 1);
		}
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