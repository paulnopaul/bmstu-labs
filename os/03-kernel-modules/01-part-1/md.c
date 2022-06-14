#include <linux/init.h>
#include <linux/init_task.h>
#include <linux/module.h>
#include <linux/kernel.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Paul");

static int func_init(void) {
	struct task_struct *task = &init_task;
	do {
	printk(KERN_INFO "=== md: %s - %d, parent: %s - %d\n",
			task->comm, task->pid, task->parent->comm, task->parent->pid);
} while ((task = next_task(task)) != &init_task);

printk(KERN_INFO "=== md: current: %s - %d, parent: %s - %d\n",
		current->comm, current->pid, current->parent->comm, current->parent->pid);
	return 0;
}

static void func_exit(void) {
	printk(KERN_ALERT "Module unloaded\n");
}

module_init (func_init);
module_exit (func_exit);
