#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "journal.h"

int handle_status()
{
	FILE *filepointer2;
	filepointer2 = fopen("handle.txt", "r");
	if( filepointer2 == NULL )
   	{
      		printf("Nothing is there to read in the Fault tolerant system.\n");
   	}
	char ch;
	char status[100];
	int i;
	i=0;
	while( ( ch = fgetc(filepointer2) ) != EOF )
	{
		status[i]=ch;
		i++;
	}
	status[i]='\0';
	printf("%s",status);
	fclose(filepointer2);
	// for the details of the file
	int k;
	char block[100]="block\n";
	char allow[100]="allow\n";
	//printf("%s",block);
	//k=strcmp(status,block);
	//printf("%d\n",k);
	if(strcmp(status,allow)==0)
	{
		// no fault has occured.Proceed
		//printf(" I am in allow\n");
		return 1;
	}
	else if(strcmp(status,block)==0)
	{
		return 0;
	}
}
void crash_unlock()
{
	FILE *filepointer;
		filepointer = fopen("tracker.txt", "r");
		if( filepointer == NULL )
   		{
			
      			printf("Nothing is there to read in the journal File system.\n");
			return;
   		}
 	
   		// vkl new
		char files[10][100];
		int nofiles,j,i;
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
		for ( i=nofiles-1; i>=0 ; i--)
		{
			//printf("%s\n",files[i]);
		}
		fclose(filepointer);
	
		for (i=nofiles-1;i>=0;i--)
		{
			// open file pointer for every file in tracker till we get what we want.
			FILE *filepointer1;
			filepointer1 = fopen(files[i], "r");
			//printf("%s\n",files[i]);
			if( filepointer1 == NULL )
   			{
      				perror("Error while opening the file-Fault handling.\n");
      				exit(EXIT_FAILURE);
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
		
			if ( strcmp(v->recordStatus,"commited")==0)
			{
				break;
			}
			else if (strcmp(v->recordStatus,"aborted")==0)
			{
				break;
			}
			else if(strcmp(v->recordStatus,"pending")==0)
			{
				struct journal* temp2;
				temp2=(struct journal *)malloc(sizeof(struct journal));
				temp2->actionID = vinaynum;
				strcpy(temp2->value,v->value);
				strcpy(temp2->recordStatus,"aborted");
				FILE *fptr;
				// get the filename
				char basename[100];
				char variable[100];
				strcpy(basename,"journal");
				sprintf(variable, "%d", vinaynum);
				strcat(basename,variable);
				strcat(basename,".txt");
			
				fptr=fopen(basename,"w");
				if(fptr==NULL)
				{
      					printf("Error in creating the file!");
		
   				}
				fprintf(fptr,"%d\n",temp2->actionID);
	   			fprintf(fptr,"%s\n",temp2->value);
				fprintf(fptr,"%s\n",temp2->recordStatus);
   				fclose(fptr);	
			//value
		
			}

		}	
		//  Open the file and make it as proper, after fault tolerance is done.
		FILE *filepointer3;
		filepointer3 = fopen("handle.txt", "w");
		if( filepointer3 == NULL )
   		{
      			printf("Nothing is there to read in the Fault tolerant system.\n");
   		}
		fprintf(filepointer3,"allow\n");
		fclose(filepointer3);	
}
void handle()
{
	//  Open the file to check if any fault occured.
	//printf("I am here\n");
	FILE *filepointer2;
	filepointer2 = fopen("handle.txt", "r");
	if( filepointer2 == NULL )
   	{
      		printf("Nothing is there to read in the Fault tolerant system.\n");
   	}
	char ch;
	char status[100];
	int i;
	i=0;
	while( ( ch = fgetc(filepointer2) ) != EOF )
	{
		status[i]=ch;
		i++;
	}
	status[i]='\0';
	//printf("%s",status);
	fclose(filepointer2);
	// for the details of the file
	int k;
	char block[100]="block\n";
	char allow[100]="allow\n";
	//printf("%s",block);
	//k=strcmp(status,block);
	//printf("%d\n",k);
	// extra code..
	int lock_s;
	lock_s = lock_read();
	if( lock_s == 0)
	{

	if(strcmp(status,allow)==0)
	{
		// no fault has occured.Proceed
		//printf(" I am in allow\n");
		return;
	}
	else if(strcmp(status,block)==0)
	{
		// code to read the journal file system recursively till you find last "commited" and make all the files with "pending" to "aborted"
		// open tracker. Get file names. check the status. If it is "pending" then make it "aborted".( fault handling)
		//printf(" I am inside block \n");
		FILE *filepointer;
		filepointer = fopen("tracker.txt", "r");
		if( filepointer == NULL )
   		{
			
      			printf("Nothing is there to read in the journal File system.\n");
			return;
   		}
 	
   		// vkl new
		char files[10][100];
		int nofiles,j,i;
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
		for ( i=nofiles-1; i>=0 ; i--)
		{
			//printf("%s\n",files[i]);
		}
		fclose(filepointer);
	
		for (i=nofiles-1;i>=0;i--)
		{
			// open file pointer for every file in tracker till we get what we want.
			FILE *filepointer1;
			filepointer1 = fopen(files[i], "r");
			//printf("%s\n",files[i]);
			if( filepointer1 == NULL )
   			{
      				perror("Error while opening the file-Fault handling.\n");
      				exit(EXIT_FAILURE);
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
		
			if ( strcmp(v->recordStatus,"commited")==0)
			{
				break;
			}
			else if (strcmp(v->recordStatus,"aborted")==0)
			{
				break;
			}
			else if(strcmp(v->recordStatus,"pending")==0)
			{
				struct journal* temp2;
				temp2=(struct journal *)malloc(sizeof(struct journal));
				temp2->actionID = vinaynum;
				strcpy(temp2->value,v->value);
				strcpy(temp2->recordStatus,"aborted");
				FILE *fptr;
				// get the filename
				char basename[100];
				char variable[100];
				strcpy(basename,"journal");
				sprintf(variable, "%d", vinaynum);
				strcat(basename,variable);
				strcat(basename,".txt");
			
				fptr=fopen(basename,"w");
				if(fptr==NULL)
				{
      					printf("Error in creating the file!");
		
   				}
				fprintf(fptr,"%d\n",temp2->actionID);
	   			fprintf(fptr,"%s\n",temp2->value);
				fprintf(fptr,"%s\n",temp2->recordStatus);
   				fclose(fptr);	
			//value
		
			}

		}	
		//  Open the file and make it as proper, after fault tolerance is done.
		FILE *filepointer3;
		filepointer3 = fopen("handle.txt", "w");
		if( filepointer3 == NULL )
   		{
      			printf("Nothing is there to read in the Fault tolerant system.\n");
   		}
		fprintf(filepointer3,"allow\n");
		fclose(filepointer3);

	}
	return;
	}
	return;
}
