#include "stm32f10x.h"
#include "keyvalues.h"
#include "lcd.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
#define CHARWIDTH   34
#define CHARHEIGHT  30
#define STARTX       0
#define STARTY     190
#define SPACEX      12
#define SPACEY       8
#define FINGER      15
#define FINGERWIDTH 10
#define GAP         50

void Delayus(int duration);
void RGBLED_CONFIG(void);
void Row3Column1 (void);
void KEY_CONFIG(void);
void TimerConfig(void);
void MoveFinger(int f1,int f2, int f3, int f4, int f5);
void keypad1(void);
void keypad2(void);
void keypad3(void);
void keypad4(void);
void inputUI(void);
void convert(void);
char text[1000];
int textindex=0;
int key_value;
int i=0;
int k = 0;
int x = 0;
int y = 0;
char buffer[30];
int strindex = 0;
int strnum[100];
char str1[100];
char truestr[100];
int keycordx[]={STARTX,STARTX+CHARWIDTH,STARTX+2*CHARWIDTH,STARTX+3*CHARWIDTH,STARTX+4*CHARWIDTH,STARTX+5*CHARWIDTH,STARTX+6*CHARWIDTH,STARTX,STARTX+CHARWIDTH,STARTX+2*CHARWIDTH,STARTX+3*CHARWIDTH,STARTX+4*CHARWIDTH,STARTX+5*CHARWIDTH,STARTX+6*CHARWIDTH,STARTX,STARTX+CHARWIDTH,STARTX+2*CHARWIDTH,STARTX+3*CHARWIDTH,STARTX+4*CHARWIDTH,STARTX+5*CHARWIDTH,STARTX+6*CHARWIDTH,STARTX,STARTX+CHARWIDTH,STARTX+2*CHARWIDTH,STARTX+3*CHARWIDTH,STARTX+4*CHARWIDTH,STARTX+5*CHARWIDTH};
int keycordy[]={STARTY,STARTY,STARTY,STARTY,STARTY,STARTY,STARTY,STARTY+CHARHEIGHT,STARTY+CHARHEIGHT,STARTY+CHARHEIGHT,STARTY+CHARHEIGHT,STARTY+CHARHEIGHT,STARTY+CHARHEIGHT,STARTY+CHARHEIGHT,STARTY+2*CHARHEIGHT,STARTY+2*CHARHEIGHT,STARTY+2*CHARHEIGHT,STARTY+2*CHARHEIGHT,STARTY+2*CHARHEIGHT,STARTY+2*CHARHEIGHT,STARTY+2*CHARHEIGHT,STARTY+3*CHARHEIGHT,STARTY+3*CHARHEIGHT,STARTY+3*CHARHEIGHT,STARTY+3*CHARHEIGHT,STARTY+3*CHARHEIGHT};

char words[5][20];
int wordlist[10] = {0,0,0,0,0,0,0,0,0,0};
int kernel[4] = {17,11,7,5};
int wordamount=0;
int act=0;
int w;
int signs[20];
int sindex=0;
int m = 0;
int p = 0;
int k1 = 0;
int ke = 0;
int flag = 0;	
	
int Fingers[37][5]={{110,90,90,90,90},
    {120,150,120,120,120},
    {120,150,150,120,120},
    {100,150,150,120,120},
    {110,150,150,150,150},
    {100,150,150,150,150},
    {110,150,150,150,120},
    {110,150,150,120,150},
    {110,150,120,150,150},
    {110,120,150,150,150},
    {100,120,120,120,120},
    {130,150,150,150,150},
    {120,90,90,90,90},
    {120,150,120,120,120},
    {110,120,120,120,120},
    {120,120,150,150,150},
    {100,150,120,120,120},
    {100,150,150,120,120},
    {110,120,120,120,150},
    {110,120,120,120,150},
    {100,150,150,120,120},
    {100,150,120,120,120},
    {110,80,80,80,80},
    {110,80,80,80,80},
    {110,90,90,90,90},
    {100,150,150,150,150},
    {100,150,80,80,80},
    {120,150,150,120,120},
    {120,120,120,120,120},
    {100,120,120,120,120},
    {110,150,150,120,120},
    {110,150,150,120,120},
    {110,150,150,150,120},
    {130,90,120,120,120},
    {100,120,120,120,150},
    {110,150,120,120,150},
		{100,100,100,100,150}};
  char str2[80] = "i love you";
  const char s[2] = " ";
  char* token;
    //char temp[20];
  int temp = 0;
