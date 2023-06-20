/*
 * @Description: 
 * @Author: Stone-Mo
 * @Date: 2023-06-19
 * Copyright (c) 2023 by [Stone-Mo] , All Rights Reserved.
 */
#ifndef __GPIO_H__
#define __GPIO_H__
#include<stdio.h>  
#include<unistd.h>  
#include<sys/mman.h>  
#include<sys/types.h>  
#include<sys/stat.h>  
#include<fcntl.h> 

/* configure only in this / 以下适配 */

// 支持 H6 \ H616
#if defined(ALLWINNER_H6)||defined(ALLWINNER_H616) 
	#define GPIO_BASE_ADDRESS	0x0300B000
#else //支持 H3 \ H6 \ F1C100S \ F1C200S \F1C600S \ V3S
	#define GPIO_BASE_ADDRESS	0x01C20800
#endif

#if defined(ALLWINNER_V3S)
	typedef enum
	{
		PB = 1,
		PC = 2,
		PD = 3,
		PE = 4,
		PF = 5,
		PG = 6,
	}Port;
#elif defined(ALLWINNER_F1C100S)||defined(ALLWINNER_F1C200S)||defined(ALLWINNER_F1C600S)
	typedef enum
	{
		PA = 0,
		PB = 1,
		PC = 2,
		PD = 3,
		PE = 4,
		PF = 5,
	}Port;
#elif defined(ALLWINNER_H6)
	typedef enum
	{
		PC = 2,
		PD = 3,
		PF = 5,
		PG = 6,
		PH = 7,
	}Port;
#elif defined(ALLWINNER_H616)
        typedef enum
        {
                PC = 2,
                PF = 5,
                PG = 6,
                PH = 7,
		PI = 9,
        }Port;
#else // ALLWINNER H3
	typedef enum
	{
		PA = 0,
		PB = 1,
		PC = 2,
		PD = 3,
		PE = 4,
		PF = 5,
		PG = 6,
	}Port;
#endif

/* config end 结束*/

typedef struct
{
	unsigned int CFG[4];
	unsigned int DAT ;
	unsigned int DRV0;
	unsigned int DRV1;
	unsigned int PUL0;
	unsigned int PUL1;
}GPIO_Map;

typedef enum
{
	IN			= 0x00,
	OUT			= 0x01,
	DISABLE		= 0x07,
}Pin_Mode;

extern unsigned int *GPIO;

int GPIO_Init(void);
int GPIO_SetValue(Port port, unsigned int pin, int value);
int GPIO_GetValue(Port port, unsigned int pin, int value);
int GPIO_SetConfig(Port port, unsigned int pin, Pin_Mode pin_mode);
int GPIO_Close(void);

#endif
