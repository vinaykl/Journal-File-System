#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "journal.h"

int lock_read()
{
	//printf("In Lock \n");
	FILE *filepointer;
	filepointer=fopen("lock.txt","r");
	if(filepointer==NULL)
	{
      		printf("Error in creating/opening the file!");
      		return -1;
		
   	}
	char ch;
	char status[100];
	int i;
	i=0;
	while( ( ch = fgetc(filepointer) ) != EOF )
	{
		status[i]=ch;
		i++;
	}
	status[i]='\0';
	//printf("%s",status);
	fclose(filepointer);
	int lock_status = 0;
	if(strcmp(status,"lock\n")==0)
	{
		lock_status = 1;
	}
	else if(strcmp(status,"unlock\n")==0)
	{
		lock_status = 0;
	}
	else
	{
		lock_status = -1;
	}
	//printf("%d\n",lock_status);
	return lock_status;
}
int lock_create()
{
	//printf("In lock create\n");
	FILE *filepointer1;
	filepointer1=fopen("lock.txt","w");
	if(filepointer1==NULL)
	{
      		printf("Error in creating/opening the file!");
      		return 0;
   	}
	fprintf(filepointer1,"lock\n");
	fclose(filepointer1);
	return 1;
}

int lock_unlock()
{
	//printf("In lock Unlock\n");
	FILE *filepointer2;
	filepointer2=fopen("lock.txt","w");
	if(filepointer2==NULL)
	{
      		printf("Error in creating/opening the file!");
      		return 0;
   	}
	fprintf(filepointer2,"unlock\n");
	fclose(filepointer2);
	return 1;
}
	
