#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>


int newAction_counter=0;

int newDataId()
{
	char c;
	//char filename[100];
	//int length=0;
	FILE *filepointer;
	filepointer = fopen("tracker.txt", "r");
	if( filepointer == NULL )
   	{
		return 1;
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
	
	//printf(" Allocate getting details from %s\n",files[nofiles-1]);
	// get the number
	FILE *filepointer1;
	filepointer1 = fopen(files[nofiles-1], "r");
	if( filepointer1 == NULL )
   	{
      		perror("Error while opening the file.\n");
      		exit(EXIT_FAILURE);
   	}
		// get the corresponding file and save the value
	char contents[10][100];
	int vkl,arglength;
	vkl=0;
	arglength=0;
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
		
	newAction_counter = vinaynum;
	newAction_counter++;
	return newAction_counter;
	
}
