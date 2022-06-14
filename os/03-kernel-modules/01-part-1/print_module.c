#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int func_init(void) {
	printk(KERN_ALERT "Module md loaded!\n");
	return 0;
}

static void func_exit(void) {
	printk(KERN_ALERT "Module unloaded\n");
}

module_init (func_init);
modeule_exit (func_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Paul");
MODULE_DESCRIPTION("Module description");
