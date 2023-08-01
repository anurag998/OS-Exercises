#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/param.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>

struct color{
int val;
struct list_head list;	
};

static int start = 25;
module_param(start, int, 0);
static LIST_HEAD(color_list);

void addNum(int val){

	struct color * genericColor;
	genericColor = (struct color *)kmalloc(sizeof(struct color), GFP_KERNEL);
	genericColor->val = val;
	INIT_LIST_HEAD(&genericColor->list);
	list_add_tail(&genericColor->list, &color_list);
}


/* This function is called when the module is loaded. */
int simple_init(void)
{

	int initNum = start;	
	struct color * ptr;
	printk(KERN_INFO "Loading Module\n");
	// Iterating
while(initNum != 1)
{


addNum(initNum);
if(initNum%2 == 0)	initNum/=2;
else	initNum = initNum*3 + 1;

//printf("%d ", initNum);
}
addNum(initNum);

	list_for_each_entry(ptr, &color_list, list){
		
		printk(KERN_INFO "%d ", ptr->val);
	}
      	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	struct color *ptr, *next;

	list_for_each_entry_safe(ptr, next, &color_list, list){
	list_del(&ptr->list);
	kfree(ptr);
	}
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

