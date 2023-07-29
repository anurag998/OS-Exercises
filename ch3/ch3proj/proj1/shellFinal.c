#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#define MAX_LINE		80 /* 80 chars per line, per command */
#define READ_END 0
#define WRITE_END 1

char ** parse(char * str, int beg, int end, int * bg_exec)
{
	char ** parsed_str = (char **)malloc(sizeof(char * )* 40);
	int i = beg, curr_word_beg = beg, k = 0;
	while(i < end)
	{
		if(str[i] == ' ')
		{
			//end curr word
			int curr_word_end = i-1;

			if(curr_word_beg > curr_word_end){
				// Nthing
			}
			else
			{
				int curr_word_size = curr_word_end - curr_word_beg + 2;
				char * curr_word = (char * )malloc(sizeof(char) * curr_word_size);
				int j = curr_word_beg;
				while(j <= curr_word_end)
				{
					curr_word[j - curr_word_beg] = str[j];
					j++;
				}
				curr_word[j] = '\0';
				parsed_str[k] = curr_word;
				k++;
			}

			curr_word_beg = i+1;
		}
		

		i++;
	}
	int curr_word_end = end-1;	
	if(curr_word_beg<=end-1)
	{
		
		int curr_word_size = curr_word_end - curr_word_beg + 2;
		char * curr_word = (char * )malloc(sizeof(char) * curr_word_size);
		int j = curr_word_beg;
		while(j <= curr_word_end)
		{
			curr_word[j - curr_word_beg] = str[j];
			j++;
		}
		curr_word[j] = '\0';
		parsed_str[k] = curr_word;
		k++;
	}
	parsed_str[k] = NULL;

	if(strcmp(parsed_str[k-1], "&")  == 0)
	{
		*bg_exec = 1;
		parsed_str[k-1] = NULL;
	}

	return parsed_str;
}

int main(void)
{
	//char *part1[MAX_LINE/2 + 1], *part2[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
    	int should_run = 1;
	char last_command[MAX_LINE];
	last_command[0] = '\0';
	int last_eoc, last_pivot;
    	while (should_run){   
        	int bg_run = 0, pivot = -1, i = 0;
		
		printf("osh>");
        	fflush(stdout);
		
		char curr_command[MAX_LINE];
		
		// Scanning the command from stdin

		while(1)
		{
			char ch;
			scanf("%c", &ch);
			curr_command[i] = ch;
			if(ch == '>' || ch == '<' || ch == '|')
			{
				pivot = i;
			}
			else if(ch == '\n')	break;
			i++;
		}
		curr_command[i] = '\0';
		
		int end_of_command = i;

		if(strcmp(curr_command, "!!") == 0)
		{
			if(last_command[0]!= '\0')
			{
				int it = 0;
				while(last_command[it] != '\0')
				{
					curr_command[it] = last_command[it];
					it++;
				}
				curr_command[it] = '\0';
				end_of_command = last_eoc;
				pivot = last_pivot;
			}
			else
			{
				printf("NO last command found");
				continue;
			}
		}
		
		// copy curr command as the last executed command
		int it = 0;
		last_eoc = end_of_command;
		last_pivot = pivot;
		while(curr_command[it] != '\0')
		{
			last_command[it] = curr_command[it];
			it++;
		}
		last_command[it] = '\0';

		
		
		if(pivot == -1)
		{
			char ** first_arg = parse(curr_command, 0, i, &bg_run);
			if(strcmp(*first_arg, "exit") == 0)	return 0;
			//int iter1 = 0;
			//while(*(first_arg + iter1) != NULL)
			//{printf("%s", *(first_arg + iter1));iter1++;}

			int id = fork();
			if(id == -1)
			{
				printf("Fork failed \n");
				return 1;
			}
			else if(id == 0)
			{
				int st = execvp(first_arg[0], first_arg);
				if(st == -1)
				{
					printf("execvp failed \n");
					return 1;	
				}
			}
			else
			{
				if(bg_run == 0)	wait(NULL);

			}
		}
		else
		{
			char **first_arg = parse(curr_command, 0, pivot, &bg_run);
			//int iter1 = 0;
			//while(*(first_arg + iter1) != NULL)
			//{printf("%s ", *(first_arg + iter1));iter1++;}
			//printf("\n");	
			//iter1 = 0;
			char **second_arg = parse(curr_command, pivot+1, end_of_command, &bg_run);
			//while(*(second_arg + iter1) != NULL)
			//{printf("%s ", *(second_arg + iter1));iter1++;}
			//printf("\n");
			if(curr_command[pivot] == '>')
			{
				
				int id = fork();
				if(id == -1)
				{
					printf("Fork failed \n");
					return 1;
				}
				else if(id == 0)
				{
					int fd = open(*second_arg, O_CREAT | O_RDWR | O_APPEND, 0640);
					dup2(fd, 1);
					//close(1);
					int st = execvp(first_arg[0], first_arg);
					if(st == -1)
					{
						printf("execvp failed\n");
						return 0;
					}
				}
				else
				{
					if(bg_run == 0)wait(NULL);
				}
			}
			else if(curr_command[pivot] == '<')
			{
				
				int id = fork();
				if(id == -1)
				{
					printf("Fork failed \n");
					return 1;
				}
				else if(id == 0)
				{
					int fd = open(*second_arg, O_CREAT | O_RDWR);
					dup2(fd, 0);
					
					int st = execvp(first_arg[0], first_arg);
					if(st == -1)
					{
						printf("execvp failed");
						return 1;	
					}
				}
				else
				{
					if(bg_run == 0)	wait(NULL);

				}
			}
			else
			{
				
				int id = fork();
				if(id == -1)
				{
					printf("Fork failed \n");
					return 1;
				}
				else if(id == 0)
				{

					int fd[2];
					if(pipe(fd) == -1)
					{
						printf("Pipe failed\n");
						return 1;
					}

					int id2 = fork();
					if(id2 == -1)	{printf("fork failed");return -1;}
					else if(id2 == 0)
					{
						dup2(fd[WRITE_END], 1);
						close(fd[WRITE_END]);
						close(fd[READ_END]);

						int st = execvp(first_arg[0], first_arg);
						if(st == -1)	{printf("Execvp failed");return -1;}
					}
					else
					{
						
					close(fd[WRITE_END]);
					dup2(fd[READ_END], 0);
					close(fd[READ_END]);
					
					int st = execvp(second_arg[0], second_arg);

					if(st == -1)	{printf("execvp failed");return 1;}
					}
				}
				else
				{
					if(bg_run == 0)	wait(NULL);


				}
			}
		}		
        
    	}
    
	return 0;
}
