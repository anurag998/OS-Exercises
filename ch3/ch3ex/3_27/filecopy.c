/**
 * Example program demonstrating UNIX pipes.
 *
 * Figures 3.21 & 3.22
 *
 * @author Silberschatz, Galvin, and Gagne
 * Operating System Concepts  - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define MAX_FILE_SIZE 500
#define READ_END	0
#define WRITE_END	1

int main(int argc, char* argv[])
{
	if(argc != 3){
	fprintf(stderr, "Illegal usage \n Correct usage: ./filecopy input_file_name.txt output_file_name.txt");
	return -1;
	}
	FILE * fptr = fopen(argv[1], "r");
	char ch;
	int i = 0;
	
	char file_cont[MAX_FILE_SIZE];
	while((i < MAX_FILE_SIZE) && (ch = fgetc(fptr)) != EOF)
	{
		file_cont[i] = ch;
		i++;
	}
	file_cont[i] = '\0';
	
	
	//char write_msg[MAX_FILE_SIZE];
	//char read_msg[MAX_FILE_SIZE];
	pid_t pid;
	int fd[2];

	/* create the pipe */
	if (pipe(fd) == -1) {
		fprintf(stderr,"Pipe failed");
		return 1;
	}
	
	/* now fork a child process */
	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}

	if (pid > 0) {  /* parent process */
		/* close the unused end of the pipe */
		close(fd[READ_END]);

		/* write to the pipe */
		write(fd[WRITE_END], file_cont, strlen(file_cont)+1); 

		/* close the write end of the pipe */
		close(fd[WRITE_END]);
	}
	else { /* child process */
		/* close the unused end of the pipe */
		close(fd[WRITE_END]);

		/* read from the pipe */
		char child_read_file[MAX_FILE_SIZE];
		read(fd[READ_END], child_read_file, MAX_FILE_SIZE);
		//printf("child read %s\n",read_msg);
		
		FILE * write_fptr = fopen(argv[2], "w");
		fprintf(write_fptr,"%s", child_read_file);
		/* close the write end of the pipe */
		close(fd[READ_END]);
	}

	return 0;
}
