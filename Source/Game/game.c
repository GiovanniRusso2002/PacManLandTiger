#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "game.h"
#include "stdio.h"
#include "string.h"
#include <stdlib.h>
#include "../RIT/RIT.h"
#include "../GLCD/GLCD.h" 
#include "../timer/timer.h"



int lives=1;
int total_score=0;
int direzione=STOP;
volatile int seconds=60;
powerPill vettPowerPill[6];
position pacman;
int prima_mossa=1;
int score_life=0;
int pills_eaten=0;

int resume=0;
int last_direzione;

int isStopped=0;


int game_field_input[ROWS][COLS] = {
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1},
    {-1, 1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1, 1,-1},
    {-1, 1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1, 1,-1},
    {-1, 1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1, 1,-1},
    {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1},
    {-1, 1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1, 1,-1},
    {-1, 1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1, 1,-1},
    {-1, 1, 1, 1, 1, 1, 1,-1,-1, 1, 0, 0, 0,-1,-1, 0, 0, 0, 1,-1,-1, 1, 1, 1, 1, 1, 1,-1},
    {-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1, 0,-1,-1, 0,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1},
    { 0, 0, 0, 0, 0,-1, 1,-1,-1,-1,-1,-1, 0,-1,-1, 0,-1,-1,-1,-1,-1, 1,-1, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0,-1, 1,-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1, 1,-1, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0,-1, 1,-1,-1, 0,-1,-1, 0, 0, 0, 0,-1,-1, 0,-1,-1, 1,-1, 0, 0, 0, 0, 0},
    {-1,-1,-1,-1,-1,-1, 1,-1,-1, 0,-1, 0, 0, 0, 0, 0, 0,-1, 0,-1,-1, 1,-1,-1,-1,-1,-1,-1},
    {-2, 0, 0, 0, 0, 0, 1, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 1, 0, 0, 0, 0, 0,-2},
    {-1,-1,-1,-1,-1,-1, 1,-1,-1, 0,-1, 0, 0, 0, 0, 0, 0,-1, 0,-1,-1, 1,-1,-1,-1,-1,-1,-1},
    { 0, 0, 0, 0, 0,-1, 1,-1,-1, 0,-1,-1,-1,-1,-1,-1,-1,-1, 0,-1,-1, 1,-1, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0,-1, 1,-1,-1, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,-1,-1, 1,-1, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0,-1, 1,-1,-1, 0,-1,-1,-1,-1,-1,-1,-1,-1, 0,-1,-1, 1,-1, 0, 0, 0, 0, 0},
    {-1,-1,-1,-1,-1,-1, 1,-1,-1, 0,-1,-1,-1,-1,-1,-1,-1,-1, 0,-1,-1, 1,-1,-1,-1,-1,-1,-1},
    {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1},
    {-1, 1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1, 1,-1},
    {-1, 1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1, 1,-1},
    {-1, 1, 1, 1,-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1,-1, 1, 1, 1,-1},
    {-1,-1,-1, 1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1, 1,-1,-1,-1},
    {-1,-1,-1, 1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1, 1,-1,-1,-1},
    {-1, 1, 1, 1, 1, 1, 1,-1,-1, 1, 1, 1, 1,-1,-1, 1, 1, 1, 1,-1,-1, 1, 1, 1, 1, 1, 1,-1},
    {-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1},
    {-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1},
    {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
};


//-2=portale, -1=wall, 0=empty, 1=standard pill, 3=pacman, 4=power pill

void draw_grid(void)
{
	unsigned int i,j;

	for(i=0;i<ROWS;i++){
		for(j=0;j<COLS;j++){
			if(game_field_input[i][j]==-1) LCD_DrawSquare(j, i, Blue);
			if(game_field_input[i][j]==1) LCD_StandardPill(j, i, White);
			if(game_field_input[i][j]==3){
				LCD_DrawPacman(j, i, Yellow);
				pacman.i=i;
				pacman.j=j;
			}
		}
	}
		
	return;
}

void writeScore(int score_counter){
	char score[20];
	sprintf(score, "%d", total_score);
	GUI_Text(150,5, (uint8_t *)  "Score:", White, Black);
	GUI_Text(200,5, (uint8_t *)  score, White, Black);
}

void writeCounter(){
	char sec[3];
	sprintf(sec, "%d", seconds);
	GUI_Text(25,5, (uint8_t *)  "Game Over:", White, Black);
	if(seconds==9) 	GUI_Text(110,5, (uint8_t *)  "  ", Black, Black);
	GUI_Text(105,5, (uint8_t *)  sec, White, Black);
	
}

void writeVite(){
	char vite[20];
	sprintf(vite, "%d", lives);
	GUI_Text(25,300, (uint8_t *)  "Vite:", White, Black);
	GUI_Text(70,300, (uint8_t *)  vite, White, Black);
}


void gameInit(){
	
	LCD_Clear(Black);	
	draw_grid();
	init_timer(0,0x10B0760); //0.5 sec
	init_timer(2,0xF4240*1.5);
	enable_timer(2);
	
  GUI_Text(100,300, (uint8_t *)  "PAUSE", Yellow, Black);
	
	NVIC_SetPriority(TIMER0_IRQn, 3);

	NVIC_SetPriority(RIT_IRQn, 0);
	
	writeCounter();
	writeVite();
	writeScore(total_score);
	
	return;
}

