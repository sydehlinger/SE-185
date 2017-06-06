
// SE 185 lab7.c
//
// This is the outline for your program
// Please implement the functions given by the prototypes below and
// complete the main function to make the program complete.
// You must implement the functions which are prototyped below exactly
//  as they are requested.

#include <stdio.h>
#include <math.h>
#define PI 3.141592653589

//NO GLOBAL VARIABLES ALLOWED


//PRE: Arguments must point to double variables or int variables as appropriate
//This function scans a line of DS4 data, and returns
//  True when left button is pressed
//  False Otherwise
//POST: it modifies its arguments to return values read from the input line.
int read_line(double* g_x, double* g_y, double* g_z, int* time, int* Button_T, int* Button_X, int* Button_S, int* Button_C);

// PRE: -1.0 <= x_mag <= 1.0
// This function computes the roll of the DS4 in radians
// if x_mag outside of -1 to 1, treat it as if it were 1 or -1
// POST: -PI/2 <= return value <= PI/2
double roll(double x_mag);

// PRE: -1.0 <= y_mag <= 1.0
// This function computes the pitch of the DS4 in radians
// if y_mag outside of -1 to 1, treat it as if it were 1 or -1
// POST: -PI/2 <= return value <= PI/2
double pitch(double y_mag);


// PRE: -PI/2 <= rad <= PI/2
// This function scales the roll value to fit on the screen
// POST: -39 <= return value <= 39
int scaleRadsForScreen(double rad);

// PRE: num >= 0
// This function prints the character use to the screen num times 
// This function is the ONLY place printf is allowed to be used
// POST: nothing is returned, but use has been printed num times
void print_chars(int num, char use);

//PRE: -39 <= number <=39
// Uses print_chars to graph a number from -39 to 39 on the screen.
// You may assume that the screen is 80 characters wide.
void graph_line(int number);

int main()
{
	double x, y, z;			// magnitude values of x, y, and z
	int b_Up, b_Down, b_Left, b_Right;	// variables to hold the button statuses
	double roll_rad, pitch_rad;		// value of the roll measured in radians
	int scaled_value; 	// value of the roll adjusted to fit screen display
	int type;	// 0 if roll, 1 if pitch

	//insert any beginning needed code here
	
	do
	{
		// Get line of input (DONE)
		scanf("%lf, %lf, %lf, %d, %d, %d, %d", &x, &y, &z, &b_Up, &b_Right, &b_Down, &b_Left);
		
		// calculate roll and pitch.  Use the buttons to set the condition for roll and pitch (DONE)
		if(type == 0){
			roll_rad = roll(x);
		}else{
			pitch_rad = pitch(y);
		}

		// switch between roll and pitch(up vs. down button) (DONE)
		if(b_Up == 1){
			type = 0;
		}else if(b_Down == 1){
			type = 1;
		}
		
		// Scale your output value (DONE?)
		if(type == 0){
			scaled_value = scaleRadsForScreen(roll_rad);
		}else{
			scaled_value = scaleRadsForScreen(pitch_rad);
		}
		
		// Output your graph line
		graph_line(scaled_value);

		fflush(stdout);
	} while (b_Left == 0); // Modify to stop when left button is pressed
	return 0;
}

int read_line(double* g_x, double* g_y, double* g_z, int* time, int* Button_T, int* Button_X, int* Button_S, int* Button_C) {
	scanf("%lf %lf %lf %d %d %d %d %d", &g_x, &g_y, &g_z, &time, &Button_T, &Button_X, &Button_S, &Button_C);
	if(Button_C == 0){
		return 0;
	}else{
		return 1;
	}
}

double roll(double x_mag) {
	if(x_mag <= -1){
		x_mag = -1;
	}else if(x_mag >= 1){
		x_mag = 1;
	}
	return asin(x_mag);
}

double pitch(double y_mag) {
	if(y_mag <= -1){
		y_mag = -1;
	}else if(y_mag >= 1){
		y_mag = 1;
	}
	return asin(y_mag);
}

int scaleRadsForScreen(double rad) {
	return (rad * 39) / (PI / 2) ;
}

void print_chars(int num, char use) {
	if(num == 0){
		printf("%40c\n", use);
	}else if(num > 0){
		printf("%40c", use);
		for(int i = 0; i < num - 1; ++i){
			printf("%c", use);
		}
		printf("\n");
	}else{
        if(num == -1){
            printf("%40c", use);
        }else{
			int col = 41 + num;
			printf("%*c", col, use);
            for(int j = col; j < 40; ++j){
				printf("%c", use);
			}
		}
		printf("\n");
	}
}

void graph_line(int number) {
	if(number == 0){
		print_chars(number, '0');
	}else if(number > 0){
		print_chars(number, 'r');
	}else if(number < 0){
		print_chars(number, 'l');
	}
	
}