int main()
{	
	int dummy = 0;
	KEY_CONFIG();
	
	GPIOC->ODR = 0x0000;
	Delayus(5000);
	LCD_INIT();
  //LCD_Clear(0,0,180,220,BLUE2);
	TimerConfig();
		RGBLED_CONFIG();
	    wordlist[0] = ('l'-'a'+1)*kernel[0] +('o'-'a'+1)*kernel[1] +('v'-'a'+1)*kernel[2] + ('e'-'a'+1)*kernel[3];
   // printf(" love is %d\n",wordlist[0]);
    wordamount++;
		//	LCD_FillTriangle(0,0,200,200,214,150,BLACK);
	LCD_DrawSpPoly(0,0,240,0,240,100,200,130,BLUE);
	LCD_FillTriangle(0,0,0,50,200,130,BLUE);
	LCD_FillTriangle(130,90,200,130,240,100.,BLUE);
  LCD_DrawString(0,0," ELEC3300 PROJECT");
	LCD_DrawString(0,15," Group 30 ");
	LCD_DrawBoldLineV(180,95,180,20,RED);
	LCD_DrawBoldLineV(182,95,182,20,RED);
	LCD_DrawBoldLineH(165,58,197,58,RED);
	LCD_DrawBoldLineH(165,60,197,60,RED);
	LCD_DrawBoldLineV(165,70,165,45,RED);
	LCD_DrawBoldLineV(167,70,167,45,RED);
	LCD_DrawBoldLineV(197,70,197,45,RED);
	LCD_DrawBoldLineV(199,70,199,45,RED);
	LCD_DrawString(15,120,"To input words");
	LCD_DrawString(15,135,"Press K2");
	LCD_DrawString(15,160,"To confirm");
	LCD_DrawString(15,175,"Press K1");
	
  LCD_DrawSpPoly(FINGER+35,360,FINGER+35,260,FINGER+FINGERWIDTH+35,260, FINGER+FINGERWIDTH+35, 360 ,BLUE);
	  LCD_DrawSpPoly(FINGER+GAP+20,360,FINGER+GAP+20,220,FINGER+FINGERWIDTH+20+GAP,220, FINGER+FINGERWIDTH+20+GAP, 360 ,BLUE);
	  LCD_DrawSpPoly(FINGER+2*GAP,360,FINGER+2*GAP,200,FINGER+FINGERWIDTH+2*GAP,200, FINGER+FINGERWIDTH+2*GAP, 360 ,RED);
	  LCD_DrawSpPoly(FINGER+3*GAP-20,360,FINGER-20+3*GAP,210,FINGER+FINGERWIDTH-20+3*GAP,210, FINGER+FINGERWIDTH-20+3*GAP, 360 ,BLUE);
	  LCD_DrawSpPoly(FINGER+4*GAP-35,360,FINGER-35+4*GAP,250,FINGER+FINGERWIDTH-35+4*GAP,250, FINGER+FINGERWIDTH-35+4*GAP, 360 ,BLUE);
	while( 1 )
	{
  /* task 4 
		GPIOB->BRR = GPIO_Pin_5;
		Delayus(1);
		GPIOB->BSRR = GPIO_Pin_5;
		Delayus(1);
		
	*/
		//LCD_DrawSpPoly(0,0,180,220,40,100,GREEN);

		dummy = GPIOC->IDR;
		if (dummy & 0x2000) //if it is pressed, LOGIC_HIGH
		{ GPIOB->BRR = GPIO_Pin_1;
			inputUI();
		}
		else
		    GPIOB->BSRR = GPIO_Pin_1;
		
		
	//	keypad2();
	//	keypad3(&i, &startx, &starty);
	//keypad1();	
		
	}
}


