/* Robotrun - an application for the Pololu 3pi Robot
 *
 * This application uses the Pololu AVR C/C++ Library.  For help, see:
 * -User's guide: http://www.pololu.com/docs/0J20
 * -Command reference: http://www.pololu.com/docs/0J18
 *
 * Created: 3/18/2023 11:16:12 AM
 *  Author: Kaspe
 */

/*
 * Part of this code was derived but not copied from Pololu at https://www.pololu.com/docs/0J21/8.e
 * Though this isn't a copy or just plain rewritten in different variable names large parts do look alike
 */

#include <pololu/3pi.h>
#include "FindLine.h"
#include "MazeSolve.h"

char arrayToStockroom[128] = {3,3,1,3};
char arrayFromStockroom[128] = {0};

void toStockRoom()
{
	int i = 0;
	int check = 0;
	while(1)
	{
		followLine(0,1);
		turn(arrayToStockroom[i]);
		if(check == 7)
		{
			break;
		}
		i++;
	}
}

void fromStockRoom()
{
	int i = 0;
	int check = 0;
	while(1)
	{
		followLine(&check,1);
		turn(arrayFromStockroom[i]);
		if(check == 7)
		{
			break;
		}
		i++;
	}
}

void routeKnown(int *ToStockRoom)
{	
	if(*ToStockRoom)
	{
		toStockRoom();
		*ToStockRoom = 0;
	}
	else
	{
		fromStockRoom();
		*ToStockRoom = 1;
	}
}

void convertArray(int arrayLength)
{
	for(int i = arrayLength; i >= 0; i--)
	{
		if(arrayToStockroom[i] == 3)
		{
			arrayFromStockroom[arrayLength-i] = 1;
		}
		else if(arrayToStockroom[i] == 1)
		{
			arrayFromStockroom[arrayLength - i] = 3;
		}
		else
		{
			arrayFromStockroom[arrayLength - i] = 0;
		}
	}
}

void simplify(int crossing, int *pathLength)
{
	if(*pathLength < 3 || arrayToStockroom[(*pathLength-2)] != 2)
		return;
		
	int i;
	int totalTurn = 0;
	for(i = 1; i <= 3; i++)
	{
		switch(arrayToStockroom[*pathLength-i])
		{			
			case 1:
			totalTurn += 90;
			break;
			
			case 3:
			totalTurn += 270;
			break;
			
			case 2:
			totalTurn += 180;
			break;
		}
	}
	totalTurn %= 360;
	
	switch(totalTurn)
	{
		case 0:
		arrayToStockroom[*pathLength-3] = 0;
		break;
		
		case 90:
		arrayToStockroom[*pathLength-3] = 1;
		break;
		
		case 180:
		arrayToStockroom[*pathLength-3] = 2;
		break;
		
		case 270:
		arrayToStockroom[*pathLength-3] = 3;
		break;
	}
	*pathLength -= 2;
}

void solveMaze()
{
	static int stockroom = 1;
	int inMaze = 1;
	static int irouteKnown = 0;
	static int i = 0;
	
	if(irouteKnown == 1)
	{
		routeKnown(&stockroom);
	}
	else
	{
		while(1)
		{
			int crossing = 0;
			followLine(&crossing, inMaze);
			if(crossing == 7)
			{
				break;
			}
			else if(crossing == 2)
			{
				set_motors(0,0);
				turn(0);
				arrayToStockroom[i] = 0;
			}
			else if(crossing == 99)
			{
				set_motors(0,0);
				turn(1);
				delay_ms(20);
				arrayToStockroom[i] = 2;
			}
			else
			{
				turn(1);
				arrayToStockroom[i] = 1;
			}
			i++;
			simplify(crossing, &i);
			
			if(i == 11)
			{
				irouteKnown = 1;
				break;
			}			
		}
		convertArray(i);
	}	
	irouteKnown = 1;
}

/*
int main()
{ 
	char test;
	initRobot();
	clear();
	solveMaze();
	clear();
	wait_for_button_press(BUTTON_B);
	wait_for_button_release(BUTTON_B);
	solveMaze();
}*/
