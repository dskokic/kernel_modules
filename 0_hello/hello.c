#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

int init_hello(void) {
	printk("Hello from init_hello()\n");
	return 0;
}

void exit_hello(void) {
	printk("Goodbye from exit_hello()\n");
}

module_init(init_hello);
module_exit(exit_hello);

