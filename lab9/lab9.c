// WII-MAZE Skeleton code written by Jason Erbskorn 2007
// Edited for ncurses 2008 Tom Daniels
// Updated for Esplora 2013 TeamRursch185
// Updated for DualShock 4 2016 Rursch


// Headers
#include <stdio.h>
#include <math.h>
#include <ncurses/ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// Mathematical constants
#define PI 3.14159

// Screen geometry
// Use ROWS and COLS for the screen height and width (set by system)
// MAXIMUMS
#define NUMCOLS 100
#define NUMROWS 80

// Character definitions taken from the ASCII table
#define AVATAR 'A'
#define WALL '*'
#define EMPTY_SPACE ' '

// Number of samples taken to form an average for the gyroscope data
// Feel free to tweak this.  You may actually want to use the moving averages
// code you created last week 
#define NUM_SAMPLES 10  


// 2D character array which the maze is mapped into
char MAZE[NUMROWS][NUMCOLS];


// POST: Generates a random maze structure into MAZE[][]
//You will want to use the rand() function and maybe use the output %100.  
//You will have to use the argument to the command line to determine how 
//difficult the maze is (how many maze characters are on the screen).
void generate_maze(int difficulty);

// PRE: MAZE[][] has been initialized by generate_maze()
// POST: Draws the maze to the screen 
void draw_maze(void);

// PRE: 0 < x < COLS, 0 < y < ROWS, 0 < use < 255
// POST: Draws character use to the screen and position x,y
void draw_character(int x, int y, char use);

// PRE: -1.0 < x_mag < 1.0
// POST: Returns tilt magnitude scaled to -1.0 -> 1.0
// You may want to reuse the roll function written in previous labs.  
float calc_roll(float x_mag);

void delay(unsigned int ms);

// Main - Run with './ds4rd.exe -t -g -b' piped into STDIN
void main(int argc, char* argv[])
{
	int time, difficulty, avX, avY;
	double x, y, z;
	
	sscanf(argv[1], "%d", &difficulty);
	
	// setup screen    
	initscr();
	refresh();

	// Generate and draw the maze, with initial avatar
	generate_maze(difficulty);
	draw_maze();
	avX = NUMCOLS/2;
	avY = 0;
	draw_character(avX, avY, AVATAR);

	// Read gyroscope data to get ready for using moving averages.    
	scanf("%d, %lf, %lf, %lf", &time, &x, &y, &z);
	
	double direction = -10;
	int directVal = 0;
	int waiting = 0;
	int movingSideways = 0;
	int prevX = 0;
	int	prevY = 0;

	// Event loop
	do
	{
		// Read data, update average
        scanf("%d, %lf, %lf, %lf", &time, &x, &y, &z);
		
		//if(!waiting){
			//draw_character(avX,avY, EMPTY_SPACE);
		//}			
		//if(movingSideways){
			//draw_character(avX,avY, EMPTY_SPACE);
		//}
		
		//get direction				
		if(calc_roll(x) > .1){
			//move left
			if(avX > 0){ // keeps avatar in maze on left side
				directVal = -1;
			}else if(x < -0.1){
				//move right
				if(avX < NUMCOLS){ // keeps avatar in maze on right side
					directVal = 1;
				}else{
					directVal = 0;
				}
			}
		}
		
		if(directVal != 0){
			//check in directVal direction and below
			if(MAZE[avX + directVal][avY] != EMPTY_SPACE && MAZE[avX][avY + 1] != EMPTY_SPACE){	
				//stuck
				draw_character(avX, avY, AVATAR);
						
				int count = 0;
				int i = avX;
				while(i > 0 && i < NUMCOLS){	
					i = i - directVal;
					if(MAZE[i][avY] != EMPTY_SPACE){
						i = -5;
						break;
					}
					if(MAZE[i][avY+1] == EMPTY_SPACE){
						break;
					}
					count++;
				}
						
				if(i==-5){
					endwin();
					printf("YOU LOSE!");
					break;
				}		
				continue;
			}
		}else if(MAZE[avX][avY + 1] == EMPTY_SPACE){
			//moves avatar down
			avY++;
			draw_character(avX, avY - 1, EMPTY_SPACE);
			draw_character(avX, avY, AVATAR);
		}
		
		//checks if there's a star below character
		//if(MAZE[avX][avY + 1] == WALL){
			//while(MAZE[avX][avY + 1] == WALL){
				//scanf("%d, %lf, %lf, %lf", &time, &x, &y, &z);
				//else if(x < -.5){
					//move right
					//avX++;
					//draw_character(avX, avY, EMPTY_SPACE);
					//draw_character(avX, avY, AVATAR);
					//break;
				//}
			//}
		//}else{
			//moves avatar down
			//avY++;
			//delay(1000);
			//draw_character(avX, avY - 1, EMPTY_SPACE);
			//draw_character(avX, avY, AVATAR);
		//}
	} while(avY != NUMROWS);

	// Print the win message
	endwin();
	
	printf("YOU WIN!\n");
}

void generate_maze(int difficulty){
	srand(time(NULL));
	for(int i = 0; i < NUMROWS; ++i){
		for(int j = 0; j < NUMCOLS; ++j){
            rand() % 100;
            if(rand() % 100 < difficulty){
                MAZE[i][j] = WALL;
            }else{
                MAZE[i][j] = EMPTY_SPACE;
            }
		}
	}
}

void draw_maze(void){
	for(int i = 0; i < NUMROWS; ++i){
		for(int j = 0; j < NUMCOLS; ++j){
            draw_character(i,j,MAZE[i][j]);
		}
	}
	refresh();
}

float calc_roll(float x_mag){
	if(x_mag <= -1){
		x_mag = -1;
	}else if(x_mag >= 1){
		x_mag = 1;
	}
	return asin(x_mag);
}

void delay(unsigned int ms)
{
    clock_t sec = ms + clock();
    while (sec > clock());
}

// PRE: 0 < x < COLS, 0 < y < ROWS, 0 < use < 255
// POST: Draws character use to the screen and position x,y
//THIS CODE FUNCTIONS FOR PLACING THE AVATAR AS PROVIDED.
//
//    >>>>DO NOT CHANGE THIS FUNCTION.<<<<
void draw_character(int x, int y, char use)
{
	mvaddch(y,x,use);    
	refresh();
}