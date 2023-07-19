time_smh.c contains code for calculating the time taken by bash commands to execute.

Compilation: gcc time_shm.c -o time_shm -lrt

Usage: ./time_shm <command_name> <args> 		(without the angular brackets)
Example: ./time_shm ls
	 ./time_shm pwd
	 ./time_shm mkdir Anu

time_pipe.c also containc code for calculating the time taken by bask commands to execute. It used pipe as a method for inter-process communication.

Compilation: gcc time_pipe.c -o time_pipe

Usage: ./time_pipe <command_name> <args>
