/*
 * @Description: 
 * @Author: Stone-Mo
 * @Date: 2023-06-19
 * Copyright (c) 2023 by [Stone-Mo] , All Rights Reserved.
 */
#include "gpio.h"  

unsigned int *GPIO = NULL;

int GPIO_Init(void)
{
    int mem_fd;
    unsigned int *gpio_map;
    off_t gpio_offset;
    size_t gpio_size;

    // 获取页面大小
    size_t page_size = getpagesize();

    // 计算偏移和大小
    gpio_offset = GPIO_BASE_ADDRESS & ~(page_size - 1);
    gpio_size = (GPIO_BASE_ADDRESS - gpio_offset) + sizeof(unsigned int);

    // 打开 /dev/mem 设备
    mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (mem_fd == -1) {
        perror("Failed to open /dev/mem");
        return 1;
    }

    // 映射地址
    gpio_map = mmap(NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, gpio_offset);
    if (gpio_map == MAP_FAILED) {
        perror("Failed to map GPIO register");
        close(mem_fd);
        return 1;
    }

    // 操作寄存器
    GPIO = (unsigned int *)((unsigned int)gpio_map + (GPIO_BASE_ADDRESS - gpio_offset));

    close(mem_fd);
    return 0;
}

int GPIO_SetValue(Port port, unsigned int pin, int value)
{
	if(GPIO == NULL) return -1;
	GPIO_Map *gpio_map =(GPIO_Map *) ((unsigned int)GPIO + (port * 0x24));
	if(value)
		gpio_map->DAT |= (1 << pin);
	else
		gpio_map->DAT &= ~(1 << pin);
	return 0;
}
int GPIO_GetValue(Port port, unsigned int pin, int value)
{

	return 0;
}
int GPIO_SetConfig(Port port, unsigned int pin, Pin_Mode pin_mode)
{
	if(GPIO == NULL) return -1;
	GPIO_Map *gpio_map =(GPIO_Map *) ((unsigned int)GPIO + (port * 0x24));
	gpio_map->CFG[pin / 8] &= ~((unsigned int)0x07 << pin % 8 * 4);
    gpio_map->CFG[pin / 8] |=  ((unsigned int)pin_mode << pin % 8 * 4);
	return 0;
}

int GPIO_Close(void)
{
	off_t gpio_offset;
    size_t gpio_size;
	// 获取页面大小
    size_t page_size = getpagesize();
    // 计算偏移和大小
    gpio_offset = GPIO_BASE_ADDRESS & ~(page_size - 1);
    gpio_size = (GPIO_BASE_ADDRESS - gpio_offset) + sizeof(unsigned int);
	return munmap(GPIO, gpio_size);
}
