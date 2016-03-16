#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct courseInfo{
	int courseID;
	char courseName[30];
};

struct studentInfo{
		char studentID[10];
		char fname[20];
		char lname[25];
		int numcourses;
		struct courseInfo CourseInfo[10];
		struct studentInfo *next;
};

typedef struct studentInfo sinfo;

sinfo *head=NULL;
//required functions
void addStudent();
void deleteStudent();
void searchStudentID();
void searchStudentlName();
void displayStudentInfo();void displayStudentInfos();
void saveStudentInfo();
void loadStudentInfo();
void exits();
sinfo *newsinfo();
void toupperer(char name[], int);
int main(void){
	
	int option;
	
	do{
		
		printf("Please select one of the following options.\n");
		printf("1) Add Student\n2) Delete Student\n3) Search Student Last Name\n4) Search Student ID\n5) Display Student Info\n6) Save Student Info\n7) Load Student Info\n8) Exit\n");
		scanf("%d",&option);

		switch(option){
			case 1: addStudent();break;
			case 2: deleteStudent();break;
			case 3: searchStudentlName();break;
			case 4: searchStudentID();break;
			case 5: displayStudentInfos();break;
			case 6: saveStudentInfo();break;
			case 7: loadStudentInfo();break;
			case 8: exit(0);break;
			default: printf("Pick a valid choice. Thx.\n");
		}
	}while(option!=8);
}

void toupperer(char name[], int x){
	int i;
	i=0;

	name[i]=toupper(name[i]);

}

void addStudent(){
	
	char input[200];
	int cAttend;
	char sID[9];
	int i;
	int cID;
	
		sinfo *nsinfo=newsinfo();

		printf("Adding new student: \n");

		printf("Student ID: ");
		scanf("%s",sID);
		strcpy(nsinfo->studentID,sID);

		printf("First name: ");
		scanf("%s",input);
		toupperer(input,1);
		strcpy(nsinfo->fname,input);

		printf("Last name: ");
		scanf("%s",input);
		toupperer(input,1);
		strcpy(nsinfo->lname,input);

		printf("Number of courses attending: ");
		scanf("%d",&cAttend);
		nsinfo->numcourses=cAttend;
		
		for(i=0;i<cAttend;i++){
			printf("Course ID: ");
			scanf("%d",&cID);
			nsinfo->CourseInfo[i].courseID=cID;

			printf("Course Name: ");
			scanf("%s",input);
			strcpy(nsinfo->CourseInfo[i].courseName,input);
		}
}

void deleteStudent(){
	int i,j=0;
	sinfo *new, *old;
	char studID[10];
   
	printf("Insert student ID of student you would like to delete: ");
	scanf("%s",studID);
    
	old = NULL;
	
	for (new = head; new != NULL; old = new, new = new->next){
	
	if(strcmp(studID,new->studentID)==0){

		if (old = NULL){ 
			head = new->next;free(new);
		}
		else{ 
			old->next = new->next;free(new);
		}
		
			//free(new);
		return;
		}
	}
}

void searchStudentID(){

	int knt=0;
	char ID[9];
	sinfo *temp=head;
	printf("What ID would you like to search?\n");
	scanf("%s",ID);

	while(temp){
		if(strcmp(ID,temp->studentID)==0)
			knt++;
		temp=temp->next;
	}
	temp=head;
	while(temp){
		if(strcmp(ID,temp->studentID)==0){
			displayStudentInfo(temp);
		}
	temp=temp->next;
	}
}

void searchStudentlName(){

	int knt=0;
	char lastname[25];
	sinfo *temp=head;
	printf("What last name would you like to search?\n");
	scanf("%s",lastname);

	while(temp){
		if(strcmp(lastname,temp->lname)==0)
			knt++;
		temp=temp->next;
	}
	temp=head;
	while(temp){
		if(strcmp(lastname,temp->lname)==0){
			displayStudentInfo(temp);
		}
	temp=temp->next;
	}
}

void displayStudentInfo(sinfo *temp){
	int i=0;
	printf("%s\n",temp->studentID);
	printf("%s\n",temp->fname);
	printf("%s\n",temp->lname);
	printf("%d\n",temp->numcourses);
	for(i=0;i<temp->numcourses;i++){
	printf("%s ",temp->CourseInfo[i].courseName);
	printf("%d\n",temp->CourseInfo[i].courseID);}
}

void displayStudentInfos(){
	sinfo *temp=head;
	while(temp){
		displayStudentInfo(temp);
		temp=temp->next;
	}
}

void saveStudentInfo(){
	FILE *output;
	sinfo *temp=head;
	int i=0;
	if((output=fopen("inputStudents.txt","wb"))==NULL){
		printf("Can't open the output file.\n");
		exit(0);
	}
	while(temp){
		fprintf(output,"%s\n",temp->studentID);
		fprintf(output,"%s\n",temp->fname);
		fprintf(output,"%s\n",temp->lname);
		fprintf(output,"%d\n",temp->numcourses);
		for(i=0;i<temp->numcourses;i++){
		fprintf(output,"%s ",temp->CourseInfo[i].courseName);
		fprintf(output,"%d\n",temp->CourseInfo[i].courseID);}
		temp=temp->next;
	}
	fclose(output);
	printf("Student Info Save Successful.\n");
}

void loadStudentInfo(){
	FILE *input;
	int i=0;
    if(head){
        sinfo *temp = head;
        while(head){
            head = head->next;
            free(temp);
            temp = head;
        }
    }
    if ((input=fopen("inputStudents.txt","rb"))==NULL){
    	printf("File not valid.\n");
    	exit(0);
    }
    while(!feof(input)){
    	sinfo *nsinfo=newsinfo();

    	fscanf(input,"%s\n",nsinfo->studentID);
    	fscanf(input,"%s\n",nsinfo->fname);
    	fscanf(input,"%s\n",nsinfo->lname);
    	fscanf(input,"%d\n",&(nsinfo->numcourses));
    	for(i=0;i<nsinfo->numcourses;i++){
    	fscanf(input,"%s ",nsinfo->CourseInfo[i].courseName);
    	fscanf(input,"%d\n",&(nsinfo->CourseInfo[i].courseID));}
    }
    fclose(input);
}

void exits(){
	int z;
	printf("Press 1 to save and exit.\n");
	fflush(stdin);
	scanf("%d",&z);

	if (z==1){
		saveStudentInfo();
	}
exit(0);
}

sinfo *newsinfo(){
	sinfo *newzinfo;
	newzinfo=(sinfo *) malloc(sizeof(sinfo));
	newzinfo->next=NULL;

	if(head==NULL){
		head=newzinfo;
	}
	else{
		sinfo *temp=head;
		while(temp->next!=NULL){
			temp=temp->next;
		}
	temp->next=newzinfo;
	}
	return newzinfo;
}