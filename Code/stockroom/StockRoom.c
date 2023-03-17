#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include "StockRoom.h"

int packageAmount;
int crossing;
enum direction{minX, plusX, minY, plusY};
enum direction facing;
struct coords{int Xcurrent, Ycurrent, Xpackage, Ypackage;};
struct coords p1;

void stockroomRoutine()
{
	if(packageAmount != 0)//there are still orders to be completed
	{
		switch(facing) //turn facing minus X
		{
			case minY:
			turn(1);
			facing = minX;
			break;
			case plusX:
			turn(2);
			facing = minX;
			break;
			case plusY:
			turn(3);
			facing = minX;
			break;
		}
		while(p1.Xcurrent<p1.Xpackage) //drive until the X coords is reached
		{
			followLine(&crossing, 0);
			if(crossing != 0)
			{
				turn(0);
			}
		}
		findPackageY();	//get all the packages on this X
	}
	else if(packageAmount <= 0) //there are no orders left
	{
		TurnBack();//drive back to the maze
	}
}

void findPackageY()
{
	
}

void passingToCharge()
{
	turn(1);
	while(crossing != 1)
	{
		followLine(&crossing, 0);
		if(crossing != 0)
		{
			turn(0);
		}
	}
	turn(1);
	followLine(&crossing, 0);
}

void TurnBack()
{
	switch(facing)
	{
		case plusX:
		turn(1);
		facing = minY;
		break;
		case plusY:
		turn(2);
		facing = minY;
		break;
		case minX:
		turn(3);
		facing = minY;
		break;
	}
	while(crossing != 1 && crossing != 5)
	{
		followLine(&crossing, 0);
		if(crossing != 0)
		{
			turn(0);
		}
	}
	turn(3);
	facing = plusX;
	while(*mazeBorder != true)
	{
		followLine(&crossing, 0);
		if(crossing != 0)
		{
			turn(0);
		}
	}
}
