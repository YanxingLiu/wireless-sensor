#ifndef __DHT__11__H
#define __DHT__11__H
#include "sys.h"
//IO方向设置
#define DHT11_IO_IN()  {GPIOE->CRL &= 0XFFFFFFF0; GPIOE->CRL |= 8;}
#define DHT11_IO_OUT() {GPIOE->CRL &= 0XFFFFFFF0; GPIOE->CRL |= 3;}
////IO操作函数											   
#define	DHT11_DQ_OUT PEout(0) //数据端口	PE0
#define	DHT11_DQ_IN  PEin(0)  //数据端口	PE0 

u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11  
#endif
