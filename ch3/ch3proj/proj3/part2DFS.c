
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/param.h>
#include <linux/sched.h>

/* This function is called when the module is loaded. */
void DFS(struct task_struct * curr)
{
	
	struct task_struct * task;
	struct list_head * list;
	list_for_each(list, &(curr->children))
	{
	task = list_entry(list, struct task_struct, sibling);
	printk(KERN_INFO "command = [%s] pid = [%d] state = [%ld] \n", task->comm, task->pid, task->state);	
	DFS(task);
	}
}

int simple_init(void)
{
	struct task_struct *init_ptr = &init_task;
	//struct task_struct * task;
	//struct list_head * list;
	printk(KERN_INFO "Loading Module\n");
	DFS(init_ptr);
	//list_for_each(list, &(init_task.children))
	//{
	//task = list_entry(list, struct task_struct, sibling);
	//printk(KERN_INFO "command = [%s] pid = [%d] state = [%ld] \n", task->comm, task->pid, task->state);
	//}

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

