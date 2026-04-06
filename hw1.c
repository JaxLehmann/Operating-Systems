#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/uaccess.h> 
#include <linux/jiffies.h> // i imported jiffies
#include <linux/proc_fs.h> // library imported for step 5a

int counter = 0; // global counter variable teehee
static struct timer_list my_timer;
void timer(struct timer_list *t);
	

void timer(struct timer_list *t) { 
 
 mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000));
 counter++;
 printk(KERN_INFO "Counter is %d and jiffies is %ld\n", counter, jiffies);
}



static ssize_t proc_read(struct file *file, char __user *buf, size_t len, loff_t *offset) {
    static int completed = 0;
    const char *message = "Whoopsies, Jax is all up in your kernel.\n"; 
    size_t message_len = strlen(message);
    

    if (completed) {
        completed = 0; 
        return 0; 
    }

    if (copy_to_user(buf, message, message_len)) {
        return -EFAULT;
    }

    completed = 1; 
    return message_len;
}


static const struct proc_ops proc_ops = {
    .proc_read = proc_read,
};



int counter_module_init(void) {
	printk(KERN_INFO "counter module has been loaded\n");
    	timer_setup(&my_timer, timer, 0);
    	mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000));
    	proc_create("Jax", 0666, NULL, &proc_ops);
	

    return 0;
}



void counter_module_exit(void) {
	remove_proc_entry("Jax", NULL);
	printk(KERN_INFO "counter module has been removed\n");
	del_timer(&my_timer);
    	
}
module_init(counter_module_init);
module_exit(counter_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jax Lehmann");
MODULE_DESCRIPTION("Lab demonstrates loading a new LKM to create a counter and print to system log, print jiffies, and create a /proc file displaying user message.");

