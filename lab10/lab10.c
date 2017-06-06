// Lab 10 DS4Talker Skeleton Code

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ncurses.h>
#define MAXWORDS 100
#define WORDLEN 11
#define DEBUG 0   // set to 0 to disable debug output

#define ROWS 100
#define COL 5

// reads words from the file
// into wl and trims the whitespace off of the end
// DO NOT MODIFY THIS FUNCTION
int readWords(char* wl[MAXWORDS], char* filename); 

//modifies s to trim white space off the right side
// DO NOT MODIFY THIS FUNCTION
void trimws(char* s) ;

int main(int argc, char* argv[]) {
	char* wordlist[MAXWORDS];
	int wordCount;
	int i, xVal, yVal;
	wordCount = readWords(wordlist, argv[1]);
	
	char words[ROWS][COL];

	if (DEBUG) {
		printf("Read %d words from %s \n",wordCount, argv[1]);
		for (i = 0; i< wordCount; i++) {
			printf("%s,", wordlist[i]);

			}
		printf("\n");
		}

// most of your code goes here. Don't forget to include the ncurses library 
	initscr();
    refresh();
    
    for(i = 0; i < wordCount; i++){
        mvprintw(yVal, xVal, "%s", wordlist[i]);
        refresh();
        xVal += 15;
        if(xVal >= 75){
            yVal++;
            xVal = 0;
        }
    }
    
    int rowCount = wordCount / 5;
    if(wordCount % rowCount != 0){
        rowCount++;
    }
	
	int time, tri, O, X, square, leftJoyB, rightJoyB, idk, idk2, R2, L2, R1, L1, leftJoyX, leftJoyY, rightJoyX, rightJoyY;
    int curX = 12, curY, prevX, prevY;
	int directX, directY;
	int moveTime;
    int lengthOfLast, lengthOfSentance = 0;
	int lastCommand[MAXWORDS];
	int index = 0;
    
    while(1){
		scanf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", &time, &tri, &O, &X, &square, &leftJoyB, &rightJoyB, &idk, &idk2, &R2, &L2, &R1, &L1, &leftJoyX, &leftJoyY, &rightJoyX, &rightJoyY);
		
		if(time - moveTime < 125){
			continue;
		}
		
		if(leftJoyY > 100 ){
			directY = 1;
		}else if(leftJoyY < -100){
			directY = -1;
		}else if(leftJoyX > 100){
			directX = 15;
		}else if(leftJoyX < -100){
			directX = -15;
		}else{
			directX = 0;
			directY = 0;
		}
            
		if(curX + directX < 75){
			prevX = curX;
			curX += directX;			
		} 
		if(curY + directY < rowCount){
			prevY = curY;
	        curY += directY;		
		}
		
		moveTime = time;
        
		mvaddch(prevY, prevX, ' ');
        mvaddch(curY, curX, '<');
		refresh();
        
        if(tri){
            //adds word with space
			char toAdd[WORDLEN];
			//finds word based on column and row
            int indexToUse = (curY * 5) + (curX / 15);
            lengthOfLast = strlen(wordlist[indexToUse]) + 1;
			//adds the word to an array 
            strcpy(toAdd, wordlist[indexToUse]);
			//prints that word in the array
            mvprintw(rowCount + 2, lengthOfSentance," %s", toAdd);
			//adds this command to an array to keep track of it for deletion
			lastCommand[index] = strlen(wordlist[indexToUse]) + 1;
            lengthOfSentance += lengthOfLast;
			index++;
        }else if(square){
            //adds word without space
			char toAdd[WORDLEN];
			//finds word based on column and row
            int indexToUse = (curY * 5) + (curX / 15);
            lengthOfLast = strlen(wordlist[indexToUse]);
			//adds the word to an array 
            strcpy(toAdd, wordlist[indexToUse]);
			//prints that word in the array
            mvprintw(rowCount + 2, lengthOfSentance,"%s", toAdd);
			//adds this command to an array to keep track of it for deletion
			lastCommand[index] = strlen(wordlist[indexToUse]);
            lengthOfSentance += lengthOfLast;
			index++;
        }else if(X){
            //removes last item
				for(int i = 0; i < lastCommand[index]; i++){
					mvprintw(rowCount + 2, lengthOfSentance - lastCommand[index] + i, " ");
					refresh();
				}
				lengthOfSentance -= lastCommand[index];
				index--;
        }else if(rightJoyB){
			for(int i = 0; i < lengthOfSentance; i++){
				mvprintw(rowCount + 2, i, " ");
				refresh();
			}
			lengthOfSentance = 0;
		}    
    }
    return 0;
}

// DO NOT MODIFY THIS FUNCTION
void trimws(char* s) {
        int len = strlen(s) ;
        int x;
        if (len ==0) return;
        x = len-1;
        while (isspace(s[x]) && (x>=0)) {
                s[x] = '\0';
                x--;
                }
        }


// DO NOT MODIFY THIS FUNCTION
int readWords(char* wl[MAXWORDS], char* filename) {
	int numread =0;
	char line[WORDLEN];
	char *p;
	FILE* fp = fopen(filename,"r");
	while (!feof(fp)) {
		p  =fgets(line, WORDLEN, fp);
		if (!feof(fp) && p !=NULL) {
			trimws(line);
			wl[numread] = (char *)  malloc(strlen(line)+1);
			strcpy(wl[numread], line);
			numread++;
			}
		} 
	fclose(fp);
	return numread;	
	}