void inputUI()
{
	char todraw = 'a';
	int i = 0;
	int amount=0;
	int startx = STARTX;
	int starty = STARTY;
  int x,y;
	char* inputstr;
	LCD_Clear(0,0,240,320,WHITE);
	LCD_DrawLine(STARTX,STARTY-8,240,STARTY-8,BLACK);
	for(i=0,todraw='a';i<26;i++,todraw++)
	{
		LCD_DrawChar(startx+SPACEX,starty+SPACEY,todraw);
		startx += CHARWIDTH;
		if (i == 6 | i == 13 | i == 20)
		{
			startx = 0;
			starty += CHARHEIGHT;
		}
	}
		
  //LCD_DrawSquare2(0,190,34,220,BLUE2);
  k = 0;
 x = 0;
	y = 0;
	LCD_DrawSquare2(keycordx[x],keycordy[y],keycordx[x]+CHARWIDTH,keycordy[y]+CHARHEIGHT,BLUE);
	while(1)
	{
		//if (GPIOC->IDR & 0x2000) //if it is pressed, LOGIC_HIGH
			//break;
		//keypad2();
	keypad3();
		keypad2();
		keypad4();
		// LCD_DrawSquare2(startx,starty,startx+CHARWIDTH,starty+CHARHEIGHT,RED);
		//keypad4();
if (GPIOA->IDR & 0x0001) 
		{ 
		//	MoveFinger(150,150,150,100,150);
		//Delayus(5000000);
		//	LCD_DrawString(50,50,"hello");
			convert();
			amount = sindex;
			for (sindex = 0;sindex < amount+1;sindex++)
			{
				if(sindex<amount)
				{
					MoveFinger(Fingers[signs[sindex]][0],Fingers[signs[sindex]][1],Fingers[signs[sindex]][2],Fingers[signs[sindex]][3],Fingers[signs[sindex]][4]);
					Delayus(5000000);
				}
				else
				{
					MoveFinger(100,150,150,150,150);
					Delayus(3000000);
          break;
				}
			}
			for (sindex = 0;sindex<20;sindex++)
			{
				signs[sindex] = 0;
			}
			sindex = 0;
			memset(truestr, 0, sizeof(truestr));
			memset(str1, 0, sizeof(str1));
			memset(strnum, 0, sizeof(strnum));
			memset(buffer, 0, sizeof(buffer));
			
			break;
		}
		
	}
	LCD_Clear(0,0,240,360,WHITE);
	LCD_DrawString(40,100,"END, Now press reset");
	Delayus(10000000);
	
	
	//return inputstr;
	
}




void RGBLED_CONFIG (void)
{		
	/* Task 1: Configure the RGB LED as output */

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_0 | GPIO_Pin_1; // Pin_5 for R, Pin_0 for G, Pin_1 for B
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	

	
}



void TimerConfig(void)
{

	//parameter for Task 2
	
	//GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 |  GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

  	TIM_TimeBaseStructure.TIM_Period = 1000; 
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    

	
	  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 500;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
			  TIM_OC2PolarityConfig(TIM3, TIM_OCPolarity_High);
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
		
		
	  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 200;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
			  TIM_OC2PolarityConfig(TIM3, TIM_OCPolarity_High);
		
		TIM_OC2Init(TIM3, &TIM_OCInitStructure);
		  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE)
	;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9 ; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);
	TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);

	 TIM_TimeBaseStructure.TIM_Period = 2000; 

    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

  //MoveFinger(100,120,150,200,100);
	MoveFinger(100,100,100,150,100);
	Delayus(100000);
	KEY_CONFIG ();
		 TIM_Cmd(TIM3, ENABLE); 
		 TIM_Cmd(TIM4, ENABLE);
		
}