int setNewDirection(int newDirection){
	switch(newDirection){
		case RIGHT:
			if(game_field_input[pacman.i][pacman.j+1]==-1) return 0; 
		return 1;
			
		case UP:
			if(game_field_input[pacman.i-1][pacman.j]==-1) return 0;
		return 1;
		
		case LEFT:
			if(game_field_input[pacman.i][pacman.j-1]==-1) return 0;
		return 1;
			
		case DOWN:
			if(game_field_input[pacman.i+1][pacman.j]==-1) return 0;
		return 1;
		
				
		
		}
	return 1;
}


void assignPowerPill(){
	int k;
	for(k=0; k<NUM_POWERPILL;k++){
		if(vettPowerPill[k].time==seconds && game_field_input[vettPowerPill[k].i][vettPowerPill[k].j] == 1){
			game_field_input[vettPowerPill[k].i][vettPowerPill[k].j] = 4;
			LCD_PowerPill(vettPowerPill[k].j, vettPowerPill[k].i, White);
		}
	}
}

void movePacman(){
	if(prima_mossa && direzione!=0){
		int save_seconds;
		int k,i,j,t;
		
		save_seconds=seconds;
		srand(LPC_TIM1->TC);
		disable_timer(1);
		
		for(k=0;k<NUM_POWERPILL;k++){
			
			while(1){
			i = rand() % 32;
			j = rand() % 28;
			t = (rand() % save_seconds) + 1;
			if(game_field_input[i][j]==1){
				powerPill p;
				p.i=i;
				p.j=j;
				p.time=t;
				vettPowerPill[k] = p;
				break;
				}
			}
			
		}
	prima_mossa=0;
	
	}
	
	int new_score=0;
 	switch(direzione){
			case RIGHT:
				
			if(game_field_input[pacman.i][pacman.j+1]==-2){
				game_field_input[pacman.i][pacman.j] = 0;
				LCD_DeleteStaff(pacman.j, pacman.i, Black);
				pacman.j = pacman.j-23;
				LCD_DrawPacman(pacman.j, pacman.i, Yellow);
				game_field_input[pacman.i][pacman.j] = 3;
				break;
			}
			if(game_field_input[pacman.i][pacman.j+1]!=-1){
				if(game_field_input[pacman.i][pacman.j+1]==1) new_score = STANDARDPILL;
				if(game_field_input[pacman.i][pacman.j+1]==4) new_score = POWERPILL;
				game_field_input[pacman.i][pacman.j] = 0;
				LCD_DeleteStaff(pacman.j, pacman.i, Black);
				pacman.j = pacman.j+1;
				LCD_DrawPacman(pacman.j, pacman.i, Yellow);
				game_field_input[pacman.i][pacman.j] = 3;
			}
			break;
		case UP:
			
			if(game_field_input[pacman.i-1][pacman.j]!=-1){
				if(game_field_input[pacman.i-1][pacman.j]==1) new_score = STANDARDPILL;
				if(game_field_input[pacman.i-1][pacman.j]==4) new_score = POWERPILL;
				game_field_input[pacman.i][pacman.j] = 0;
				LCD_DeleteStaff(pacman.j, pacman.i, Black);
				pacman.i=pacman.i-1;
				game_field_input[pacman.i][pacman.j] = 3;
				LCD_DrawPacman(pacman.j, pacman.i, Yellow);
			}
			break;
		case LEFT:
			
		  if(game_field_input[pacman.i][pacman.j-1]==-2){
				game_field_input[pacman.i][pacman.j] = 0;
				LCD_DeleteStaff(pacman.j, pacman.i, Black);
				pacman.j = pacman.j+23;
				LCD_DrawPacman(pacman.j, pacman.i, Yellow);
				game_field_input[pacman.i][pacman.j] = 3;
				break;
			}
			
			if(game_field_input[pacman.i][pacman.j-1]!=-1){
				if(game_field_input[pacman.i][pacman.j-1]==1) new_score = STANDARDPILL;
				if(game_field_input[pacman.i][pacman.j-1]==4) new_score = POWERPILL;
				game_field_input[pacman.i][pacman.j] = 0;
				LCD_DeleteStaff(pacman.j, pacman.i, Black);
				pacman.j=pacman.j-1;
				game_field_input[pacman.i][pacman.j] = 3;
				LCD_DrawPacman(pacman.j, pacman.i, Yellow);
			}
			break;
		case DOWN:
			
			if(game_field_input[pacman.i+1][pacman.j]!=-1){
				if(game_field_input[pacman.i+1][pacman.j]==1) new_score = STANDARDPILL;
				if(game_field_input[pacman.i+1][pacman.j]==4) new_score = POWERPILL;
				game_field_input[pacman.i][pacman.j] = 0;
				LCD_DeleteStaff(pacman.j, pacman.i, Black);
				pacman.i=pacman.i+1;
				game_field_input[pacman.i][pacman.j] = 3;
				LCD_DrawPacman(pacman.j, pacman.i, Yellow);
			}
			break;
		default:
			break;
		}
		
		if(new_score!=0){
			pills_eaten++;
			score_life+=new_score;
			total_score+=new_score;
			if(score_life>=1000){
				score_life-=1000;
				lives++;
				writeVite();
			}
			writeScore(total_score);
			if(pills_eaten==240){
				direzione=STOP;
				disable_RIT();
				disable_timer(0);
				isStopped=0;
				GUI_Text(100,300, (uint8_t *)  "VICTORY!!!", Blue, Black);
			}
		}
	
}



