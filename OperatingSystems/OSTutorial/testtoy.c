/* Bernardo Pla */
/* COP 4610 Lab 1, Spring 2017 */

#include <linux/module.h>

static int hello_init(void)
{
	printk("Hello world, This is Bernardo Pla\n");
	printk("Hello world 2, this is Bernardo Pla\n");
	printk("Hello world 3, this is Bernardo Pla\n");
	return 0;
}

static void hello_exit(void)
{
	printk("Goodbye world, Bernardo Pla, signing off\n");
	printk("Goodbye world 2, Bernardo Pla, signing off\n");
	printk("Goodbye world 3, Bernardo Pla, signing off\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("BERNARDO PLA");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello World Module");

