#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

 

#define KEY0  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9)//��ȡ����1
#define KEY2 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8)//��ȡ����2
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	//wkup����
#define KEY3  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12)	//key3
#define KEY4	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11)	//key4
 



void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8 mode);  	//����ɨ�躯��					    
#endif
