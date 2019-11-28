#include "mq4.h"
#include "stm32f10x.h"
#include "stm32f10x_adc.h"
void MQ4_ADC_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO|RCC_APB2Periph_ADC2,ENABLE);
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//12M  最大14M 设置ADC时钟（ADCCLK）
	ADC_DeInit(ADC2);
 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;//ADC
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;	//模拟输入
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
 
 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; 
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; 
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; 
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 
	ADC_InitStructure.ADC_NbrOfChannel = 1; 
	ADC_Init(ADC2, &ADC_InitStructure);
	
	//设置指定ADC的规则组通道，设置它们的转化顺序和采样时间
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_239Cycles5);
	
	//内部温度传感器是在ADC1通道16的。
	ADC_RegularChannelConfig(ADC2,ADC_Channel_1,1,ADC_SampleTime_239Cycles5);
//	ADC_TempSensorVrefintCmd(ENABLE);//打开内部温度传感器使能
	ADC_Cmd(ADC2,ENABLE);	
 
	ADC_ResetCalibration(ADC2);//重置指定的ADC的校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC2));//获取ADC重置校准寄存器的状态
	
	ADC_StartCalibration(ADC2);//开始指定ADC的校准状态
	while(ADC_GetCalibrationStatus(ADC2));//获取指定ADC的校准程序
 
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);//使能或者失能指定的ADC的软件转换启动功能
}
u16 test_adc_value;
u16 GetMQ4Value(void)
{
			uint16_t ADCVal;
			float Voltage;
			uint16_t ppm;
			ADC_SoftwareStartConvCmd(ADC2, ENABLE);
	    while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));
			ADCVal = ADC_GetConversionValue(ADC2);
			test_adc_value = ADCVal;
			Voltage = ADCVal * 3.3 / 4096;
	//无天然气的环境下，实测AOUT端的电压为0.5V，当检测到天然气时，电压每升高0.1V,实际被测气体浓度增加200ppm
			ppm = (Voltage - 0.5) / 0.1 * 200;
			return ppm;
			//return ADCVal;
}

int Read_MQ4_DOUT_Data(void)
{
	int status;
	status = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3);
	return status;
}

void adc_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
	GPIO_Init(GPIOA,&GPIO_InitStructure); 
	
	ADC_DeInit(ADC1);
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1,&ADC_InitStructure); 
	
	 ADC_Cmd(ADC1,ENABLE); 
	 
	 ADC_ResetCalibration(ADC1);
	 while(ADC_GetResetCalibrationStatus(ADC1));
	 ADC_StartCalibration(ADC1);
	  while(ADC_GetCalibrationStatus(ADC1));
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

u16 get_adc(void)
{
	ADC_RegularChannelConfig(ADC1,1,1,ADC_SampleTime_239Cycles5);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	return ADC_GetConversionValue(ADC1); 
}

