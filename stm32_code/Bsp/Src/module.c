#include "module.h"
#include "lmiic.h"

u8 addr=0x90;
u8 addr1=0x91;
u8 buff[2]={0};
float data;

uint16_t I2C_LM75read(void)
{
	u16 readDATA=0x0000;
	u8 tempH=0x00;
	u8 tempL=0x00;
	
	IIC_Start();
	IIC_Send_Byte(addr);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x00);
	IIC_Wait_Ack();
	
	IIC_Start();
	IIC_Send_Byte(addr1);
	IIC_Wait_Ack();
	tempH=IIC_Read_Byte(1);
	tempL=IIC_Read_Byte(0);
	IIC_Stop();
	readDATA=(((u16)tempH<<8 )| tempL)>>5;
	return readDATA;
}