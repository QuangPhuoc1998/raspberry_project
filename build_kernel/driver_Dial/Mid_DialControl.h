#ifndef _MID_DIAL_CONTROL_H_
#define _MID_DIAL_CONTROL_H_

#include "main.h"

#define GPIO_CHANNEL_A (2)
#define GPIO_CHANNEL_B (3)
#define GPIO_CHANNEL_P (4)

#define DIAL_READ_CHANNEL_A gpio_get_value(GPIO_CHANNEL_A)
#define DIAL_READ_CHANNEL_B gpio_get_value(GPIO_CHANNEL_B)
#define DIAL_READ_CHANNEL_P gpio_get_value(GPIO_CHANNEL_P)

typedef enum
{
	NO_CHANGE = 0x00,
	UP = 0xF0,
	DOWN = 0x0F
} DialDirection_t;

uint8_t Mid_DialInit(void);
void Mid_DialDeinit(void);
void Mid_DialHandler(void);
uint8_t Mid_DialGetDirection(void);

#endif // _MID_DIAL_CONTROL_H_
