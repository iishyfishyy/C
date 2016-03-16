#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char * argv []) {	

	if(argc != 3){
		printf("Insufficient arguments, use format: \"./a.out filetoopen.ppm filetowrite.ppm\"\n");
		exit(1);
	}
	
	//open files to read and to write
	FILE * fr = fopen(argv[1], "r+");		
	FILE * fw = fopen(argv[2], "w+");

	//declare needed variables
	int rows, cols, MAX, i, j, k, h;
	int pid, status;
	int num_one, num_two, average;

	//write first line out
	for (i = 0; i < 3; i++)
		fputc(fgetc(fr), fw);
	
	//read and write ppm metadata
	fscanf(fr, "%d%d", &cols, &rows );
	fscanf(fr, "%d", &MAX);	
	fgetc(fr);	
	fprintf(fw,"%d %d\n",cols * 2 - 1, rows * 2 - 1 );
	fprintf(fw,"%d\n", MAX);

	cols *= 3;
	int array [rows][cols];
	
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			fscanf(fr, "%d", &array[i][j]);
	
	//write numbers in rgb value area
	for (i = 0; i < rows; i++) {
		fflush(fw); //critical, must flush file output stream
		if ((pid = fork()) == 0) {
			for (j = 0; j < cols; j++) {				
				if ( (j % 3 == 0) && (j != 0) ) {
					for (k = 3, h = 0; k > 0; k--, h++)
						fprintf(fw,"%d ", ((array[i][j - k] + array[i][j + h])/2));
				}
				fprintf(fw,"%d ", array[i][j]);							
			}					
			fprintf(fw, "\n");	

			if (i != rows - 1)
				for (j = 0; j < cols; j++) {				
					if ( (j % 3 == 0) && (j != 0) ) {
						for (k = 3, h = 0; k > 0; k--, h++) {
							num_one = (array[i][j - k] + array[i + 1][j - k]) / 2;
							num_two = (array[i][j + h] + array[i + 1][j + h]) / 2;
							average = (num_one + num_two) / 2; // calculate average of rgb value
							fprintf(fw,"%d ", average);
						}	
					}
					fprintf(fw, "%d ", ((array[i][j] + array[i + 1][j]) / 2));
				}	
			fprintf(fw, "\n");
			
			exit(0);
		}
		else{
			wait(&status);
		}
	}		

	fclose (fr);
	fclose (fw);
	
	return 0;	
	
}	