#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
//Pin0  RS
//Pin1  RW
//Pin2  enable
//Pin3  DB0
//Pin4  DB1
//Pin5  DB2
//Pin6  DB3
//Pin7  DB4
//Pin8  DB5
//Pin9  DB6
//Pin10 DB7
//Pin11 CS1
//Pin12  CS2
//Pin13  reset
//Pin14 dummy pin
const uint16_t num1[8]={0x0001,0x0420,0x0410,0x07F8,0x07F8,0x0400,0x0400,0x0001};
const uint16_t num0[8]={0x0001,0x01E0,0x03F0,0x0408,0x0408,0x03F0,0x01E0,0x0001};
const uint16_t num2[8]={0x0001,0x0430,0x0638,0x0508,0x0588,0x0488,0x0470,0x0001};
const uint16_t num3[8]={0x0001,0x0330,0x0618,0x0408,0x04C8,0x04C8,0x0330,0x0001};
const uint16_t num4[8]={0x0001,0x00F8,0x00F8,0x0080,0x0080,0x07F8,0x07F8,0x0001};
const uint16_t num5[8]={0x0001,0x02F8,0x06D8,0x04D8,0x04D8,0x04D8,0x0398,0x0001};
const uint16_t num6[8]={0x0001,0x01F0,0x07F8,0x04C8,0x04C8,0x04D8,0x0390,0x0001};
const uint16_t num7[8]={0x0001,0x0618,0x0718,0x0198,0x00D8,0x0078,0x0038,0x0001};
const uint16_t num8[8]={0x0001,0x0330,0x06D8,0x06D8,0x06D8,0x06D8,0x0330,0x0001};
const uint16_t num9[8]={0x0001,0x04E0,0x06C8,0x04C8,0x04C8,0x07F8,0x01F0,0x0001};

void delay()  // Found to be working without any delay
{
	int i;
	for(i=0;i<1;i++)
	{
	}
}
uint16_t counter[8]={0x0,0b0001000,0b0010000,0b00110000,0b0100000,0b0101000,0b0110000,0b0111000};
uint16_t Ycount[8]={0x0,0b1000000,0b010000000,0b11000000,0b100000000,0b101000000,0b110000000,0b111000000};
void chipselect(int n);
void DisplayOn();
void SetY(int n);
void SetPage(uint16_t Pagepins);
void StartLine(uint16_t StartPins);
void DisplayData(uint16_t DisplayPins);
void clearscr(int n);
void DispNum();
void initializeLED()
{
	GPIO_InitTypeDef GPIO_InitStruct;

	    /* Clock for GPIOD */
	    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	    /* Set pins */
	    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4 | GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9 | GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
	    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	    GPIO_Init(GPIOE, &GPIO_InitStruct);
	    GPIO_SetBits(GPIOE,GPIO_Pin_13);
}



int main(void)
{
initializeLED();

clearscr(1);
chipselect(1);
DisplayOn();  // Display On
//SetY(0x0);
SetPage(0x0);
StartLine(0x0);
DispNum(num0);
DispNum(num1);
DispNum(num2);
DispNum(num3);
DispNum(num4);
DispNum(num5);
DispNum(num6);
DispNum(num7);
clearscr(2);
chipselect(2);
DisplayOn();
//SetY(0x0);   // set in DispNum
SetPage(0x0);
StartLine(0x0);
DispNum(num8);
DispNum(num9);
while(1)
	{

    }
}
void chipselect(int n){
	switch (n){
	case 1:
		GPIO_SetBits(GPIOE,GPIO_Pin_11);
		GPIO_ResetBits(GPIOE,GPIO_Pin_12);
		break;
	case 2:
		GPIO_SetBits(GPIOE,GPIO_Pin_12);
		GPIO_ResetBits(GPIOE,GPIO_Pin_11);
		break;
	case 3:
		GPIO_SetBits(GPIOE,GPIO_Pin_11);
		GPIO_SetBits(GPIOE,GPIO_Pin_12);
		break;
	}
	}
