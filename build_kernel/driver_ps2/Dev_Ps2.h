#ifndef _DEV_PS2_H
#define _DEV_PS2_H

#include "main.h"


#define MOSI    20
#define MISO    19
#define CS      18
#define CLK     21

#define DI gpio_get_value(MISO) 

#define DO_H gpio_set_value(MOSI, 1)
#define DO_L gpio_set_value(MOSI, 0)

#define CS_H gpio_set_value(CS, 1)
#define CS_L gpio_set_value(CS, 0)

#define CLK_H gpio_set_value(CLK, 1)
#define CLK_L gpio_set_value(CLK, 0)

//These are our button constants
#define PSB_SELECT 1
#define PSB_L3 2
#define PSB_R3 3
#define PSB_START 4
#define PSB_PAD_UP 5
#define PSB_PAD_RIGHT 6
#define PSB_PAD_DOWN 7
#define PSB_PAD_LEFT 8
#define PSB_L2 9
#define PSB_R2 10
#define PSB_L1 11
#define PSB_R1 12
#define PSB_GREEN 13
#define PSB_RED 14
#define PSB_BLUE 15
#define PSB_PINK 16

#define PSB_TRIANGLE 13
#define PSB_CIRCLE 14
#define PSB_CROSS 15
#define PSB_SQUARE 16

//#define WHAMMY_BAR 8

//These are stick values
#define PSS_RX 5 // Right rocker X Axis data 
#define PSS_RY 6
#define PSS_LX 7
#define PSS_LY 8

extern uint8_t Data[9];
extern uint16_t MASK[16];
extern uint16_t Handkey;
extern uint8_t PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY;         //PS2 Related variables

void Dev_Ps2Init(void);
void Dev_Ps2Read(uint8_t * Rxdata);
int Dev_Ps2SoftInit(void);
void Dev_Ps2SoftDeInit(void);

void PS2_Init(void);
uint8_t PS2_RedLight(void);   // Judge whether it is red light mode 
void PS2_ReadData(void); // Read handle data 
void PS2_Cmd(uint8_t CMD);		  // Send command to handle 
uint8_t PS2_DataKey(void);		  // Key value reading 
uint8_t PS2_AnologData(uint8_t button); // Get an analog of a rocker 
void PS2_ClearData(void);	  // Clear data buffer 
void PS2_Vibration(uint8_t motor1, uint8_t motor2);// Vibration setting motor1 0xFF open , Other customs ,motor2 0x40~0xFF

void PS2_EnterConfing(void);	 // Enter the configuration 
void PS2_TurnOnAnalogMode(void); // Send analog quantity 
void PS2_VibrationMode(void);    // Vibration setting 
void PS2_ExitConfing(void);	     // Complete the configuration 
void PS2_SetInit(void);		     // Configuration initialization 

void PS2_Read(void);  // Read PS2 Control amount of handle 
#endif // _DEV_PS2_H