void MoveFinger(int f1,int f2, int f3, int f4, int f5)
{

	
	TIM_OCInitStructure.TIM_Pulse = f1;   // finger 1 ring
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
		
			
	TIM_OCInitStructure.TIM_Pulse = f2;   // finger 2 little
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
		
					
	TIM_OCInitStructure.TIM_Pulse = f3;   // finger 3 thumb 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
		
							
	TIM_OCInitStructure.TIM_Pulse = f5;   // finger 4 middle
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
		
	TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Gated);
	TIM_SelectInputTrigger(TIM4, TIM_TS_ITR2);
}



void KEY_CONFIG (void)
{		
	/* Task 2: Configure K1 and K2 as input */
	//GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	 //row
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 |GPIO_Pin_7; // Pin_5 for R, Pin_0 for G, Pin_1 for B
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // column
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7; // Pin_5 for R, Pin_0 for G, Pin_1 for B
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
		
}




void keypad1(void)
{
	if (GPIOC->IDR & 0x0010)
	{
		Delayus(20000);
		if (GPIOC->IDR & 0x0010)
		{
			GPIOA->ODR = 0x0010;
			Delayus(100);
			if (GPIOC->IDR & 0x0010)
				{
					key_value = 1;
					LCD_Clear(0,0,180,220,RED);
						GPIOA->ODR = 0x00F0;
	          GPIOC->ODR = 0x0000;
				}
			else
				{
			    GPIOA->ODR = 0x0020;
			    Delayus(100);
					if (GPIOC->IDR & 0x0010)
					{
						key_value = 2;
						LCD_Clear(0,0,180,220,BLUE);
						GPIOA->ODR = 0x00F0;
	          GPIOC->ODR = 0x0000;
					}
					else
					{
						GPIOA->ODR = 0x0040;
						Delayus(100);
						if (GPIOC->IDR & 0x0010)
						{
							key_value = 3;
							LCD_Clear(0,0,180,220,GREEN);
							GPIOA->ODR = 0x00F0;
							GPIOC->ODR = 0x0000;
						}
						else
						{
							GPIOA->ODR = 0x0080;
							Delayus(100);
							if (GPIOC->IDR & 0x0010)
							{
								key_value = 4;
								LCD_Clear(0,0,180,220,YELLOW);
								GPIOA->ODR = 0x00F0;
								GPIOC->ODR = 0x0000;
							}
						}
					}
				}	
		}
	}

}


void keypad2(void)
{
	if (GPIOC->IDR & 0x0020)
	{
		Delayus(200000);
		if (GPIOC->IDR & 0x0020)
		{
			//GPIOA->ODR = 0x0010;
			GPIOA->BSRR = GPIO_Pin_4;
								GPIOA->BRR = GPIO_Pin_5;
								GPIOA->BRR = GPIO_Pin_8;
								GPIOA->BRR = GPIO_Pin_7;
			Delayus(100);
			if (GPIOC->IDR & 0x0020)
				{
					key_value = 1;
					LCD_Clear(0,0,180,220,RED);
						//GPIOA->ODR = 0x00F0;
	        			GPIOA->BSRR = GPIO_Pin_4;
								GPIOA->BSRR = GPIO_Pin_5;
								GPIOA->BSRR = GPIO_Pin_8;
								GPIOA->BSRR = GPIO_Pin_7;  
					GPIOC->ODR = 0x0000;
				}
			else
				{
			    //GPIOA->ODR = 0x0020;
			    GPIOA->BRR = GPIO_Pin_4;
								GPIOA->BSRR = GPIO_Pin_5;
								GPIOA->BRR = GPIO_Pin_8;
								GPIOA->BRR = GPIO_Pin_7;  
					Delayus(100);
					if (GPIOC->IDR & 0x0020)
					{
						key_value = 2;
					LCD_DrawSquare2(keycordx[x],keycordy[y],keycordx[x]+CHARWIDTH,keycordy[y]+CHARHEIGHT,WHITE);
					//LCD_DrawChar(20,20,k+'0');
					if(k>6 && k <= 25) 
					{
						k -= 7;
            x -= 7;
            y -= 7;						
					}				
       LCD_DrawSquare2(keycordx[x],keycordy[y],keycordx[x]+CHARWIDTH,keycordy[y]+CHARHEIGHT,BLUE);
						//GPIOA->ODR = 0x00F0;
	        GPIOA->BSRR = GPIO_Pin_4;
								GPIOA->BSRR = GPIO_Pin_5;
								GPIOA->BSRR = GPIO_Pin_8;
								GPIOA->BSRR = GPIO_Pin_7;    
					GPIOC->ODR = 0x0000;
					}
					else
					{
						//GPIOA->ODR = 0x0040;
						GPIOA->BRR = GPIO_Pin_4;
								GPIOA->BRR = GPIO_Pin_5;
								GPIOA->BSRR = GPIO_Pin_8;
								GPIOA->BRR = GPIO_Pin_7;  
						Delayus(100);
						if (GPIOC->IDR & 0x0020)
						{
							key_value = 3;
						//	LCD_Clear(0,0,180,220,GREEN);
							//GPIOA->ODR = 0x00F0;
							GPIOA->BSRR = GPIO_Pin_4;
								GPIOA->BSRR = GPIO_Pin_5;
								GPIOA->BSRR = GPIO_Pin_8;
								GPIOA->BSRR = GPIO_Pin_7;  
							GPIOC->ODR = 0x0000;
						}
						else
						{
							//GPIOA->ODR = 0x0080;
							GPIOA->BRR = GPIO_Pin_4;
								GPIOA->BRR = GPIO_Pin_5;
								GPIOA->BRR = GPIO_Pin_8;
								GPIOA->BSRR = GPIO_Pin_7;  
							Delayus(100);
							if (GPIOC->IDR & 0x0020)
							{
								key_value = 4;
						//		LCD_Clear(0,0,180,220,YELLOW);
								GPIOA->ODR = 0x00F0;
								GPIOC->ODR = 0x0000;
							}
						}
					}
				}	
		}
	}

}



