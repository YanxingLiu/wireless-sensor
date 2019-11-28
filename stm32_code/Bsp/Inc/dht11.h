#ifndef __DHT__11__H
#define __DHT__11__H
#include "sys.h"
//IO��������
#define DHT11_IO_IN()  {GPIOE->CRL &= 0XFFFFFFF0; GPIOE->CRL |= 8;}
#define DHT11_IO_OUT() {GPIOE->CRL &= 0XFFFFFFF0; GPIOE->CRL |= 3;}
////IO��������											   
#define	DHT11_DQ_OUT PEout(0) //���ݶ˿�	PE0
#define	DHT11_DQ_IN  PEin(0)  //���ݶ˿�	PE0 

u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11  
#endif
