/**
 * Linux内核支持很多模块，驱动程序就是其中最重要的一种，
 * 甚至文件系统也可以写成一个模块，然后加入到内核中。
 * 
 * 加载内核的命令：insmod/modprode
 * 卸载模块命令：rmmod
 */ 
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

int __init xxx_init(void)
{
    // 模块加载时的初始化工作
    return 0;
}

void __exit xxx_exit(void)
{
    // 模块卸载时的销毁工作
}

module_init(xxx_init);  // 指定模块的初始化函数的宏
module_exit(xxx_exit);  // 指定模块的卸载函数的宏

MODULE_LICENSE("GPL");