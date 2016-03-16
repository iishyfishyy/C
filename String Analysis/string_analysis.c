#include <stdio.h>
#include <string.h>
 

void letterAnalysis(int,char[][81] );
int wordLengthAnalysis(int,char[][81],int );
void wordAnalysis(char[][81],int);

int main (void) 
{
	char stringarray[10][81];
	int numline,r,wordlent;
	int wordcount;
   
	scanf("%d",&numline);
	for(r=0;r<=numline;r++){
		fgets(stringarray[r+1],81,stdin);
	}
   
	letterAnalysis(numline,stringarray);
   
	for(wordlent=1;wordlent<=20;wordlent++){
		wordcount=wordLengthAnalysis(numline,stringarray,wordlent);
		printf("number of words with length %d = %d\n",wordlent,wordcount);
	} 
   
	wordAnalysis(stringarray,numline);

return 0;
}

void letterAnalysis(int numline,char stringarray[][81] )
{ 
	int num[26],r;
	char check;
	int y,z,c;
	for (z=0;z<26;z++)
		num[z]=0;

	for(z=0,check=97;z<26,check<123;z++,check++){
			for (r=0;r<=numline;r++){
				for (c=0;c<81;c++){
					if ( stringarray[r+1][c] == check||stringarray[r+1][c] == check-32 ){
						num[z]++;
					}		
				if(stringarray[r+1][c]=='\0')
              break;
         }
      }

	printf("%c: %d\n",check,num[z]);

	}
}
    

int wordLengthAnalysis(int numline,char stringarray[][81],int wordlent)
{
	int r,count=0;
	char temp[81];
	char *ptr;
	for(r=0;r<=numline;r++)
	{
		strcpy(temp,stringarray[r+1]);
		ptr=strtok(temp," \n");
		while(ptr!=NULL)
		{
			if(strlen(ptr)==wordlent)
				count++;  
		ptr=strtok(NULL," \n");
		}
	} 
return count;
}


void wordAnalysis(char stringarray[][81],int numline)
{
	int r,c,count=0;
	int numword=0;
	char *ptr,temp1[100][81];
	char temp[81],check[81];
	for (r=0;r<=numline;r++)
	{
		strcpy(temp,stringarray[r+1]);
		ptr=strtok(temp," \n");
		while(ptr!=NULL)
		{
			strcpy(temp1[numword],ptr);
			numword++;
			ptr=strtok(NULL," \n");
		}
	}
	for(c=0;c<numword;c++)
	{  
		strcpy(check,temp1[c]);
		if (c == 0)
			count++;
		for(r=0; r < numword; r++)
		{
			if(!strcmp(check,temp1[r+1]))
				count++;
		}
		printf(" the word %s appeared %d times \n",check,count);
		count = 0;
	}
}