void DisplayOn()
{
    GPIO_SetBits(GPIOE, GPIO_Pin_3);
    GPIO_SetBits(GPIOE, GPIO_Pin_4);
    GPIO_SetBits(GPIOE, GPIO_Pin_5);
    GPIO_SetBits(GPIOE, GPIO_Pin_6);
    GPIO_SetBits(GPIOE, GPIO_Pin_7);
    GPIO_SetBits(GPIOE, GPIO_Pin_8);
    GPIO_SetBits(GPIOE, GPIO_Pin_2);
  delay();					//Display On

    GPIO_ResetBits(GPIOE,GPIO_Pin_2);

    GPIO_ResetBits(GPIOE,GPIO_Pin_3);
    GPIO_ResetBits(GPIOE,GPIO_Pin_4);
    GPIO_ResetBits(GPIOE,GPIO_Pin_5);
    GPIO_ResetBits(GPIOE,GPIO_Pin_6);
    GPIO_ResetBits(GPIOE,GPIO_Pin_7);
    GPIO_ResetBits(GPIOE,GPIO_Pin_8);
}
void SetY(int n)
{
	GPIO_SetBits(GPIOE, GPIO_Pin_9);
	        GPIO_SetBits(GPIOE, GPIO_Pin_5);
	        if(n >0 )
	        {
	        GPIO_SetBits(GPIOE, Ycount[n]);}
	        else {
	        GPIO_ResetBits(GPIOE,GPIO_Pin_3);
	        GPIO_ResetBits(GPIOE,GPIO_Pin_4);
	        GPIO_ResetBits(GPIOE,GPIO_Pin_5);
	        GPIO_ResetBits(GPIOE,GPIO_Pin_6);
	        GPIO_ResetBits(GPIOE,GPIO_Pin_7);
	        GPIO_ResetBits(GPIOE,GPIO_Pin_8);
	        }
	        GPIO_SetBits(GPIOE, GPIO_Pin_2);
	                delay();			//Set Y address

			GPIO_ResetBits(GPIOE,GPIO_Pin_2);
			if(n>0){
			GPIO_ResetBits(GPIOE, Ycount[n]);}
			GPIO_ResetBits(GPIOE,GPIO_Pin_9);
			GPIO_ResetBits(GPIOE,GPIO_Pin_5);
}
void SetPage(uint16_t Pagepins) // Default 6
{

	GPIO_SetBits(GPIOE, GPIO_Pin_6);
		    GPIO_SetBits(GPIOE, GPIO_Pin_7);
		    GPIO_SetBits(GPIOE, GPIO_Pin_8);
		    GPIO_SetBits(GPIOE, GPIO_Pin_10);
		    if(Pagepins >0 )
		    {
		    GPIO_SetBits(GPIOE, Pagepins);}
		    else {
		    GPIO_ResetBits(GPIOE,GPIO_Pin_3);
		    GPIO_ResetBits(GPIOE,GPIO_Pin_4);
		    GPIO_ResetBits(GPIOE,GPIO_Pin_5);
		    }
		    GPIO_SetBits(GPIOE, GPIO_Pin_2);
		                delay();	// Set page

			GPIO_ResetBits(GPIOE,GPIO_Pin_2);
			if (Pagepins >0){
			GPIO_ResetBits(GPIOE,Pagepins);}
			GPIO_ResetBits(GPIOE,GPIO_Pin_6);
			GPIO_ResetBits(GPIOE,GPIO_Pin_7);
			GPIO_ResetBits(GPIOE,GPIO_Pin_8);
			GPIO_ResetBits(GPIOE,GPIO_Pin_10);
}
void StartLine(uint16_t StartPins)
{
					GPIO_SetBits(GPIOE, GPIO_Pin_9);
					GPIO_SetBits(GPIOE, GPIO_Pin_10);
					if(StartPins >0 ){
					GPIO_SetBits(GPIOE, StartPins);}
					else {
						  GPIO_ResetBits(GPIOE,GPIO_Pin_3);
							        GPIO_ResetBits(GPIOE,GPIO_Pin_4);
							        GPIO_ResetBits(GPIOE,GPIO_Pin_5);
							        GPIO_ResetBits(GPIOE,GPIO_Pin_6);
							        GPIO_ResetBits(GPIOE,GPIO_Pin_7);
							        GPIO_ResetBits(GPIOE,GPIO_Pin_8);
					}
					GPIO_SetBits(GPIOE, GPIO_Pin_2);
					delay();			// Start Line

					GPIO_ResetBits(GPIOE,GPIO_Pin_2);
					if (StartPins >0){
					GPIO_ResetBits(GPIOE, StartPins);}
					GPIO_ResetBits(GPIOE,GPIO_Pin_9);
					GPIO_ResetBits(GPIOE,GPIO_Pin_10);
}
void DisplayData(uint16_t DisplayPins) //Default 14
{
					GPIO_SetBits(GPIOE,GPIO_Pin_0);
					if(DisplayPins >0){
					GPIO_SetBits(GPIOE,DisplayPins);}
					else {
						  GPIO_ResetBits(GPIOE,GPIO_Pin_3);
							        GPIO_ResetBits(GPIOE,GPIO_Pin_4);
							        GPIO_ResetBits(GPIOE,GPIO_Pin_5);
							        GPIO_ResetBits(GPIOE,GPIO_Pin_6);
							        GPIO_ResetBits(GPIOE,GPIO_Pin_7);
							        GPIO_ResetBits(GPIOE,GPIO_Pin_8);
							        GPIO_ResetBits(GPIOE,GPIO_Pin_9);
							        GPIO_ResetBits(GPIOE,GPIO_Pin_10);
					}
					GPIO_SetBits(GPIOE,GPIO_Pin_2);
					delay();			//	Display Data
					GPIO_ResetBits(GPIOE,GPIO_Pin_2);
					GPIO_ResetBits(GPIOE,GPIO_Pin_0);
					if(DisplayPins>0){
					GPIO_ResetBits(GPIOE,DisplayPins);}
}
void clearscr(int n)
{
	int i,k;
	if(n==1)
	{
	chipselect(1);
	}
	else if(n==2)
	{
	chipselect(2);
	}
	else if(n==3)
	{
	chipselect(3);
	}
	DisplayOn();
	SetY(0x0);
	for(k=0;k<8;k++)
	{
	SetPage(counter[k]);

	StartLine(0x0);
	for(i=0;i<64;i++)
	{
	DisplayData(0x0);
	}
	}
}
void DispNum(uint16_t num[])
{
	int i;
	static int p=0;
	SetY(p);
	for(i=0;i<8;i++)
	{
	DisplayData(num[i]);
	}
	p=p%8+1;
}
