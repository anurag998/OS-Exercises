#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <sys/wait.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<sys/types.h>


int main(int argc, char *argv[])
{

if(argc < 2)
{
fprintf(stderr, "Usage: collatz <integer> \n No argument found \n");
exit(1);
}
else if(argc > 2)
{
fprintf(stderr, "Usage: collatz <integer> \n Too many arguments \n");
exit(1);
}

errno = 0;
long initNum = strtol(argv[1], NULL, 10);

if(errno == ERANGE)
{
fprintf(stderr, "Integer overflow error");
exit(1);
}

if(initNum == 0)
{
fprintf(stderr, "Invalid Number \n");

}
//printf("%li", initNum);

const int SIZE = 4096;
const char *name = "SM";

int fd;

fd = shm_open(name, O_CREAT | O_RDWR, 0666);

ftruncate(fd, SIZE);

long int * ptr = (long int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);



int p = fork();

if(p < 0)
{
fprintf(stderr, "Couldn't create child process \n");
}
else if(p == 0)
{
//printf("%li ", initNum);
*ptr = initNum;
ptr++;
while(initNum != 1)
{
if(initNum%2 == 0)	initNum/=2;
else	initNum = initNum*3 + 1;

*ptr = initNum;
ptr++;

//printf("%li ", initNum);

}

*ptr = -1;

}
else
{

int retStat;
wait(&retStat);

while(*ptr != -1)
{
printf("%li ", *ptr);
ptr++;
}
printf("\n");
shm_unlink(name);
//printf("\n Child process retured with value %d \n", retStat);
}
return 0;
}
