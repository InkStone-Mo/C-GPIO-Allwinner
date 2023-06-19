/*
 * @Description: 
 * @FilePath: /C-GPIO-Allwinner/sample_c/main.c
 * @Author: Stone-Mo
 * @Date: 2023-06-19
 * Copyright (c) 2023 by [Stone-Mo] , All Rights Reserved.
 */
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define ALLWINNER_F1C100S
#include <gpio.h>

int main()
{
    GPIO_Init();
    GPIO_SetConfig(PE, 10, OUT);
    while (1)
    {
        GPIO_SetValue(PE, 10, 0);
        sleep(1);
        GPIO_SetValue(PE, 10, 1);
        sleep(1);
    }
    return GPIO_Close();
}
