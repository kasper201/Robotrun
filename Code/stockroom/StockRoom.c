#include "FindLine.h"
#include "StockRoom.h"
#include "MazeSolve.h"
#include "Charging.h"
#include "ComRead.h"
#include "ManualDrive.h"
#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include <pololu/PololuQTRSensors.h>

void stockroomRoutine()
{
	solveMaze();
	delay_ms(100);
	int *bcrossing = 0;
	delay_ms(100);
	followLine(&bcrossing, 0);
	bcrossing = 0;

	int package = 0;

	facing = plusX;
	p1.Xcurrent = 0;
	p1.Ycurrent = 0;
	p1.Xpackage = 0;
	p1.Ypackage = 0;
	
	clear();
	print("calcul");
	lcd_goto_xy(0,1);
	print("ating");
	play("o5 c#" );
	delay_ms(1000);
	
	while(o1.packageAmount!=0)//there are still orders to be completed
	{
		clear();
		print("start.");
		lcd_goto_xy(0,1);
		print(";)");
		play("o5 c#" );
		delay_ms(200);
		clear();

		p1.Xpackage = o1.Xorders[package];
		p1.Ypackage = o1.Yorders[package];

		findPackage(&bcrossing); //go to the package
		
		package++;
	}
	TurnBack();//drive back to the maze
	
	delay_ms(100);
	solveMaze();
	delay_ms(100);
	
	followLine(0,0);
	set_motors(0,0);
	turn(1);
	followLine(0,0);
	set_motors(0,0);
	delay_ms(100);
}

void findPackage(int *crossing)
{
	turnToX(p1.Xpackage,crossing);
	
	while(p1.Xcurrent!=p1.Xpackage) //drive until the y coords is reached
	{
		crossing = 0;
		followLine(&crossing, 0);
		if(crossing != 0)
		{
			turn(0);
		}
		if(facing == plusX)
		{
			p1.Xcurrent++;
		}
		if(facing == minX)
		{
			p1.Xcurrent--;
		}
	}
	
	clear();
	print("X");
	lcd_goto_xy(0,1);
	print("reached");
	play("o5 c#" );
	delay_ms(100);

	turnToY(p1.Ypackage,crossing);
	
	while(p1.Ycurrent!=p1.Ypackage) //drive until the y coords is reached
	{
		crossing = 0;
		followLine(&crossing, 0);
		if(crossing != 0)
		{
			turn(0);
		}
		if(facing == plusY)
		{
			p1.Ycurrent++;
		}
		if(facing == minY)
		{
			p1.Ycurrent--;
		}
	}
	
	clear();
	print("order");
	lcd_goto_xy(0,1);
	print("reached");
	play("o5 c#" );
	delay_ms(1000);
	o1.packageAmount--;
}

void turnToX(int x,int ccrossing)
{
	switch(facing)
	{
		case plusX:
		if(p1.Xcurrent<x)
		{
			turn(0);
			facing = plusX;
		}
		else
		{
			turn(2);
			facing = minX;
		}
		break;
		
		
		case minY:
		if(p1.Xcurrent<x)
		{
			turn(1);
			facing = plusX;
		}
		else
		{
			turn(3);
			facing = minX;
		}
		break;
		
		
		case minX:
		if(p1.Xcurrent<x)
		{
			turn(2);
			facing = plusX;
		}
		else
		{
			turn(0);
			facing = minX;
		}
		break;
		
		
		case plusY:
		if(p1.Xcurrent<x)
		{
			turn(3);
			facing = plusX;
		}
		else
		{
			turn(1);
			facing = minX;
		}
		break;
	}
}

void turnToY(int y,int ccrossing)
{
	switch(facing) //turn facing the wanted y
	{
		case plusX:
		if(p1.Ycurrent<y)
		{
			turn(1);
			facing = plusY;
		}
		else
		{
			turn(3);
			facing = minY;
		}
		break;
		
		case minY:
		if(p1.Ycurrent<y)
		{
			turn(2);
			facing = plusY;
		}
		else
		{
			turn(0);
			facing = minY;
		}
		break;
		
		case minX:
		if(p1.Ycurrent<y)
		{
			turn(3);
			facing = plusY;
		}
		else
		{
			turn(1);
			facing = minY;
		}
		break;
		
		case plusY:
		if(p1.Ycurrent<y)
		{
			turn(0);
			facing = plusY;
		}
		else
		{
			if(ccrossing = 2)
			{
				turn(1);
				facing = plusY;
			}
			else if(ccrossing = 3)
			{
				turn(3);
				facing = minY;
			}
			else
			{
				turn(2);
				facing = minY;
			}
		}
		break;
	}
}

void TurnBack()
{
	int crossing = 0;
	switch(facing)
	{
		case minX:
		turn(1);
		facing=minY;
		break;
		
		case plusY:
		turn(2);
		facing=minY;
		break;
		
		case plusX:
		turn(3);
		facing=minY;
		break;
		
		case minY:
		break;
	}
	if(p1.Ycurrent != 0)
	{
		while(crossing!=1 && crossing!=5 && crossing!=7)
		{
			crossing = 0;
			followLine(&crossing, 0);
			if(crossing != 0)
			{
				turn(0);
			}
		}
	}
	turn(3);
	while(crossing!=7)
	{
		crossing = 0;
		followLine(&crossing, 0);
		if(crossing!=0)
		{
			turn(0);
		}
	}
}