void keypad3()
{
	if (GPIOC->IDR & 0x0040)
	{
		Delayus(200000);
		if (GPIOC->IDR & 0x0040)
		{
			//GPIOA->ODR = 0x0010;
			GPIOA->BSRR = GPIO_Pin_4;
								GPIOA->BRR = GPIO_Pin_5;
								GPIOA->BRR = GPIO_Pin_8;
								GPIOA->BRR = GPIO_Pin_7;  
			Delayus(100);
			if (GPIOC->IDR & 0x0040)
				{
					key_value = 1;
					LCD_DrawSquare2(keycordx[x],keycordy[y],keycordx[x]+CHARWIDTH,keycordy[y]+CHARHEIGHT,WHITE);
				//	LCD_DrawChar(20,20,k+'0');
					if(x != 0 && y != 0) 
					{
						k--;
						y--;
						x--;			
					}
					else
					{
					k=25;x=25;y=25;
					}	
					
    LCD_DrawSquare2(keycordx[x],keycordy[y],keycordx[x]+CHARWIDTH,keycordy[y]+CHARHEIGHT,BLUE);
						//GPIOA->ODR = 0x00F0;
					
	        GPIOA->BSRR = GPIO_Pin_4;
								GPIOA->BSRR = GPIO_Pin_5;
								GPIOA->BSRR = GPIO_Pin_8;
								GPIOA->BSRR = GPIO_Pin_7;    
					GPIOC->ODR = 0x0000;
				}
			else
				{
			    //GPIOA->ODR = 0x0020;
					GPIOA->BRR = GPIO_Pin_4;
								GPIOA->BSRR = GPIO_Pin_5;
								GPIOA->BRR = GPIO_Pin_8;
								GPIOA->BRR = GPIO_Pin_7;  
			    Delayus(100);
					if (GPIOC->IDR & 0x0040)
					{
						key_value = 2;
						strnum[strindex] = 66;
						  str1[strindex] = ' ';
						truestr[strindex] = ' ';
							strindex++;
						  LCD_DrawString(50,50,str1);
						
						
						//GPIOA->ODR = 0x00F0;
	          GPIOA->BSRR = GPIO_Pin_4;
								GPIOA->BSRR = GPIO_Pin_5;
								GPIOA->BSRR = GPIO_Pin_8;
								GPIOA->BSRR = GPIO_Pin_7;  
						GPIOC->ODR = 0x0000;
					}
					else
					{
						//GPIOA->ODR = 0x0040;
						GPIOA->BRR = GPIO_Pin_4;
								GPIOA->BRR = GPIO_Pin_5;
								GPIOA->BSRR = GPIO_Pin_8;
								GPIOA->BRR = GPIO_Pin_7;  
						Delayus(100);
						if (GPIOC->IDR & 0x0040)
						{
							key_value = 3;
							LCD_DrawSquare2(keycordx[x],keycordy[y],keycordx[x]+CHARWIDTH,keycordy[y]+CHARHEIGHT,WHITE);
					LCD_DrawChar(20,20,k+'0');
					if(x != 25 && y != 25) 
					{
						k++;
						y++;
						x++;	
					}
						else
					{
					k=0;x=0;y=0;
					}	
					LCD_DrawSquare2(keycordx[x],keycordy[y],keycordx[x]+CHARWIDTH,keycordy[y]+CHARHEIGHT,BLUE);
							//GPIOA->ODR = 0x00F0;
					GPIOA->BSRR = GPIO_Pin_4;
								GPIOA->BSRR = GPIO_Pin_5;
								GPIOA->BSRR = GPIO_Pin_8;
								GPIOA->BSRR = GPIO_Pin_7;  		
					GPIOC->ODR = 0x0000;
						}
						else
						{
							//GPIOA->ODR = 0x0080;
							GPIOA->BRR = GPIO_Pin_4;
								GPIOA->BRR = GPIO_Pin_5;
								GPIOA->BRR = GPIO_Pin_8;
								GPIOA->BSRR = GPIO_Pin_7;  
							Delayus(100);
							if (GPIOC->IDR & 0x0040)
							{
								key_value = 4;
						//		LCD_Clear(0,0,180,220,YELLOW);
								//GPIOA->ODR = 0x00F0;
								GPIOA->BSRR = GPIO_Pin_4;
								GPIOA->BSRR = GPIO_Pin_5;
								GPIOA->BSRR = GPIO_Pin_8;
								GPIOA->BSRR = GPIO_Pin_7;  
								GPIOC->ODR = 0x0000;
							}
						}
					}
				}	
		}
	}

}




