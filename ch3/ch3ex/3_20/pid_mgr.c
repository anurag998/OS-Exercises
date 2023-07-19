#include "pid_mgr.h"

int allocate_map(void)
{
	// initializing all the values in bool array to 0

	for(int i=0;i<RANGE;i++)	pid_tbl[i] = false;
	return 0;
}

int allocate_pid(void)
{
	// Search for the first pid that is unassigned and return it

	for(int i=0;i<RANGE;i++)
	{
		if(pid_tbl[i] == false)
		{
			pid_tbl[i] = true;
			return i+MIN_PID;
		}
	}
	return -1;
}

void release_pid(int pid)
{
	pid_tbl[pid-MIN_PID] = false;
}
