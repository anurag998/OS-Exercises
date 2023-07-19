#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <sys/wait.h>
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

int p = fork();

if(p < 0)
{
fprintf(stderr, "Couldn't create child process \n");
}
else if(p == 0)
{
printf("%li ", initNum);
while(initNum != 1)
{
if(initNum%2 == 0)	initNum/=2;
else	initNum = initNum*3 + 1;

printf("%li ", initNum);
}

}
else
{

int retStat;
wait(&retStat);
printf("\n Child process retured with value %d \n", retStat);
}
return 0;
}
