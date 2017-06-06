// SE 185 Lab 8
#include <stdio.h>


#define MAXPOINTS 10000

// compute the average of the first num_items of buffer
double avg(double buffer[], int num_items);

//update the max and min of the first num_items of array
void maxmin(double array[], int num_items, double* max, double* min);

//shift length-1 elements of the buffer to the left and put the 
//new_item on the right.
void updatebuffer(double buffer[], int length, double new_item);



int main(int argc, char* argv[]) {
	
	/* DO NOT CHANGE THIS PART OF THE CODE */

	double x[MAXPOINTS], y[MAXPOINTS], z[MAXPOINTS];
	int lengthofavg = 0;
	if (argc>1) {
		sscanf(argv[1], "%d", &lengthofavg );
		printf("You entered a buffer length of %d\n", lengthofavg);
	}
	else {
		printf("Enter a length on the command line\n");
		return -1;
	}
	if (lengthofavg <1 || lengthofavg >MAXPOINTS) {
		printf("Invalid length\n");
		return -1;
	}
	
	/* PUT YOUR CODE HERE */
    int up, right, down, left, index;
    double max, min;
    
	while(left == 0){
        //Scans a line from controller
        scanf("%lf, %lf, %lf, %d, %d, %d, %d", &x[index], &y[index], &z[index], &up, &right, &down, &left);
        if(index > lengthofavg){
            printf("Avg X: %lf, Avg Y: %lf, Avg Z: %lf, ", avg(x, lengthofavg), avg(y, lengthofavg), avg(z, lengthofavg));
            printf("X: ");
            maxmin(x, index, &max, &min);
            printf(", Y: ");
            maxmin(y, index, &max, &min);
            printf(", Z: ");
            maxmin(z, index, &max, &min);
            printf("\n");
            updatebuffer(x, index + 1, x[index]);
            updatebuffer(y, index + 1, y[index]);
            updatebuffer(z, index + 1, z[index]);
        }else{
            index++;
        }
	}

}

double avg(double buffer[], int num_items){
	double sum;
	for(int i = 0; i < num_items; ++i){
		sum += buffer[i];
	}
	return sum / num_items;
}

void maxmin(double array[], int num_items, double* max, double* min){
	*min = array [0];
	*max = array[0];
	for(int i = 0; i < num_items; ++i){
		if(array[i] < *min){
			*min = array[i];
		}
		if(array[i] > *max){
			*max = array[i];
		}
	}
    printf("(Max: %lf, ", *max);
    printf("Min: %lf)", *min);
}

void updatebuffer(double buffer[], int length, double new_item){
	for(int i = 0; i < length; ++i){
		buffer[i] = buffer[i + 1];
	}
	buffer[length -1] = new_item;
}