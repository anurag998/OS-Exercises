#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
int main()
{

	int f = fork();
	if(f < 0)	printf("Failed to create child process");
	else if(f ==0)	exit(0);
	else sleep(20000);

	return 0;
}
