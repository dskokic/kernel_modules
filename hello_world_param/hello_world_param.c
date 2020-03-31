#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Darko Skokic");
MODULE_DESCRIPTION("Simple linux module with parameters");
MODULE_VERSION("0.1");

static int number1 = 31;
static int number2 = 12;
static char *message = "NewYear";
module_param(number1, int, S_IRUGO);
module_param(number2, int, S_IRUGO);
module_param(message, charp, S_IRUGO);
MODULE_PARM_DESC(number1, "First  integer argument");
MODULE_PARM_DESC(number2, "Second integer argument");
MODULE_PARM_DESC(message, "Message to be displayed together with arguments");

static int __init init_hello_world(void) {
	printk(KERN_INFO "Hello!\n");
	printk(KERN_INFO "number1=%d, number2=%d, message=%s\n", number1, number2, message);
	return 0;
}

static void __exit exit_hello_world(void) {
	printk(KERN_INFO "Goodbye, unloading module hello_world_param!\n");
}

module_init(init_hello_world);
module_exit(exit_hello_world);

