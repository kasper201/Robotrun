/* Robotrun - an application for the Pololu 3pi Robot
 *
 * This application uses the Pololu AVR C/C++ Library.  For help, see:
 * -User's guide: http://www.pololu.com/docs/0J20
 * -Command reference: http://www.pololu.com/docs/0J18
 *
 * Created: 3/18/2023 11:16:12 AM
 *  Author: Kaspe
 */

#include <pololu/3pi.h>
#include "FindLine.h"

void routeKnown(int stockStart, int sizeArray, int turnArray[])
{
	int inMaze = 1;
	int resetCrossing = 0;
	if(stockStart == 0)//if stockStart == 0 robot will go from start to stockroom otherwise if stockStart == 1 the robot will go from stockroom to start
	{
		for(int i = 0; i <= sizeArray; i++)
		{
			followLine(&resetCrossing, inMaze);
			turn(turnArray[i]);
			set_motors(50,50);
			delay_ms(50);
		}
	}
	
	else
	{
		for(int i = sizeArray; i >= 0; i--)
		{
			followLine(&resetCrossing, inMaze);
			turn(turnArray[i]);
			set_motors(50,50);
			delay_ms(50);
		}
	}
}

void solveMaze(int stockStart, int irouteKnown, int sizeArray, int (*turnArray)[sizeArray], int *state)
{
	if(irouteKnown == 1)//if route known just drive like the old array
	{
		routeKnown(stockStart, sizeArray, *turnArray);
	}
}

int main()
{ 
	int array[] = {1,3,1,2,2};//will become empty in actual code, this is just for testing purposes
	int sizeArray = sizeof(array)/sizeof(int);
	int state = 0;
	while(1)
	{
		solveMaze(0, 1, sizeArray, &array, &state);
	}
}
