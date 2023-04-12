#include "FindLine.h"
#include "StockRoom.h"
#include "MazeSolve.h"
#include "Charging.h"
#include "ComRead.h"
#include "ManualDrive.h"
#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include <pololu/PololuQTRSensors.h>

char arrayToStockroom[128] = {0};


void toStockRoom()
{
	int i = 0;
	int check = 0;
	while(1)
	{
		followLine(&check,1);
		turn(arrayToStockroom[i]);
		if(check == 7)
		{
			break;
		}
		else if(check == 99)
		{
			break;
		}
		else if(check == 69)
		{
			set_motors(0,0);
			delay_ms(1000);
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
		if(check == 2)
		{
			turn(0);
		}
		else if(check == 7)
		{
			break;
		}
		else
		{
			turn(1);
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

void simplify(int crossing, int *pathLength)
{
	if(*pathLength < 3 || arrayToStockroom[(*pathLength-2)] != 2)
		return;
		
	int i;
	int totalTurn = 0;
	for(i = 1; i <= 3; i++)
	{
		totalTurn += arrayToStockroom[*pathLength-i];
	}
	totalTurn %= 4;
	
	arrayToStockroom[*pathLength-3] = totalTurn;
	
	*pathLength -= 2;
}

void solveMaze()
{
	static int stockroom = 0;
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
				set_motors(0,0);
				turn(1);
				arrayToStockroom[i] = 1;
			}
			i++;
			simplify(crossing, &i);		
		}
		irouteKnown = 1;
	}	
}
