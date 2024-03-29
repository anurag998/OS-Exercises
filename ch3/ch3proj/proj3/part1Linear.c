/**
 * simple.c
 *
 * A simple kernel module. 
 * 
 * To compile, run makefile by entering "make"
 *
 * Operating System Concepts - 10th Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/param.h>
#include <linux/sched.h>

/* This function is called when the module is loaded. */
int simple_init(void)
{
	struct task_struct * task;
	printk(KERN_INFO "Loading Module\n");
	for_each_process(task)
	{
			
	printk(KERN_INFO "command = [%s] pid = [%d] state = [%ld] \n", task->comm, task->pid, task->state);
	}
      	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

