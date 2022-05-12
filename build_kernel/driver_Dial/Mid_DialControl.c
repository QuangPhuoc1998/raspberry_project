#include "Mid_DialControl.h"

uint8_t g_ubEncoderValue[3] = {0};
uint8_t g_ubEncoderBuffer[3][2] = {0};
uint8_t g_ubUpDownMoveValue = NO_CHANGE;
uint8_t g_bMoveEncoderCount = 0;
uint8_t g_ubEncoderCount = 0;

void _DialScan(void);
void _DialClearBuffer(void);

uint8_t Mid_DialInit(void)
{
    /*--- Checking the GPIO ---*/
    if(gpio_is_valid(GPIO_CHANNEL_A) == false)
    {
        pr_err("GPIO %d is not valid\n", GPIO_CHANNEL_A);
        return 1;
    }
    if(gpio_is_valid(GPIO_CHANNEL_B) == false)
    {
        pr_err("GPIO %d is not valid\n", GPIO_CHANNEL_B);
        return 1;
    }
    if(gpio_is_valid(GPIO_CHANNEL_P) == false)
    {
        pr_err("GPIO %d is not valid\n", GPIO_CHANNEL_P);
        return 1;
    }
    /*--- Request GPIO ---*/
    if(gpio_request(GPIO_CHANNEL_A,"GPIO_CHANNEL_A") < 0)
    {
        pr_err("ERROR: GPIO %d request\n", GPIO_CHANNEL_A);
        gpio_free(GPIO_CHANNEL_A);
        return 1;
    }
    if(gpio_request(GPIO_CHANNEL_B,"GPIO_CHANNEL_B") < 0)
    {
        pr_err("ERROR: GPIO %d request\n", GPIO_CHANNEL_B);
        gpio_free(GPIO_CHANNEL_B);
        return 1;
    }
    if(gpio_request(GPIO_CHANNEL_P,"GPIO_CHANNEL_P") < 0)
    {
        pr_err("ERROR: GPIO %d request\n", GPIO_CHANNEL_P);
        gpio_free(GPIO_CHANNEL_P);
        return 1;
    }

    gpio_direction_input(GPIO_CHANNEL_A);
    gpio_direction_input(GPIO_CHANNEL_B);
    gpio_direction_input(GPIO_CHANNEL_P);

    return 0;
}
void Mid_DialDeinit(void)
{
    gpio_unexport(GPIO_CHANNEL_A);
    gpio_unexport(GPIO_CHANNEL_B);
    gpio_unexport(GPIO_CHANNEL_P);

    gpio_free(GPIO_CHANNEL_A);
    gpio_free(GPIO_CHANNEL_B);
    gpio_free(GPIO_CHANNEL_P);
}
void Mid_DialHandler(void)
{
	_DialScan();
	/*--- state 1 ---*/
	if(g_ubEncoderCount == 0)
	{
		if(g_ubEncoderValue[0] == g_ubEncoderValue[1])
		{
			g_ubEncoderBuffer[g_ubEncoderCount][0] = g_ubEncoderValue[0];
			g_ubEncoderBuffer[g_ubEncoderCount][1] = g_ubEncoderValue[1];
			g_ubEncoderCount++;
		}
	}
	else if(g_ubEncoderCount < 3)
	{
		if(g_ubEncoderBuffer[g_ubEncoderCount-1][0] != g_ubEncoderValue[0] || g_ubEncoderBuffer[g_ubEncoderCount-1][1] != g_ubEncoderValue[1])
		{
			g_ubEncoderBuffer[g_ubEncoderCount][0] = g_ubEncoderValue[0];
			g_ubEncoderBuffer[g_ubEncoderCount][1] = g_ubEncoderValue[1];
			g_ubEncoderCount++;
		}
	}
	else if(g_ubEncoderCount < 4)
	{
		if(g_ubEncoderBuffer[0][0] == 0 && g_ubEncoderBuffer[0][1] == 0)
		{
			if  ((g_ubEncoderBuffer[1][0] == 0 && g_ubEncoderBuffer[1][1] == 1)
				&& (g_ubEncoderBuffer[2][0] == 1 && g_ubEncoderBuffer[2][1] == 1))
			{
				g_ubUpDownMoveValue = DOWN;
				g_bMoveEncoderCount--;
			}
			else if ((g_ubEncoderBuffer[1][0] == 1 && g_ubEncoderBuffer[1][1] == 0)
						&& (g_ubEncoderBuffer[2][0] == 1 && g_ubEncoderBuffer[2][1] == 1))
			{
				g_ubUpDownMoveValue = UP;
				g_bMoveEncoderCount++;
			}
		}
		else if(g_ubEncoderBuffer[0][0] == 1 && g_ubEncoderBuffer[0][1] == 1)
		{
			if  ((g_ubEncoderBuffer[1][0] == 0 && g_ubEncoderBuffer[1][1] == 1)
				&& (g_ubEncoderBuffer[2][0] == 0 && g_ubEncoderBuffer[2][1] == 0))
			{
				g_ubUpDownMoveValue = UP;
				g_bMoveEncoderCount++;
			}
			else if ((g_ubEncoderBuffer[1][0] == 1 && g_ubEncoderBuffer[1][1] == 0)
						&& (g_ubEncoderBuffer[2][0] == 0 && g_ubEncoderBuffer[2][1] == 0))
			{
				g_ubUpDownMoveValue = DOWN;
				g_bMoveEncoderCount--;
			}
			else
			{
				g_ubUpDownMoveValue = NO_CHANGE;
			}
		}
		g_ubEncoderCount = 0;
		_DialClearBuffer();
		
	}
}
uint8_t Mid_DialGetDirection(void)
{
	return 0;
}


void _DialScan(void)
{
	g_ubEncoderValue[0] = DIAL_READ_CHANNEL_A;
	g_ubEncoderValue[1] = DIAL_READ_CHANNEL_B;
	g_ubEncoderValue[2] = DIAL_READ_CHANNEL_P;
	
}
void _DialClearBuffer(void)
{
	g_ubEncoderBuffer[0][0] = 0;
	g_ubEncoderBuffer[1][0] = 0;
	g_ubEncoderBuffer[2][0] = 0;
	g_ubEncoderBuffer[0][1] = 0;
	g_ubEncoderBuffer[1][1] = 0;
	g_ubEncoderBuffer[2][1] = 0;
}