void keypad4(void)
{
	if (GPIOC->IDR & 0x0080)
	{
		Delayus(200000);
		if (GPIOC->IDR & 0x0080)
		{
			//GPIOA->ODR = 0x0010;
			GPIOA->BSRR = GPIO_Pin_4;
								GPIOA->BRR = GPIO_Pin_5;
								GPIOA->BRR = GPIO_Pin_8;
								GPIOA->BRR = GPIO_Pin_7;  
			Delayus(100);
			if (GPIOC->IDR & 0x0080)
				{
					key_value = 1;
					strindex--;
					strnum[strindex] = 67;
					str1[strindex] = ' ';
					truestr[strindex] = 0;
					//strindex--;
					LCD_DrawString(50,50,str1);
					
					
					
						//GPIOA->ODR = 0x00F0;
	        GPIOA->BSRR = GPIO_Pin_4;
								GPIOA->BSRR = GPIO_Pin_5;
								GPIOA->BSRR = GPIO_Pin_8;
								GPIOA->BSRR = GPIO_Pin_7;    
					GPIOC->ODR = 0x0000;
				}
			else
				{
			    //GPIOA->ODR = 0x0020;
			    GPIOA->BRR = GPIO_Pin_4;
								GPIOA->BSRR = GPIO_Pin_5;
								GPIOA->BRR = GPIO_Pin_8;
								GPIOA->BRR = GPIO_Pin_7;  
					Delayus(100);
					if (GPIOC->IDR & 0x0080)
					{
						key_value = 2;
			LCD_DrawSquare2(keycordx[x],keycordy[y],keycordx[x]+CHARWIDTH,keycordy[y]+CHARHEIGHT,WHITE);
			//		LCD_DrawChar(20,20,k+'0');
					if(k>=0 && k <= 18) 
					{
						k += 7;
            x += 7;
            y += 7;						
					}				
       LCD_DrawSquare2(keycordx[x],keycordy[y],keycordx[x]+CHARWIDTH,keycordy[y]+CHARHEIGHT,BLUE);
						//GPIOA->ODR = 0x00F0;
	        GPIOA->BSRR = GPIO_Pin_4;
								GPIOA->BSRR = GPIO_Pin_5;
								GPIOA->BSRR = GPIO_Pin_8;
								GPIOA->BSRR = GPIO_Pin_7;    
					GPIOC->ODR = 0x0000;
					}
					else
					{
						//GPIOA->ODR = 0x0040;
						GPIOA->BRR = GPIO_Pin_4;
								GPIOA->BRR = GPIO_Pin_5;
								GPIOA->BSRR = GPIO_Pin_8;
								GPIOA->BRR = GPIO_Pin_7;  
						Delayus(100);
						if (GPIOC->IDR & 0x0080)
						{
							key_value = 3;
							strnum[strindex] = k;
						  str1[strindex] = k + 'a';
							truestr[strindex] = k + 'a';
							strindex++;
						  LCD_DrawString(50,50,str1);
							//GPIOA->ODR = 0x00F0;
							GPIOA->BSRR = GPIO_Pin_4;
								GPIOA->BSRR = GPIO_Pin_5;
								GPIOA->BSRR = GPIO_Pin_8;
								GPIOA->BSRR = GPIO_Pin_7;  
							GPIOC->ODR = 0x0000;
						}
						else
						{
							//GPIOA->ODR = 0x0080;
							GPIOA->BRR = GPIO_Pin_4;
								GPIOA->BRR = GPIO_Pin_5;
								GPIOA->BRR = GPIO_Pin_8;
								GPIOA->BSRR = GPIO_Pin_7;  
							Delayus(100);
							if (GPIOC->IDR & 0x0080)
							{
								key_value = 4;
								
								//strnum[strindex++] = k;
							//  str[strindex++] = k + 'a';
								//GPIOA->ODR = 0x00F0;
								GPIOA->BSRR = GPIO_Pin_4;
								GPIOA->BSRR = GPIO_Pin_5;
								GPIOA->BSRR = GPIO_Pin_8;
								GPIOA->BSRR = GPIO_Pin_7;  
								GPIOC->ODR = 0x0000;
							}
						}
					}
				}	
		}
	}

}


