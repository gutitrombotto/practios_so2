#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>		/* Needed for the macros */

static int __init hello_init(void)
{
	printk(KERN_INFO "Hola Sistemas Operativos II!\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO "Adios Sistemas Operativos II\n");
}

module_init(hello_init);
module_exit(hello_exit);