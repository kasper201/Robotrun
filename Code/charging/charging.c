#include <pololu/3pi.h>
#include "Charging.h"
#include "MazeSolve.h"
#include "FindLine.h"

void chargeRoutine()
{
	delay_ms(100);
	solveMaze();
	delay_ms(100);
	passingToCharge();
	delay_ms(100);
	followCharge(0);
	timeToCharge();
	delay_ms(100);
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

void batteryRead( unsigned int *percentage)
{
	int average;
	
	for(int i = 0; i < 10; i++)
	{
		unsigned int voltage = read_battery_millivolts_3pi();
		average += voltage;
	}
	*percentage = (((*percentage-4500)/5));
}

void timeToCharge()
{
	clear();
	print("FLOEFS");
	lcd_goto_xy(0,1);
	print("SLEEPS");
	play("o5 c#" );
	delay_ms(10000);
}
