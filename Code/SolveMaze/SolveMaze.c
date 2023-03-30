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

int arrayToStockroom[64];
int arrayFromStockroom[64];

void routeKnown()
{

}

void simplify(int crossing, int *pathLength)
{
	int turnValue = 0;
	int i = 0;
	int totalTurn = 0;
	if(pathLength < 3 || arrayToStockroom[pathLength-2] != 2)
		return;
	
	for(i = 0; i <= 3; i++)
	{
		switch(arrayToStockroom[pathLength-i])
		{
			case 1:
			totalTurn += 1;
			break;
			
			case 2:
			totalTurn += 2;
			break;
			
			case 3:
			totalTurn += 3;
			break;
		}
	}
	totalTurn %= 4;
	
	switch(totalTurn)
	{
		case 0:
		arrayToStockroom[i-3] = 0;
		break;
		
		case 1:
		arrayToStockroom[i-3] = 1;
		break;
		
		case 2:
		arrayToStockroom[i-3] = 2;
		break;
		
		case 3;
		arrayToStockroom[i-3] = 4;
		break;
	}
	*pathLength -= 2;
}

void solveMaze() //set when implementing the code the state to Stockroom((5,0, facing -x) do this together with Mik
{
	static int irouteKnown = 0;
	
	if(irouteKnown = 0)
	{
		routeKnown();
	}
	else
	{
		int i = 0;
		while(1)
		{
			int crossing = 0;
			int inMaze = 1;
			followLine(&crossing, inMaze);
			if(crossing == 7)
			{
				set_motors(75,75);
				delay_ms(100);
				break;
			}
			else if(crossing == 2)
			{
				turn(0);
				arrayToStockroom[i] = 0;
			}
			else if(crossing == 99)
			{
				turn(2);
				arrayToStockroom[i] = 2;
			}
			else
			{
				turn(1);
				arrayToStockroom[i] = 1;
			}
			i++;
			simplify(crossing, &i);
		}
	}
}

int main()
{ 
	initRobot();
	
	while(1)
	{
		solveMaze();
	}
}
