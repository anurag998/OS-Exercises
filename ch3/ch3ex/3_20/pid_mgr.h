#ifndef PID_MGR_H
#define PID_MGR_H 


#define MIN_PID 300
#define MAX_PID 5000
#define RANGE MAX_PID - MIN_PID + 1


#include<stdbool.h>

bool pid_tbl[RANGE];

int allocate_map(void);

int allocate_pid(void);

void release_pid(int pid);

#endif
