#ifndef __MQ4__H
#define __MQ4__H
#include "sys.h"
void MQ4_ADC_init(void);
u16 GetMQ4Value(void);
int Read_MQ4_DOUT_Data(void);
void adc_init(void);
u16 get_adc(void);
#endif
