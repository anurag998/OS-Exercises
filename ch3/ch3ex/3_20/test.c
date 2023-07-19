#include <stdio.h>
#include "pid_mgr.h"

int main()
{
	int allocated = allocate_map();

	int pid1 = allocate_pid();
	int pid2 = allocate_pid();
	int pid3 = allocate_pid();

	printf("%d %d %d \n", pid1, pid2, pid3);
	release_pid(pid2);
	
	int pid4 = allocate_pid();

	printf("%d \n", pid4);
}
