#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "journal.h"


int write(struct journal* temp1)
{
	// Open the fault tolerant file and make an update( put it in maintainence mode)
	//printf("In write\n");
	FILE *filepointer;
	filepointer=fopen("handle.txt","w");
	if(filepointer==NULL)
	{
      		printf("Error in creating/opening the file!");
      		return false;
		
   	}
	fprintf(filepointer,"block\n");
	fclose(filepointer);
	// fault handle code end


	struct journal* temp2;
	temp2=(struct journal *)malloc(sizeof(struct journal));
	temp2 = temp1;
	
	//int counter=global_counter;
	//char temp[1000];
   	char basename[100];
	char variable[100];
	//printf("%s\n",temp1->value);
	// vkl
	int counter;
	counter = temp2->actionID;
	strcpy(basename,"journal");
	sprintf(variable, "%d", counter);
	strcat(basename,variable);
	strcat(basename,".txt");
	//printf("%s\n",basename);
	
	FILE *filepointer1;
	filepointer1 = fopen("tracker.txt", "a");
	if( filepointer1 == NULL )
   	{
      		perror("Error while opening the tracker file.\n");
      		return false;
   	}
	//printf("%s\n",basename);
	fprintf(filepointer1,"%s\n",basename);
	fclose(filepointer1);
	// Open and write to the file
	FILE *fptr;
	fptr=fopen(basename,"w");
	if(fptr==NULL)
	{
      		printf("Error in creating the file!");
      		return false;
		
   	}

	//fgets(temp, sizeof(temp), stdin);
	//gets(temp);
	//strcpy(temp,"journaltext");
	// commit
 
	//int value;
	//value = data;
	fprintf(fptr,"%d\n",temp2->actionID);
   	fprintf(fptr,"%s\n",temp2->value);
	fprintf(fptr,"%s\n",temp2->recordStatus);
   	fclose(fptr);
	char v[10];
	char compare[10] = "yes\n";
		
	
	printf("Do you want to introduce a fault and exit(yes/no)\n");
	fgets(v,10,stdin);
	//printf("%s\n",v);
	if(strcmp(compare,v)==0)
	{
		printf("Creating a fault.\n fault happened\n");
		exit(0);
	} 
	
	// Open file handle and mark it as allow
	FILE *filepointer2;
	filepointer2=fopen("handle.txt","w");
	if(filepointer2==NULL)
	{
      		printf("Error in creating/opening the file!");
      		return false;
		
   	}
	
	fprintf(filepointer2,"allow\n");
	fclose(filepointer2);
	
	// done handle code
	return temp2->actionID;
}
