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
extern vu16 ADC_DMA_IN[2]; //�����ⲿ����
 int main(void)
 {
		delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	LED_Init();			     //LED�˿ڳ�ʼ��
		oled_init();
		hardware_init();
		task_init();
		while(1)
		{
			schdule_task();
		} 
	}	 
	


