/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "LPC17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h"
#include "Game/game.h"

#include "../TouchPanel/TouchPanel.h"
#include <stdio.h> /*for sprintf*/

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


extern volatile int seconds;
extern int isStopped;
extern int direzione;

void TIMER0_IRQHandler (void)
{ 
	assignPowerPill();
  seconds--;
	writeCounter();
	if(seconds==0){
		direzione=0;
		disable_RIT();
		disable_timer(0);
		isStopped=0;
		GUI_Text(100,300, (uint8_t *)  "GAME OVER", Red, Black);
		
	}
		
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER2_IRQHandler (void)
{
	movePacman();
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
