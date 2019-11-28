#include "tasks.h"
#include "led.h"
#include "stm32f10x.h"
#include "dht11.h"
#include "module.h"
#include "usart.h"
#include "oled.h"
#include "key.h"
#include "mq4.h"
struct task_handler tasks_handle_container[MAX_TASKS] =  {0};

struct dht11_module dht11;
struct key_module key;
struct oled_display_module oled_show;
struct mq_module mq;
struct lm75a_module lm75;
//task 0
void mode_switch_task(void)
{
	KEY_Scan(0);
	if (key.key0 == 1)
	{
		oled_show.mode = TEMPERATURE_MODE;
	}
	else if(key.key1 ==1)
	{
		oled_show.mode = HUMIDTY_MODE;
	}
	else if(key.key2 == 1)
	{
		oled_show.mode = 	MQ_MODE;
	}
}

void dht11_get_info_task(void)
{
	dht11.status = DHT11_Read_Data(&dht11.temp,&dht11.humi);//读取温湿度
	lm75.raw_temp = I2C_LM75read();
	lm75.real_temp = (float)(lm75.raw_temp)*0.125;
}


void mq_get_info_task(void)
{
	mq.type = MQTYPE;
	if(mq.type == 0)
	{
		mq.mq2_value = GetMQ4Value();
	}
	else if(mq.type ==1)
	{
		mq.mq4_value = GetMQ4Value();
	}
}


void oled_task(void)
{
	if (oled_show.mode == TEMPERATURE_MODE)
	{
	OLED_Clear() ; 
	OLED_ShowString(20,0,"information");
	OLED_ShowString(12,2,"temperature:");
		oled_show.temper  = lm75.real_temp;
	OLED_ShowNum(12,4,oled_show.temper,3,16);
	OLED_ShowString(40,4,"C");
	
	}
	else if (oled_show.mode == HUMIDTY_MODE)
	{
		OLED_Clear();
		OLED_ShowString(20,0,"information");
		OLED_ShowString(12,2,"humidtut:");
		oled_show.humi = dht11.humi;
		OLED_ShowNum(4,4,oled_show.humi,3,16);
		OLED_ShowString(40,4,"RH");
	}
	else if (oled_show.mode == MQ_MODE)
	{
		OLED_Clear();
		OLED_ShowString(20,0,"information");
		
		if (mq.type == 0)	//mq2模块
		{
		OLED_ShowString(12,2,"smog:");
		oled_show.mq_info = (int)(mq.mq2_value/7);
		OLED_ShowNum(12,4,oled_show.mq_info,3,16);
		OLED_ShowString(40,4,"PPM");
		}
		else if (mq.type == 1)	//mq4模块
		{
			OLED_ShowString(12,2,"methane:");
			oled_show.mq_info = (int)(mq.mq4_value/7);
			OLED_ShowNum(12,4,oled_show.mq_info,3,16);
			OLED_ShowString(40,4,"PPM");
		}
	}
	
	if (dht11.status!=0)
	{
		LEDR = 0;
	}
	else 
	{
		LEDR = 1;
	}
}

void uart_send_task(void)
{
	printf("temp %0.1f C\r",lm75.real_temp);
	printf("humi %d RH\r",dht11.humi);
	printf("meth %d PPM\r",mq.mq4_value/7);
}



void task_register(uint8_t task_id,uint16_t task_ticks,osPriority priority,void(*task_callback)(void))
{
	tasks_handle_container[task_id].is_used = 1;
	tasks_handle_container[task_id].task_id = task_id;
	tasks_handle_container[task_id].priority = priority;
	tasks_handle_container[task_id].task_ticks = task_ticks;
	tasks_handle_container[task_id].task_callback = task_callback;
}
void task_init(void)
{
	task_register(0,1,osPriorityAboveNormal,mode_switch_task); //0 modeswitch task	10MS周期
	task_register(1,1200,osPriorityNormal,dht11_get_info_task); //1 dht11_get_info_task
	task_register(2,10,osPriorityNormal,mq_get_info_task);		//mq获取消息任务
	task_register(3,20,osPriorityNormal,uart_send_task);			//串口发送任务
	task_register(4,1000,osPriorityNormal,oled_task);				//
}

void schdule_task(void)
{
	for(int i=0;i<MAX_TASKS;i++)
	{
		if (tasks_handle_container[i].is_used)
				if(i == tasks_handle_container[i].task_id)
					 if (tasks_handle_container[i].tick_time_now>=tasks_handle_container[i].task_ticks)
					 {
					tasks_handle_container[i].task_callback();
					tasks_handle_container[i].tick_time_now = 0;
					 }
				
	}
}

