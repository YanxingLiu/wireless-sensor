#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

 

#define KEY0  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9)//读取按键1
#define KEY2 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8)//读取按键2
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	//wkup按键
#define KEY3  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12)	//key3
#define KEY4	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11)	//key4
 



void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数					    
#endif
