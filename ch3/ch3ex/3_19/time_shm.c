#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<sys/time.h>
int main(int argc, char *argv[])
{
//printf("%d\n", argc);
//printf("%s %s \n", argv[0], argv[1]);

/* Creating a shared memory region*/
const int SIZE = 4096;
const char *name = "SM_TIME";

int fd;
struct timeval *ptr;

fd = shm_open(name, O_CREAT | O_RDWR, 0666);

ftruncate(fd, SIZE);

ptr = (struct timeval *) mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

//sprintf(ptr, "%s", "Anurag");
//ptr += strlen("Anurag");
//printf("Parent %s \n", ptr);

int f = fork();
int status;

if(f < 0 )	printf("Can't create child process");
else if(f == 0)
{
	char * args[100];
	//args[1] = NULL;

	char command[100] = "/bin/";

	int i = 0;
	while(argv[1][i] != '\0')
	{
	command[i+5] = argv[1][i];
	i++;
	}
	command[i+5] = '\0';
	char *cmdPtr = command;
	args[0] = cmdPtr;
 
	for(i=2;i<argc;i++)
	{
		args[i-1] = argv[i];
	}
	args[argc-1] = NULL;
	struct timeval start;
	gettimeofday(&start, NULL);
	*ptr = start;
	
	execv(cmdPtr, args);
}
else
{
	wait(&status);
	struct timeval start = *ptr;
	//printf("Parent %lu \n", start.tv_sec);
	struct timeval curr;
	gettimeofday(&curr, NULL);
	unsigned long int diff_sec = (curr.tv_sec - start.tv_sec);
	unsigned long int diff_ms = (curr.tv_usec - start.tv_usec);
	printf("Time in Seconds: %lu.", diff_sec);
	printf("%06lu \n", diff_ms);
	shm_unlink(name);
}
return 0;
}
