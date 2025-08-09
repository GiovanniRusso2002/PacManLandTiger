/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "RIT.h"
#include <string.h>
#include "LPC17xx.h"
#include "../timer/timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "Game/game.h"
#include <stdio.h> /*for sprintf*/


/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
volatile int down_0 = 0;
volatile int down_1 = 0;
volatile int down_2 = 0;

extern int direzione;
extern position pacman;
extern int resume;
extern int last_direzione;
extern int isStopped;


void RIT_IRQHandler (void)
{
  static int js_up=0;
	static int js_down=0;
	static int js_right=0;
	static int js_left=0;
	static int js_select=0;

	if(down_0 !=0){
	down_0++;
	if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){
		switch(down_0){
			case 2:
				//code here: 
				if(resume){
					resume=0;
					GUI_Text(100,300, (uint8_t *)  "PAUSE", Yellow, Black);
					isStopped=0;
					disable_timer(0);
					last_direzione = direzione;
					direzione=0;
				}
				else{
					isStopped=1;
					resume=1;
					GUI_Text(100,300, (uint8_t *)  "     ", Black, Black);
					enable_timer(0);
					direzione=last_direzione;
			  }
				break;
			default:
				break;
		}
	}
	else {	/* button released */
		down_0=0;			
		NVIC_EnableIRQ(EINT0_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
	}
}
	
	
if(isStopped){
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
		/* Joytick UP pressed */
		js_up++;
		switch(js_up){
			case 1:
				if(setNewDirection(UP)) direzione=UP;
				break;
			default:
				break;
		}
		
	}
	else{
			js_up=0;
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	
		/* Joytick RIGHT pressed */
		js_right++;
		switch(js_right){
			case 1:
				//code here:
			if(setNewDirection(RIGHT)) direzione=RIGHT;
  			break;
			default:
				break;
		}
	}
	else{
			js_right=0;
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	
		/* Joytick LEFT pressed */
		js_left++;
		switch(js_left){
			case 1:
				//code here:
			if(setNewDirection(LEFT)) direzione=LEFT;	
				break;
			default:
				break;
		}
	}
	else{
			js_left=0;
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
		/* Joytick DOWN pressed */
		js_down++;
		switch(js_down){
			case 1:
				//code here:
			if(setNewDirection(DOWN)) direzione=DOWN;
				break;
			default:
				break;
		}
	}
	else{
			js_down=0;
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
		/* Joytick SELECT pressed */
		js_select++;
		switch(js_select){
			case 1:
				//code here:
				break;
			default:
				break;
		}
	}
	else{
			js_select=0;
	}
	


}

	reset_RIT();
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
