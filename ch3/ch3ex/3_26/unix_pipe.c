#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

int main(void)
{
	char write_msg[BUFFER_SIZE] = "Greetings";
	char read_msg[BUFFER_SIZE];
	pid_t pid;
	int fd1[2], fd2[2];
	// fd1 parent writes, chile reads
	// fd2 - > Child write, parent reads
	
	/* create the pipe */
	if (pipe(fd1) == -1) {
		fprintf(stderr,"Pipe failed");
		return 1;
	}
	
	if(pipe(fd2) == -1)
	{
		fprintf(stderr, "Pipe failed");
		return 1;
	}

	
	
	// Write the message to the buffer
	// close(fd1[READ_END]);
	
	write(fd1[WRITE_END], write_msg, strlen(write_msg) + 1);
	printf("Written %s by the parent process\n", write_msg);
	// close(fd1[WRITE_END]);
	
	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}

	if (pid > 0) {  /* parent process */
		int status;
		wait(&status);
		char read_msg_2[BUFFER_SIZE];
		read(fd2[READ_END], read_msg_2, BUFFER_SIZE);
		printf("Parent Process Reads %s \n", read_msg_2);
	}
	else { /* child process */
		/* close the unused end of the pipe */
		close(fd1[WRITE_END]);
		

		/* read from the pipe */
		read(fd1[READ_END], read_msg, BUFFER_SIZE);
		printf("child read %s\n",read_msg);

		/* close the write end of the pipe */
		close(fd1[READ_END]);
		
		int diff = 'A' - 'a';
		int i = 0;
		while(read_msg[i] != '\0')
		{
			if(read_msg[i] >= 'a' && read_msg[i] <= 'z')
			{
				read_msg[i] += diff;
			}
			else if(read_msg[i] >= 'A' && read_msg[i] <= 'Z')
			{read_msg[i] -= diff;}
			
			i++;
			
		}
		
		write(fd2[WRITE_END], read_msg, strlen(read_msg)+1);
		
	}

	return 0;
}
