#ifndef __MODULE__H
#define __MODULE__H
#include "stm32f10x.h"

#define MQTYPE 1

typedef enum  {
	TEMPERATURE_MODE = 0,
	HUMIDTY_MODE = 1,
	MQ_MODE = 2,
} display_mode;

struct key_module {
	uint8_t key_wk;
	uint8_t key0;
	uint8_t key1;
	uint8_t key2;
	uint8_t key3;
	uint8_t key4;
};
struct dht11_module
{
	uint8_t temp;
	uint8_t humi;
	uint8_t status;
};

struct mq_module
{
	uint8_t type;
	uint16_t mq2_value;
	uint16_t mq4_value;
};

struct lm75a_module
{
	float real_temp;
	uint16_t raw_temp;
};

struct oled_display_module
{
	display_mode mode;
	int temper;
	int humi;
	int mq_info;
};
uint16_t I2C_LM75read(void);
#endif
