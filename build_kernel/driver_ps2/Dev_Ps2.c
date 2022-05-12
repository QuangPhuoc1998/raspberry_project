#include "main.h"

/*--- Define for soft SPI ---*/
#define DELAY_TIME ndelay(5000);
#define delay_us(us) udelay(us)

uint8_t PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY;         //PS2 Related variables 

uint16_t Handkey;	//  Key value reading , Zero hour storage .
uint8_t Comd[2]={
    0x01,0x42};	// Start ordering . Request data 
uint8_t Data[9]={
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; // Data storage array 
uint16_t MASK[]={
    
    PSB_SELECT,
    PSB_L3,
    PSB_R3 ,
    PSB_START,
    PSB_PAD_UP,
    PSB_PAD_RIGHT,
    PSB_PAD_DOWN,
    PSB_PAD_LEFT,
    PSB_L2,
    PSB_R2,
    PSB_L1,
    PSB_R1 ,
    PSB_GREEN,
    PSB_RED,
    PSB_BLUE,
    PSB_PINK
	};

/*--- #define for hard SPI ---*/

#define READ_KEY_LENGTH 9
uint8_t s_aubReadKeyValue[READ_KEY_LENGTH] = {0x80, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // 1

/*--- Using Hard SPI ---*/
void Dev_Ps2Init(void)
{

}
void Dev_Ps2Read(uint8_t * Rxdata)
{
    Hal_SpiWrite(s_aubReadKeyValue, Rxdata, READ_KEY_LENGTH);
}
/*--- Using Soft SPI ---*/
int Dev_Ps2SoftInit(void)
{
    /*--- Setting GPIO ---*/
    /*-> MOSI */
    if(gpio_is_valid(MOSI) == false){
    pr_err("GPIO %d is not valid\n", MOSI);
        goto r_gpio;
    }
    
    //Requesting the GPIO
    if(gpio_request(MOSI,"MOSI") < 0){
        pr_err("ERROR: GPIO %d request\n", MOSI);
        goto r_gpio;
    }
    
    //configure the GPIO as output
    gpio_direction_output(MOSI, 0);
    /*-> MISO */
    if(gpio_is_valid(MISO) == false){
        pr_err("GPIO %d is not valid\n", MISO);
        goto r_gpio;
    }
    
    //Requesting the GPIO
    if(gpio_request(MISO,"MISO") < 0){
        pr_err("ERROR: GPIO %d request\n", MISO);
        goto r_gpio;
    }
    
    //configure the GPIO as input
    gpio_direction_input(MISO);
    /*-> CS */
    if(gpio_is_valid(CS) == false){
        pr_err("GPIO %d is not valid\n", CS);
        goto r_gpio;
    }
    
    //Requesting the GPIO
    if(gpio_request(CS,"CS") < 0){
        pr_err("ERROR: GPIO %d request\n", CS);
        goto r_gpio;
    }
    
    //configure the GPIO as output
    gpio_direction_output(CS, 0);
    /*-> CLK */
    if(gpio_is_valid(CLK) == false){
        pr_err("GPIO %d is not valid\n", CLK);
        goto r_gpio;
    }
    
    //Requesting the GPIO
    if(gpio_request(CLK,"CLK") < 0){
        pr_err("ERROR: GPIO %d request\n", CLK);
        goto r_gpio;
    }
    
    //configure the GPIO as output
    gpio_direction_output(CLK, 0);

    return 0;

    r_gpio:
    gpio_free(MOSI);
    gpio_free(MISO);
    gpio_free(CS);
    gpio_free(CLK);

    return -1;
}
void Dev_Ps2SoftDeInit(void)
{
    // bps_gpio_deinit();
    
    gpio_free(MOSI);
    gpio_free(MISO);
    gpio_free(CS);
    gpio_free(CLK);
    
}

/**************************************************************************  The functionality : Send command to handle   Entrance parameters :CMD Instructions   return   value : nothing  **************************************************************************/
void PS2_Cmd(uint8_t CMD)
{
    
	volatile uint16_t ref=0x01;
	Data[1] = 0;
	for(ref=0x01;ref<0x0100;ref<<=1)
	{
    
		if(ref&CMD)
		{
    
			DO_H;                   // Output one control bit 
		}
		else DO_L;

		CLK_H;                        // The clock goes up 
		DELAY_TIME;
		CLK_L;
		DELAY_TIME;
		CLK_H;
		if(DI)
			Data[1] = ref|Data[1];
	}
	delay_us(16);
}
/**************************************************************************  The functionality : Judge whether it is red light mode ,0x41= Simulate green light ,0x73= Simulate a red light   Entrance parameters :CMD Instructions   return   value :0, Red light mode   other , Other modes  **************************************************************************/
uint8_t PS2_RedLight(void)
{
    
	CS_L;
	PS2_Cmd(Comd[0]);  // Start ordering 
	PS2_Cmd(Comd[1]);  // Request data 
	CS_H;
	if( Data[1] == 0X73)   return 0 ;
	else return 1;
}
/**************************************************************************  The functionality : Read handle data   Entrance parameters : nothing   return   value : nothing  **************************************************************************/
void PS2_ReadData(void)
{
    
	volatile uint8_t byte=0;
	volatile uint16_t ref=0x01;
	CS_L;
	PS2_Cmd(Comd[0]);  // Start ordering 
	PS2_Cmd(Comd[1]);  // Request data 
	for(byte=2;byte<9;byte++)          // Start taking data 
	{
    
		for(ref=0x01;ref<0x100;ref<<=1)
		{
    
			CLK_H;
			DELAY_TIME;
			CLK_L;
			DELAY_TIME;
			CLK_H;
		      if(DI)
		      Data[byte] = ref|Data[byte];
		}
        delay_us(16);
	}
	CS_H;
}
/**************************************************************************  The functionality : Yes, read it out PS2 Data processing , Only the key part   Entrance parameters :CMD Instructions   return   value : nothing  // When only one key is pressed, it is 0,  Not pressed is 1 **************************************************************************/
uint8_t PS2_DataKey()
{
    
	uint8_t index;

	PS2_ClearData();
	PS2_ReadData();

	Handkey=(Data[4]<<8)|Data[3];     // This is a 16 A button   Press for 0,  Not pressed is 1
	for(index=0;index<16;index++)
	{
    	    
		if((Handkey&(1<<(MASK[index]-1)))==0)
		return index+1;
	}
	return 0;          // There's no key press 
}
/**************************************************************************  The functionality : Send command to handle   Entrance parameters : Get an analog of a rocker   Range 0~256  return   value : nothing  **************************************************************************/
uint8_t PS2_AnologData(uint8_t button)
{
    
	return Data[button];
}

// Clear data buffer 
void PS2_ClearData()
{
    
	uint8_t a;
	for(a=0;a<9;a++)
		Data[a]=0x00;
}
/******************************************************  The functionality :  Handle vibration function , Calls: void PS2_Cmd(u8 CMD);  Entrance parameters : motor1: Right side small vibration motor  0x00 Turn off , Others open  motor2: Left large vibration motor  0x40~0xFF  The motor is on , The bigger the value is.   The greater the vibration   return   value : nothing  ******************************************************/
void PS2_Vibration(uint8_t motor1, uint8_t motor2)
{
	CS_L;
	delay_us(16);
    PS2_Cmd(0x01);  // Start ordering 
	PS2_Cmd(0x42);  // Request data 
	PS2_Cmd(0X00);
	PS2_Cmd(motor1);
	PS2_Cmd(motor2);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS_H;
	delay_us(16);  
}
/**************************************************************************  The functionality :short poll  Entrance parameters : nothing   return   value : nothing  **************************************************************************/
void PS2_ShortPoll(void)
{
    
	CS_L;
	delay_us(16);

	PS2_Cmd(0x01);  
	PS2_Cmd(0x42);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	CS_H;
	delay_us(16);	
}
/**************************************************************************  The functionality : Enter the configuration   Entrance parameters : nothing   return   value : nothing  **************************************************************************/
void PS2_EnterConfing(void)
{
    
    CS_L;
	delay_us(16);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x43);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x01);
	PS2_Cmd(0x00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS_H;
	delay_us(16);
}
/**************************************************************************  The functionality : Send mode settings   Entrance parameters : nothing   return   value : nothing  **************************************************************************/
void PS2_TurnOnAnalogMode(void)
{
    
	CS_L;
	PS2_Cmd(0x01);  
	PS2_Cmd(0x44);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x01); //analog=0x01;digital=0x00  The software sets the sending mode 
	PS2_Cmd(0x03); //Ox03 Latch setting , That is, you can't press the key “MODE” Set the mode .
				   //0xEE Do not latch software settings , You can press the key “MODE” Set the mode .
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS_H;
	delay_us(16);
}
/**************************************************************************  The functionality : Vibration setting   Entrance parameters : nothing   return   value : nothing  **************************************************************************/
void PS2_VibrationMode(void)
{
    
	CS_L;
	delay_us(16);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x4D);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0X01);
	CS_H;
	delay_us(16);	
}
/**************************************************************************  The functionality : Complete and save the configuration   Entrance parameters : nothing   return   value : nothing  **************************************************************************/
void PS2_ExitConfing(void)
{
    
    CS_L;
	delay_us(16);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x43);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	CS_H;
	delay_us(16);
}
/**************************************************************************  The functionality : Handle configuration initialization   Entrance parameters : nothing   return   value : nothing  **************************************************************************/
void PS2_SetInit(void)
{
	PS2_ShortPoll();
	PS2_ShortPoll();
	PS2_ShortPoll();
	PS2_EnterConfing();		// Enter configuration mode 
	PS2_TurnOnAnalogMode();	//“ traffic lights ” Configuration mode , And choose whether to save 
	PS2_VibrationMode(); // Turn on vibration mode 
	PS2_ExitConfing();		// Complete and save the configuration 
}
void PS2_Read(void)
{
  		PS2_KEY=PS2_DataKey();          // Read the key value 
        PS2_LX=PS2_AnologData(PSS_LX);  // Read the remote sensing on the left X Analog quantity in axial direction 
        PS2_LY=PS2_AnologData(PSS_LY);  // Read the remote sensing on the left Y Analog quantity in axial direction 
        PS2_RX=PS2_AnologData(PSS_RX);  // Read the remote sensing data on the right X Analog quantity in axial direction 
        PS2_RY=PS2_AnologData(PSS_RY);  // Read the remote sensing data on the right Y Analog quantity in axial direction 
}