#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Darko Skokic");
MODULE_DESCRIPTION("A simple char device kernel module.");
MODULE_VERSION("0.1");

#define DEVICE_NAME "simple_lkm"
#define INITIAL_MSG "SIMPLE LKM EXAMPLE"
#define MSG_BUFF_LEN 20

/* Prototypes for device functions */
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static int major_num;
static int device_open_count;
static char msg_buff[MSG_BUFF_LEN];
static char *msg_ptr;

static struct file_operations file_ops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

static int device_open(struct inode *inode, struct file *file) {
	printk(KERN_INFO "device_open called, device_open_count=%d\n", device_open_count);
	if(device_open_count) {
		return -EBUSY;
	}
	device_open_count++;
	try_module_get(THIS_MODULE); // not needed really	
	return 0;
}

static int device_release(struct inode *inode, struct file *file) {
	printk(KERN_INFO "device_release called, device_open_count=%d\n", device_open_count);
	device_open_count--;
	module_put(THIS_MODULE);
	return 0;
}

static ssize_t device_read(struct file *file, char *buffer, size_t len, loff_t *offset) {
	int bytes_read = 0;
	/* if we are at the end of the buffer, go back to the beginning */
	if(*msg_ptr == 0) {
		msg_ptr = msg_buff;
	}

	/* buffer is in user space, so you can't just reference it. Function put_user() handles this */
	while(len && *msg_ptr) {
		put_user(*(msg_ptr++), buffer++);
		len--;
		bytes_read++;
	}
	return bytes_read;
}

static ssize_t device_write(struct file *file, const char *buffer, size_t len, loff_t *offset) {
	printk(KERN_ALERT "This operation is not supported so far in this example1\n");
	return 0;
}

static int __init simple_init(void) {
	strncpy(msg_buff, INITIAL_MSG, MSG_BUFF_LEN);
	msg_ptr = msg_buff;

	major_num = register_chrdev(0, DEVICE_NAME, &file_ops);
	if(major_num < 0) {
		printk(KERN_ALERT "Could not register character device. (Major number=%d)!\n", major_num);
		return major_num;
	} else {
		device_open_count = 0;
		printk(KERN_INFO "Simple_module loaded and registered device major number=%d!\n", major_num);
		printk(KERN_INFO "simple_char_device loaded!\n");
		printk(KERN_INFO "msg_buff=%s\n", msg_buff);
		return 0;
	}

	device_open_count = 0;
	printk(KERN_INFO "simple_char_device loaded!\n");
	printk(KERN_INFO "msg_buff=%s\n", msg_buff);

	return 0;
}

static void __exit simple_exit(void) {
	unregister_chrdev(major_num, DEVICE_NAME);
	printk(KERN_INFO "simple_char_device unloaded and unregistered major number=%d!\n", major_num);
}

module_init(simple_init);
module_exit(simple_exit);

