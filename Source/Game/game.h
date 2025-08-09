#ifndef __GAME_H
#define __GAME_H
#include <stdint.h>
#define ROWS 32
#define COLS 28

#define STOP  0
#define RIGHT 1
#define UP    2
#define LEFT  3
#define DOWN  4

#define STANDARDPILL 10
#define POWERPILL 50

#define NUM_POWERPILL 6

typedef struct{
	int i,j, time;
} powerPill;

typedef struct{
	int i,j;
} position;

int setNewDirection(int newDirection);

void LCD_DrawPacman( uint16_t x0, uint16_t y0, uint16_t color );
void LCD_DeleteStaff( uint16_t x0, uint16_t y0, uint16_t color );
void LCD_DrawSquare( uint16_t x0, uint16_t y0, uint16_t color );
void LCD_StandardPill( uint16_t x0, uint16_t y0, uint16_t color );
void LCD_PowerPill(uint16_t x0, uint16_t y0, uint16_t color );

void gameInit();
void draw_grid();
void writeVite();

void movePacman();
void assignPowerPill();
#endif 
