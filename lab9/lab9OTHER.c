// WII-MAZE Skeleton code written by Jason Erbskorn 2007
// Edited for ncurses 2008 Tom Daniels
//Updated for Esplora 2013 TeamRursch185


// Headers
#include <stdio.h>
#include <math.h>
#include <ncurses/ncurses.h>
#include <unistd.h>

// Mathematical constants
#define PI 3.14159

// Screen geometry
// Use HEIGHT and WIDTH for the screen height and width (set by system)
// MAXIMUMS
#define WIDTH 100 //100
#define HEIGHT 80	//80

// Character definitions taken from the ASCII table
#define AVATAR 'A'
#define WALL '*'
#define EMPTY_SPACE ' '

// Number of samples taken to form an average for the accelerometer data
// Feel free to tweak this.  You may actually want to use the moving averages
// code you created last week 
#define NUM_SAMPLES 10  


// 2D character array which the maze is mapped into
char MAZE[WIDTH][HEIGHT];


// POST: Generates a random maze structure into MAZE[][]
//You will want to use the rand() function and maybe use the output %100.  
//You will have to use the argument to the command line to determine how 
//difficult the maze is (how many maze characters are on the screen).
void generate_maze(int difficulty);

// PRE: MAZE[][] has been initialized by generate_maze()
// POST: Draws the maze to the screen 
void draw_maze(void);

// PRE: 0 < x < WIDTH, 0 < y < HEIGHT, 0 < use < 255
// POST: Draws character use to the screen and position x,y
void draw_character(int x, int y, char use);

// PRE: -1.0 < y_mag < 1.0
// POST: Returns tilt magnitude scaled to -1.0 -> 1.0
// You may want to reuse the pitch function written in previous labs.  
double calc_pitch(double y_mag);

double calc_pitch(double y_mag)
{
	if(y_mag > 1) 
		y_mag = 1;
	
	if(y_mag < -1)
		y_mag = -1;
	
	if(y_mag < 0.1 && y_mag > -0.1) return 0;
	
	return (double) y_mag;	
}

int read_acc(double* a_x, double* a_y, double* a_z, int* time, int* Button_UP, int* Button_DOWN, int* Button_LEFT, int* Button_RIGHT);

int read_acc(double* a_x, double* a_y, double* a_z, int* time, int* Button_UP, int* Button_DOWN, int* Button_LEFT, int* Button_RIGHT)
{
	int Button_Joy;
	int s;
	scanf("%d, %lf, %lf, %lf, %d,  %d,  %d,  %d,  %d , %d",
			 time, a_x, a_y,a_z, Button_DOWN, Button_UP, Button_LEFT, Button_RIGHT, &Button_Joy, &s );
			   
	return *Button_UP;
			   
}

// Main - Run with './explore.exe -t -a -b' piped into STDIN
void main(int argc, char* argv[])
{
		int diff;
		sscanf(argv[1], "%d", &diff );
		printf("%d",diff);
		double x,y,z;
		int t,b_Up,b_Down,b_Left,b_Right, b_Joy, s, time;
		
		initscr();
        refresh();
		
		// Generate and draw the maze, with initial avatar
		generate_maze(diff);
		draw_maze();
		//put character to top middle
		int avX = WIDTH/2;
		int avY = 0;
		
		int delay = 100000000;
		int i = 0;
		MAZE[avX][avY] = AVATAR;
		draw_maze();
		//Avatar placed and waiting
		b_Up = 0;
		while(!b_Up)
		{
			//Begin move?
			read_acc(&x, &y, &z, &t, &b_Up, &b_Down, &b_Left, &b_Right);
		}

		// Event loop - Yes, Begin dropping
		// Read accelerometer data to get ready for using moving averages.
		double direction;
		direction = -10;
		int directionValue = 0;
		int waiting = 0;
		int movingSideways = 0;
		int prevX = 0, prevY = 0;
		do
        {

			read_acc(&x, &y, &z, &t, &b_Up, &b_Down, &b_Left, &b_Right);
			
			if(t%100 >=0 && t%100 < 4) {
				
				
				if(!waiting)
					draw_character(avX,avY, EMPTY_SPACE);
					
				if(movingSideways)
				{
					draw_character(avX,avY, EMPTY_SPACE);
				}
				
				//get direction				
				if(x > .1)
				{
					//move left
					if(avX >0)// keeps avatar in maze on left side
						directionValue = -1;
				}
				else if(x < -0.1)
				{
					//move right
					if(avX < WIDTH-1) // keeps avatar in maze on right side
						directionValue = 1;
				}
				else
					directionValue = 0;
					
				
				if(directionValue != 0)
				{
					//check in directionValue direction and below
					if(MAZE[avX+directionValue][avY] != EMPTY_SPACE && MAZE[avX][avY+1] != EMPTY_SPACE)
					{	
						//stuck in this directionValue
						waiting = 1;
						movingSideways = 1;
						draw_character(avX,avY, AVATAR);
						
						int countAway = 0;
						int i = avX;
						while(i>0 && i< WIDTH)
						{	
							i = i - directionValue;
							if(MAZE[i][avY] != EMPTY_SPACE)
							{
								i = -5;
								break;
							}
							if(MAZE[i][avY+1] == EMPTY_SPACE)
							{
								break;
							}
							countAway++;
						}
						
						if(i==-5)
						{
							endwin();
							printf("YOU LOSE!");
							if(countAway ==0)
								printf(" Completely Trapped!");
							else
								printf(" but can still move left and right!");
							
							break;
						}
						
						continue;
					}
				}
				
				if(MAZE[avX+directionValue][avY+1] == EMPTY_SPACE)
				{
					//make move
					avX = avX + directionValue;
					draw_character(avX,avY+1, AVATAR);
					waiting = 0;
					movingSideways = 0;
					avY++;
				}
				else
				{	//can't move down
					waiting = 1;
					if(waiting)
					{
						//moving left and right
						if(MAZE[avX+directionValue][avY] == EMPTY_SPACE)
						{
							//make move
							movingSideways = 1;
							avX = avX + directionValue;
							draw_character(avX,avY, AVATAR);
						}
					}
				}
				
				//move successful
				
				//check if won
				if(avY == HEIGHT)
				{
					endwin();
					printf("YOU WIN");
					break;
				}
			}
			
			refresh();
        } while(1); // Change this to end game at right time 

        // Print the win message
        endwin();
}

///////////// OUR FUNCTIONS

void generate_maze(int difficulty)
{
	//MAZE[WIDTH][HEIGHT];
	srand ( time(NULL) );
	int number = 0;
	
	int i =0, j=0;
	for(i=0;i<WIDTH;i++)
	{
		for(j=0;j<HEIGHT;j++)
		{	
			// maze[i][j] is not along border
			
			number = rand() % 100;
			
			if(number < difficulty)
				MAZE[i][j] = WALL;
			else
				MAZE[i][j] = EMPTY_SPACE;//temp
			
		}
	}
	
	
	
	return;
}

void draw_maze(void)
{
int i = 0, j = 0;
	for(i=0;i<WIDTH;i++)
	{
		for(j=0;j<HEIGHT;j++)
		{
			draw_character(i,j,MAZE[i][j]);
		}
	}
	return;
}


// PRE: 0 < x < WIDTH, 0 < y < HEIGHT, 0 < use < 255
// POST: Draws character use to the screen and position x,y
//THIS CODE FUNCTIONS FOR PLACING THE AVATAR AS PROVIDED.
//YOU DO NOT NEED TO CHANGE THIS FUNCTION.
void draw_character(int x, int y, char use)
{
        mvaddch(y,x,use);    
        refresh();
}
