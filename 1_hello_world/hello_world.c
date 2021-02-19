#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Darko Skokic");
MODULE_DESCRIPTION("A very simple linux module");
MODULE_VERSION("0.1");

static int __init init_hello_world(void) {
	printk(KERN_INFO "Hello, world!\n");
	return 0;
}

static void __exit exit_hello_world(void) {
	printk(KERN_INFO "Goodbye, world!\n");
}

module_init(init_hello_world);
module_exit(exit_hello_world);

