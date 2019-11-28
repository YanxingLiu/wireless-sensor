#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "key.h"
#include "led.h"
#include "dht11.h"
#include "mq4.h"
#include "init.h"
#include "tasks.h"
#include "bsp_adc.h"
#include "stm32f10x_adc.h"
u16 adcx;
extern vu16 ADC_DMA_IN[2]; //声明外部变量
 int main(void)
 {
		delay_init();	    	 //延时函数初始化	  
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();			     //LED端口初始化
		oled_init();
		hardware_init();
		task_init();
		while(1)
		{
			schdule_task();
		} 
	}	 
	


