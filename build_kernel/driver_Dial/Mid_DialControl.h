#ifndef _MID_DIAL_CONTROL_H_
#define _MID_DIAL_CONTROL_H_

#include "main.h"

#define GPIO_CHANNEL_A (1)
#define GPIO_CHANNEL_B (2)
#define GPIO_CHANNEL_P (3)

#define DIAL_READ_CHANNEL_A HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)
#define DIAL_READ_CHANNEL_B HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6)
#define DIAL_READ_CHANNEL_P HAL_GPIO_ReadPin(GPIOJ, GPIO_PIN_1)

typedef enum
{
	NO_CHANGE = 0x00,
	UP = 0xF0,
	DOWN = 0x0F
} DialDirection_t;

void Mid_DialInit(void);
void Mid_DialDeinit(void);
void Mid_DialHandler(void);
uint8_t Mid_DialGetDirection(void);

#endif // _MID_DIAL_CONTROL_H_
