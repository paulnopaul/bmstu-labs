#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

/*
Реализовать загружаемый модуль ядра, осуществляющий перебор списка задач (struct task_struct) и в системный файл /var/log/messages выводит идентификатор каждого встреченного процесса и имя его исполняемого файла, идентификатор процесса предка и имя этого файла. При инициализации модуля следует также использовать символ current для вывода такой же информации о текущем процессе. При выгрузке модуля записывается “Good by”. Модуль должен собираться при помощи Make-файла. Загружаемый модуль должен содержать:

● Указание лицензии GPL
● Указание автора

 */

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