void Delayus (int duration)
{
		while(duration--) 
		{
			int i=0x02;				
			while(i--)
			__asm("nop");
		}
}

void convert(void){

   // LCD_DrawString(30,30,"strats");
    /* get the first token */
    token = strtok(truestr, s);
    
    /* walk through other tokens */
    while( token != NULL ) {
     //   printf( " %s\n", token );
        strcpy(words[p], token);
        token = strtok(NULL, s);
        p++;
    }
    //strcpy(temp,words[0]);
    //w = *temp;
    //printf(" %d\n",w);
    for(k1=0;k1<p;k1++)
        //printf(" %d\n",strlen(words[k1]));
    {
        ke = 0;temp = 0;
        while(temp<strlen(words[k1]))
        {
            if(ke > 4)
                ke = 0;
            act += (int)(words[k1][temp] - 'a' + 1) * kernel[ke];
            temp++;ke++;
            
        }
      //  printf("act is %d\n",act);
        for (w=0;w<wordamount;w++)
        {
            if (act == wordlist[w])
            {
                signs[sindex] = w + 26 + 10 + 1;
                flag = 1;
                sindex++;
            }
            
        }
        act = 0;ke = 0;
        if (!flag)
        {
            temp = 0;
            while(temp<strlen(words[k1]))
            {
                signs[sindex] =(int)words[k1][temp] - 'a'+10;
                temp++;
                sindex++;
            }
            
        }
        else
            flag = 0;
    }
		//  LCD_DrawString(30,30,"ends");

}
