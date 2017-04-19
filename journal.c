#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "journal.h"
#include "faulthandle.h"
#include "newDataId.h"
#include "read.h"
#include "write.h"
#include "deallocate.h"
#include "allocate.h"
#include "lockmanager.h"


int global_counter = 0;
int global_counter1 = 0;
int kill_counter=0;
// global_counter is for new_action(both read and write)

bool to_go_to_wait()
{
	int lock_status;
	
	lock_status=lock_read();
	if(lock_status == 0)
	{
		return true;
	}
	else
	{
		kill_counter = kill_counter +1;
		if(kill_counter < 10)
		{
		sleep(2);
		to_go_to_wait();
		return true;
		}
		else
		{
		lock_unlock();
		handle();
		
		to_go_to_wait();
		}
		
	}
}

int main(int argc,char * argv[])
{
	handle();
	if(argc!=2)
	{
		printf("usage is wrong. Should have 2 arguments like JFS ARGUMENT\n");
		return 0;
	}
	char b[100]="WRITE_NEW_VALUE";
	char c[100]="COMMIT";
	char d[100]="READ_CURRENT_VALUE";
	char e[100]="ABORT";
	char valueReq[100];
	int position;
	int dataID;
	if(strstr(argv[1],b)!=NULL)
	{
		position =2;
		char *p;
		p = strtok(argv[1],"[");
		p = strtok(NULL,"]");
		strcpy(valueReq,p);
	}
	else if(strstr(argv[1],c)!=NULL)
	{
		position =3;
		char *p;
		p = strtok(argv[1],"[");
		p = strtok(NULL,"]");
		if(!p)
		{
			printf("DataId should be present\n");
			return 0;
		}
		char *pi;
		pi=strstr(p,".");
		if(pi!=NULL)
		{
			printf("Floating point found.dataId can be only Int\n");
			return 0;
		}
		dataID=atoi(p);
	}
	else if(strstr(argv[1],d)!=NULL)
	{
		position =1;
		char *p;
		p = strtok(argv[1],"[");
		p = strtok(NULL,"]");
		if(!p)
		{
			dataID=0;
		}
		else	
		{
		//printf("%s\n",p);
		char *pi;
		pi=strstr(p,".");
		if(pi!=NULL)
		{
			printf("Floating point found.dataId can be only Int\n");
			return 0;
		}
		dataID=atoi(p);
		}
	}
	else if(strstr(argv[1],e)!=NULL)
	{
		position =4;
		char *p;
		p = strtok(argv[1],"[");
		p = strtok(NULL,"]");
		// check for floating point.
		if(!p)
		{
			printf("DataId should be present\n");
			return 0;
		}
		char *pi;
		pi=strstr(p,".");
		if(pi!=NULL)
		{
			printf("Floating point found.dataId can be only Int\n");
			return 0;
		}
		dataID=atoi(p);
	}
	switch(position)
	{
			case 1: {
				// open the tracker and read the filename we need
				char * contents;
				contents = read();
				printf("%s\n",contents);
				break;
				}
			case 2: {
				
				int result;
				// Testing with the data structures
				// Lock coding
				bool goahead;
				goahead = to_go_to_wait();
				if(goahead)
				{
				// create a lock on it
				int lock;
				lock =lock_create();
				if( lock==1)
				{
					//printf(" Successfully created a lock on variable \n");
				}
				// Just for before or after atomicity
				char * contents;
				int value;
				contents = read();
				value = atoi(contents);
				// got the value
				// converting the value from string to int
				int extra;
				extra = atoi(valueReq);
				extra = extra+value;
				sprintf(valueReq, "%d", extra);
				// converted and added the value

				struct journal* temp;
				temp=(struct journal *)malloc(sizeof(struct journal));
				temp->actionID = newDataId();
				strcpy(temp->recordStatus,"pending");
				//temp->value = data;
				strcpy(temp->value,valueReq);
				result=write(temp);
				printf("DataID is %d\n",result);
				global_counter = result;
				}
				break;
				}
			case 3: {
				int num;
				int vin;
				vin = newDataId();
				vin--;
				if(dataID > vin)
				{
					printf(" dataID is not present\n");
					return 0;
				}
				num = commit(dataID);
				if(num == -1)
				{
					printf("Error in opening files\n");
				}
				else if(num== -2)
				{
					printf("cannot commit an action which is already aborted\n");
				}
				else if( num == 0)
				{
					printf("%d\n",num);
				}
				int lock1;
				lock1 =lock_unlock();
				if( lock1==1)
				{
					//printf(" Successfully lifted the  lock on variable \n");
				}
				break;
				}
			case 4: {
				int num1;
				int vin1;
				vin1 = newDataId();
				vin1--;
				if(dataID > vin1)
				{
					printf(" dataID is not present\n");
					return 0;
				}
				num1=abort1(dataID);
				if(num1 == -1)
				{
					printf("Error in opening files\n");
				}
				else if(num1== -2)
				{
					printf("cannot commit an action which is already aborted\n");
				}
				else if( num1 == 0)
				{
					printf("%d\n",num1);
				}
				int lock1;
				lock1 =lock_unlock();
				if( lock1==1)
				{
					//printf(" Successfully lifted the  lock on variable \n");
				}
				break;
				}
			default: {
				// Flow never comes here. Just for graceful exit.
				 exit(1);
				}
		}
	//}
	return 0;
}
