#include "FindLine.h"
#include "StockRoom.h"
#include "MazeSolve.h"
#include "Charging.h"
#include "ComRead.h"
#include "ManualDrive.h"
#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include <pololu/PololuQTRSensors.h>

void chargeRoutine()
{
	delay_ms(100);
	solveMaze();
	
	delay_ms(100);
	passingToCharge();
	
	delay_ms(100);
	followCharge();
	
	clear();
	print("FLOEFS");
	lcd_goto_xy(0,1);
	print("SLEEPS");
	play("o5 c#" );
	
	delay_ms(10000);
	passingToCharge2();
	
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

void passingToCharge()
{
	int crossing=0;
	followLine(&crossing, 0);
	turn(1);
	while(crossing!=1)
	{
		crossing=0;
		followLine(&crossing, 0);
		if(crossing!=0)
		{
			turn(0);
		}
	}
	turn(1);
	set_motors(50, 50);
	delay_ms(200);
}

void passingToCharge2()
{
	int crossing=0;
	followLine(&crossing, 0);
	while(crossing == 69)
	{
		set_motors(0,0);
		delay_ms(2500);
		followLine(&crossing,0);
	}
	turn(3);
	while(crossing!=1)
	{
		crossing=0;
		followLine(&crossing, 0);
		if(crossing!=0)
		{
			turn(0);
		}
	}
	turn(3);
	while(crossing!=7)
	{
		crossing=0;
		followLine(&crossing, 0);
	}
}
