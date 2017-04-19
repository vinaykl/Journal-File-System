#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "journal.h"


int commit(int dataId)
{
	// Fault handling
	FILE *filepointer3;
	filepointer3=fopen("handle.txt","w");
	if(filepointer3==NULL)
	{
      		printf("Error in creating/opening the file!");
      		return false;
		
   	}
	fprintf(filepointer3,"block\n");
	fclose(filepointer3);
	// fault handling end.
	int i;
	char valueS[100];
	char files[10][100];
	char status[100];
	// get the number of files
	FILE *filepointer;
	filepointer = fopen("tracker.txt", "r");
	if( filepointer == NULL )
   	{
      		printf("Error while opening the tracker file.\n");
      		return -1;
   	}
 
   	//printf("Tracker file is opened\n");			
 	// contents of the file tracker.txt 
	int nofiles,j;
	char ch;
	nofiles=0;
	j=0;
   	while( ( ch = fgetc(filepointer) ) != EOF )
		{
			do
			{
				files[nofiles][j] = ch;
            			j++;
      				//printf("%c\n",ch);
			}while((ch=fgetc(filepointer))!='\n');
			files[nofiles][j]='\0';
			nofiles++;
			//printf("\n");
			j=0;
		}
	// print the contents of file
	//printf("Tracker file contains :\n");
	for ( i=0; i< nofiles ; i++)
	{
		//printf("%s\n",files[i]);
	}
	fclose(filepointer);

	//
	// get the dataId which matches the actionId in file
	for (i=0;i<nofiles;i++)
	{
		// open file pointer for every file in tracker till we get what we want.
		FILE *filepointer1;
		filepointer1 = fopen(files[i], "r");
		if( filepointer1 == NULL )
   		{
      			printf("Error while opening the journal file.\n");
      			return -1;
   		}
		// get the corresponding file and save the value
		struct journal* v;
		v=(struct journal *)malloc(sizeof(struct journal));
		char contents[10][100];
		int vkl,arglength;
		vkl=0;
		arglength=0;
		char c;
		//printf("I am here \n");
		while( ( c = fgetc(filepointer1) ) != EOF )
		{
			do
			{
				contents[vkl][arglength] = c;
            			arglength++;
      				//printf("%c\n",c);
			}while((c=fgetc(filepointer1))!='\n');
			contents[vkl][arglength]='\0';
			vkl++;
			//printf("\n");
			arglength=0;
		}
		//printf("I am here 2\n");
		int vinaynum;
		vinaynum = atoi(contents[0]);
		v->actionID = vinaynum;
		//int vinay;
		//vinay= atoi(contents[1]);
		//v->value = vinay;
		strcpy(v->value,contents[1]);
		strcpy(v->recordStatus,contents[2]);
		
		if ( v->actionID == dataId)
		{
			//valueS=v->value;
			//printf("I am here\n");
			strcpy(valueS,v->value);
			strcpy(status,v->recordStatus);
			break;
		}
		//value
	}
	if(strcmp(status,"aborted")==0)
	{
		printf("cannot commit an action which is already aborted\n");
		return -2;
	}
	struct journal* temp2;
	temp2=(struct journal *)malloc(sizeof(struct journal));
	temp2->actionID = dataId;
	//temp2->value=valueS;
	strcpy(temp2->value,valueS);
	strcpy(temp2->recordStatus,"commited");
	FILE *fptr;
	// get the filename
	char basename[100];
	char variable[100];
	strcpy(basename,"journal");
	sprintf(variable, "%d", dataId);
	strcat(basename,variable);
	strcat(basename,".txt");
	//printf("%s\n",basename);
	// re write the file
	char v[10];
	char compare[10] = "yes\n";
	/*
	printf("Do you want to introduce a fault and exit(yes/no)\n");
	fgets(v,10,stdin);
	//printf("%s\n",v);
	if(strcmp(compare,v)==0)
	{
		printf("Creating a fault.\n fault happened\n");
		exit(0);
	} 

	*/
	fptr=fopen(basename,"w");
	if(fptr==NULL)
	{
      		printf("Error in creating the file!");
		return -1;
		
   	}
	fprintf(fptr,"%d\n",temp2->actionID);
   	fprintf(fptr,"%s\n",temp2->value);
	fprintf(fptr,"%s\n",temp2->recordStatus);
   	fclose(fptr);
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
	return 0;
}
