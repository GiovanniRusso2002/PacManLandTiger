/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "Game/game.h"
#include "button_EXINT/button.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"




#ifdef SIMULATOR
extern uint8_t ScaleFlag; 
#endif


int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	BUTTON_init();
	init_RIT(0x004C4B40);
	joystick_init();
  LCD_Initialization();
	enable_RIT();
	
	init_timer(1, 0);
	enable_timer(1);
	
  //	TP_Init();
	//TouchPanel_Calibrate();
	
	gameInit();

	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
