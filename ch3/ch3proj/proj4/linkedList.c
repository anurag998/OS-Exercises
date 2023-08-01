#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/param.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/slab.h>
struct color{
int red;
int blue;
int green;
struct list_head list;	
};

static LIST_HEAD(color_list);

void addColor(int redVal, int greenVal, int blueVal){

	struct color * genericColor;
	genericColor = (struct color *)kmalloc(sizeof(struct color), GFP_KERNEL);
	genericColor->red = redVal;
	genericColor->blue = greenVal;
	genericColor->green = blueVal;
	INIT_LIST_HEAD(&genericColor->list);
	list_add_tail(&genericColor->list, &color_list);

}


/* This function is called when the module is loaded. */
int simple_init(void)
{

	struct color * ptr;
	printk(KERN_INFO "Loading Module\n");
	// Iterating
	
addColor(144, 200 ,300);

addColor(255, 0, 0);
addColor(1, 0, 0);
addColor(6,7,8);

	list_for_each_entry(ptr, &color_list, list){
		
		printk(KERN_INFO "Red: %d, Green: %d, Blue: %d\n", ptr->red, ptr->green, ptr->blue);
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

