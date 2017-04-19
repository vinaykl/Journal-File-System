#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "journal.h"

char * read()
{	
	//char c;
	//char filename[100];
	//int length=0;
	FILE *filepointer;
	filepointer = fopen("tracker.txt", "r");
	if( filepointer == NULL )
   	{
      		printf("Nothing is there to read in the journal File system.\n");
		return "NoCommitedValue";
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
      			perror("Error while opening the file.\n");
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
			return v->value;
		}
		//value
	}
	return "NoCommitedValue";
	// vkl

	/*		
 	// contents of the file are
   	c = fgetc(filepointer);
    	if (isalpha(c))
    	{
        	while (isalnum(c))
        	{
            		filename[length] = c;
            		length++;
            		c = fgetc(filepointer);
        	}
        	filename[length] = '\0';
	}
	printf("Tracker file contains :\n");
	printf("%s\n",filename);
	fclose(filepointer);
	
	// reading the contents of file derived from tracker.
	
	char ch;
	FILE *fp;
	strcat(filename,".txt");
	fp = fopen(filename, "r");
	if( fp == NULL )
   	{
      		perror("Error while opening the file.\n");
      		exit(EXIT_FAILURE);
   	}
	char contents[10][100];
	int arglength =0;
	int vkl=0;
 
   	while( ( ch = fgetc(fp) ) != EOF )
	{
		do
		{
		contents[vkl][arglength] = ch;
            	arglength++;
      		//printf("%c\n",ch);
		}while((ch=fgetc(fp))!='\n');
		contents[vkl][arglength]='\0';
		vkl++;
		//printf("\n");
		arglength=0;
	}
	//contents[vkl][arglength]='\0';
	int j;
	for ( j =0;j < vkl ; j++)
	{
	//printf("%s\n",contents[j]);
	}
	int i;
	i= atoi(contents[1]);
	//printf("%d",i);
	
 
   	fclose(fp);
	return i;
	*/
	
}
