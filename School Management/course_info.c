#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CourseInfo{	
	int courseID;
	char courseName[50];
	char courseCode[12];
	char Term [6];
};

typedef struct CourseInfo courseInfo; 

void loadCourseInfo(int id, courseInfo *c_info, char *input_lines);
void displayCourseInfo(courseInfo course[], int num_courses);
void addCourseInfo(courseInfo course[], int *num_courses);
void searchCourseInfo(courseInfo course[],int num_courses);

int main(void){

	int i,num_courses;
	char input_lines[200];
	courseInfo c_info, course[20];
	int choice;
	num_courses=0;
	while(scanf("%s",input_lines)!=EOF)
    {
        loadCourseInfo(num_courses+1,&course[num_courses],input_lines);
        num_courses++;
    }

    printf("ID\tNAME\tCODE\tTERM\t\n");
	for (i=0;i<num_courses;i++){
		printf("%d\t%s\t%s\t%s",course[i].courseID,course[i].courseName,course[i].courseCode,course[i].Term);
	}

	freopen("/dev/tty", "r", stdin);

	do{
		printf("Pick an option: \n");
		printf("1) Load Course Info\n2) Display Course Info\n3) Add Course Info\n4) Search Course Info\n5) Exit\n");
		scanf("%d",&choice);
		switch (choice){
				case 1: displayCourseInfo(course,num_courses);break;
				case 2: addCourseInfo(course,&num_courses);break;
				case 3: searchCourseInfo(course,num_courses);break;
				case 4: return 0;break;
		}
	printf("Pick an option: \n");
	printf("1) Load Course Info\n2) Display Course Info\n3) Add Course Info\n4) Search Course Info\n5) Exit\n");
	scanf("%d",&choice);
	}while(choice!=4);


return 0;
}

void loadCourseInfo(int id, courseInfo *c_info, char *input_lines){

	int i=0,j=0;
	int k,z;
	char *parts=NULL;
	char code[12];
	char term[6];
	if(input_lines){
			c_info->courseID=id;
			parts = strtok(input_lines,",");
			while(parts[i]!='\0'){
				parts[i]=toupper(parts[i]);
				i++;
	}
	
	strcpy(c_info->courseName,parts);

	parts = strtok(NULL, ",");
	strcpy(code,parts);
	parts = strtok(NULL, ",");
	strcpy(code+2,parts);
	strcpy(code+4, "-");
	parts = strtok(NULL, ",");
	strcpy(code+5,parts);
	strcpy(code+8,"-");
	parts = strtok(NULL, ",");
	strcpy(code+9,parts);

	/*for(k=0;k<num_courses;k++){
				if (strcmp(course[i].courseCode,code)==0){
					printf("Course code already exists, please change course information.");
					return 0;
				}
			}*/

	strcpy(c_info->courseCode,code);

	parts = strtok(NULL, ",");
	strcpy(term,parts);
	parts = strtok(NULL, ",");
	strcpy(term+1,parts);

	strcpy(c_info->Term,term);
	}

	else{
		printf("Data not found.\n");
	}
}

void displayCourseInfo(courseInfo course[], int num_courses){

	int i;
	printf("ID\tNAME\tCODE\tTERM\t\n");
	for (i=0;i<num_courses;i++){
		printf("%d\t%s\t%s\t%s",course[i].courseID,course[i].courseName,course[i].courseCode,course[i].Term);
	}
}

void addCourseInfo(courseInfo course[], int *num_courses){
	char input_lines[200];
	printf("Enter new course's information separated by commas.\n");
	scanf("%s",input_lines);
	loadCourseInfo(*num_courses+1,&course[*num_courses],input_lines);
	(*num_courses)++;
}

void searchCourseInfo(courseInfo course[],int num_courses){
	int option,i,j,c_id;
	char c_name[20];
	printf("Would you like to search using\n1) Course ID \n2) Course name?\n");
	scanf("%d",&option);
		switch(option){
			case 1: 
			printf("Enter the course ID to search.\n");
			scanf("%d",&c_id);
			for(i=0;i<num_courses;i++){
				if(course[i].courseID==c_id){
					printf("%d\t%s\t%s\t%s",course[i].courseID,course[i].courseName,course[i].courseCode,course[i].Term);
				}
			} break;

			case 2:
			printf("Enter the course name to search.\n");
			scanf("%s",c_name);
			for(j=0;j<num_courses;j++){
				if(strcmp(course[i].courseName,c_name)==0){
					printf("%d\t%s\t%s\t%s",course[i].courseID,course[i].courseName,course[i].courseCode,course[i].Term);
				}
			} break;
		}
}