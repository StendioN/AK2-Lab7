#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/ktime.h>
#include <linux/slab.h>

MODULE_AUTHOR("Ihor Lialin <i_lyalin@ukr.net>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

struct mine_head_list {
struct mine_head_list *next;
ktime_t time;
};

static struct mine_head_list *head;

static uint param = 1;
module_param(param, uint, S_IRUGO);
MODULE_PARM_DESC(param, "The amount of params to print Hello world");

static int __init initter(void)
{
uint i;

struct mine_head_list *temp0, *temp1;
head = kmalloc(sizeof(struct mine_head_list), GFP_KERNEL);
temp0 = head;

if (param == 0) {
	printk(KERN_WARNING "The param is 0");
} else if (param >= 5 && param <= 10) {
	printk(KERN_WARNING "The param is between 5 and 10");
} 
BUG_ON(param > 10);

for (i = 0; i < param; i++) {
	temp0->next = kmalloc(sizeof(struct mine_head_list), GFP_KERNEL);
	temp0->time = ktime_get();
	if (i == 7){
		temp0 = NULL;
	}
	//BUG_ON(temp0==0);	
	pr_info("Hello World!");
	temp1 = temp0;
	temp0 = temp0->next;
}
if (param != 0) {
	kfree(temp1->next);
	temp1->next = NULL;
}

printk(KERN_INFO "Param: %d\n", param);

return 0;
}

static void __exit exitter(void)
{
struct mine_head_list *temp;
while (head != NULL && param != 0) {
	temp = head;
	pr_info("Time: %lld", temp->time);
	head = temp->next;
	kfree(temp);
}
pr_info("");
}

module_init(initter);
module_exit(exitter);
