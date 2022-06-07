void delay_ms(unsigned int ms);
/**
 * led裸机程序
 */
int bare_led(void)
{
    // 定义寄存器 GPIOE13
    volatile unsigned int *gpioe_altfn0  = (unsigned int *)0xC001E020;
    volatile unsigned int *gpioe_outenb = (unsigned int *)0xC001E004;
    volatile unsigned int *gpioe_out = (unsigned int *)0xC001E000;

    // 选择复用功能0
    *gpioe_altfn0 &= ~(0x3<<26);
    // 选择输出模式
    *gpioe_outenb |= (0x1<<13);

    // 使等闪烁
    while (1) {
        // 亮
        *gpioe_out &= ~(0x1<<13);
        delay_ms(1000);
        // 灭
        *gpioe_out |= (0x1<<13);
        delay_ms(1000);
    }
    
}

void delay_ms(unsigned int ms)
{
    int i, j;
    for(i=0; i<ms; i++){
        for(j=0; j<20000; j++)
            ;
    }
}

/**
 * 1. 编译出elf文件(用于Linux系统的文件)
 * arm-linux-gcc -nostartfiles -nostdlib -Ttext 40008000 -e bare_led bare_led.c -o bare_led
 * @ -onstartfiles: 不加入起始文件
 * @ -nostdlib: 不加入标准库
 * @ -Ttext: 指定连接地址 
 * @ -e: 程序入口(函数名)
 * 
 * 2. 将elf文件转换为bin文件(针对裸机坏境)
 * arm-linux-objcopy -O binary led led.bin
 * 
 * 3. 将二进制文件传送到开发板运行
 *  (1) 将bare_led.bin 拷贝到tftp服务器
 *  (2) tftp 40008000 bare_led.bin
 *      go 40008000
 */