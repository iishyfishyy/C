#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

void writeNum(int fw, char numholder[]);

int main(void){

	//open files for read & write
	int fd = open("ppmtext.ppm", O_RDONLY);
	int fw = open("ppmbinary.ppm", O_CREAT | O_RDWR, 0755);

	//error if file(s) could not be opened
	if(fd < 0 || fw < 0)
		printf("Error opening ppmtext.ppm or ppmbinary.ppm.\n");
	
	//array to hold file data
	char data[750];
	int i, newlinecount = 0, rows;

	//loop to handle the first three lines, and to change P3 to P6
	for(i = 0; newlinecount < 3; ++i){		
		if(read(fd, &data[i], sizeof(char)) != sizeof(char))
			printf("Error reading char at %d from file.\n", i);
		if(data[i] == '\n')
			newlinecount++;
		if(newlinecount == 0 && data[i] == '3')
			data[i] = '6';
		if(newlinecount == 1 && data[i-1] == '\n')
			rows = data[i] - '0';
		if(write(fw, &data[i], sizeof(char)) != sizeof(char))
			printf("Error writing char at %d to file.\n", i);
	}

	newlinecount = 0;
	
	char numholder[3];
	int number, j, holder_index = 0;

	//initialize all numholder[] values to x for identification
	for(j = 0; j < 3; ++j)
		numholder[j] = 'x';	

	//handle the rest of the data
	for(i = i; newlinecount < rows; ++i){
		if(read(fd, &data[i], sizeof(char)) != sizeof(char))
			printf("Error reading char at %d.\n", i);
		//if newline occurs, write values of numholder to file		
		if(data[i] == '\n'){
			writeNum(fw, numholder);
			newlinecount++;
			//reset values of numholder to x
			for(j = 0; j < 3; ++j)
				numholder[j] = 'x';
			holder_index = 0;
			continue;		
		}		
		//if space occurs, previous number has been recorded, write values
		if(data[i] == ' '){
			writeNum(fw, numholder);
			//reset numholder to x
			for(j = 0; j < 3; ++j)
				numholder[j] = 'x';			
			holder_index = 0;
			continue;		
		}
		//this case handles the single 0 value
		if(data[i] == '0' && data[i-1] == ' '){
			int zero = 0;
			if(write(fw, &zero, sizeof(zero)/sizeof(int)) != sizeof(zero)/sizeof(int))
				printf("Error writing \' \' to file.\n");
			continue;			
		}
		//if no previous cases match, data[i] is a number. insert into numholder.
		if(holder_index < 3){
			numholder[holder_index] = data[i];
			holder_index++;
		} else {
			printf("Error: value of holder_index improper.\n");
		}
	}

	close(fd);
	close(fw);

	return 0;
}

//convert number from char array to integer
void writeNum(int fw, char numholder[]){
	int i;
	int number = 0;
	for(i = 0; i < 3; ++i){
		//only work with values if numholder has a number
		if(numholder[i] != 'x') {
			//maximum value is 255 (3 digits), multiply with appropriate power
			if(i == 0){
				number += ((numholder[i]-'0')*100); }
			else if (i == 1) {
				number += ((numholder[i]-'0')*10); }
			else {
				number += ((numholder[i]-'0')*1); }
		}
	}
	//if number is still 0, this function was run accidentally or in a special case. ignore everything
	if(number != 0){
		if(write(fw, &number, sizeof(number)/sizeof(int)) != sizeof(number)/sizeof(int))
			printf("Error writing \' \' to file.\n");
	}
}