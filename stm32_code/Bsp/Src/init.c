#include "init.h"

#include "lmiic.h"
#include "led.h"
#include "oled.h"
#include "key.h"
#include "stm32f10x_usart.h"
#include "usart.h"
#include "timer.h"
#include "dht11.h"
#include "mq4.h"
void hardware_init(void)
{
	led_init();
	oled_init();
	key_init();
	usart_init();
	timer_init();
	
	DHT11_Init();
	MQ4_ADC_init();
	IIC_Init();
	
}
void led_init(void)
{
	LED_Init();
	LED0=0;
	LED1=0;
}
void oled_init(void)
{
		OLED_Init();			//初始化OLED  
		OLED_Clear() ; 
		OLED_ShowString(48,0,"Hello");
		OLED_ShowString(0,2,"Press WK_UP to  choose mode");
}
/*
按键有点问题
*/
void key_init(void)
{
	KEY_Init();          	//初始化与按键连接的硬件接口
}

void usart_init(void)
{
	uart_init(115200);
}

void timer_init(void)
{
		TIM3_Int_Init(9,7199);//10Khz的计数频率，计数到5000为500ms  
}

