#include <linux/init.h> // contains macros and functions for module initialization
#include <linux/kernel.h> // contains essential kernel definitions and functions
#include <linux/module.h> // provides functionality when working with kernel modules

int simple_init(void) {
	printk(KERN_INFO "Loading in kernel module lab2\n");
	// logs messages defined above at the info level (system log)
	// these messages will appear in system log. to view them, we use a
	// command known as dmesg (sudo)
	return 0;
}

void simple_exit(void) {
	printk(KERN_INFO "Removing kernel module lab2\n");
}

module_init(simple_init);
module_exit(simple_exit);
// These macros register simple_init as the function to run when module is loaded
// Register simple_exit as the function to run when module is unloaded

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("This is a loadable kernel module lab");
MODULE_AUTHOR("Jax Lehmann");
