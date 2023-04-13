#include "FindLine.h"
#include "StockRoom.h"
#include "MazeSolve.h"
#include "Charging.h"
#include "ComRead.h"
#include "ManualDrive.h"
#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include <pololu/PololuQTRSensors.h>

struct am{int amountOfZero, amountOfOne, amountOfTwo, amountOfThree, amountOfFour;};
struct am amount;

void stockroomRoutine()
{
	solveMaze();
	delay_ms(100);
	int crossing = 0;
	delay_ms(100);
	followLine(&crossing, 0);
	crossing = 0;

	int package = 0;

	facing = minX;
	p1.Xcurrent = 0;
	p1.Ycurrent = 0;
	p1.Xpackage = 0;
	amount.amountOfZero = 0;
	amount.amountOfOne = 0;
	amount.amountOfTwo = 0;
	amount.amountOfThree = 0;
	amount.amountOfFour = 0;
	p1.amountOfX = 0;
	
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
		
		switch(facing) //turn facing minus X if not
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
			
			case minX:
			break;
		}
		package++;
		//nextRound(); //decides witch packages are next
		
		clear();
		//print_long(p1.Xpackage);
		
		findPackageX(); //go to the X
		
		delay_ms(500);
		
		findPackageY();	//get all the packages on this X
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
/*
void nextRound()
{
	p1.Xpackage = 0;
	p1.amountOfX = 0;
	amount.amountOfZero = 0;
	amount.amountOfOne = 0;
	amount.amountOfTwo = 0;
	amount.amountOfThree = 0;
	amount.amountOfFour = 0;
	
	while(p1.amountOfX==0)
	{
		
		for(int teller=0; teller<o1.packageAmount; teller++)
		{
			if(o1.Xorders[teller]==p1.Xpackage)
			{
				switch(o1.Yorders[teller])
				{
					case 0:
					amount.amountOfZero++;
					p1.amountOfX++;
					break;
					case 1:
					amount.amountOfOne++;
					p1.amountOfX++;
					break;
					case 2:
					amount.amountOfTwo++;
					p1.amountOfX++;
					break;
					case 3:
					amount.amountOfThree++;
					p1.amountOfX++;
					break;
					case 4:
					amount.amountOfFour++;
					p1.amountOfX++;
					break;
				}
				o1.Xorders[teller] = 5;
				o1.Yorders[teller] = 5;
			}
		}
		
		if(p1.amountOfX==0)
		{
			p1.Xpackage++;
		}
		if(p1.Xpackage==5)
		{
			o1.packageAmount = 0;
			break;
		}
	}
}*/

void findPackageX()
{
	int crossing = 0;
	while(p1.Xcurrent!=p1.Xpackage) //drive until the X coords is reached
	{
		crossing = 0;
		followLine(&crossing, 0);
		if(crossing!=0)
		{
			turn(0);
			p1.Xcurrent++;
		}
	}
}

void findPackageY()
{
	int crossing = 0;
	while(p1.amountOfX != 0)
	{
		delay_ms(500);
		
		if(amount.amountOfFour>0)
		{
			turnToY(4,crossing);
			
			while(p1.Ycurrent<=4) //drive until the y coords is reached
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
			amount.amountOfFour--;
			clear();
			print("order");
			lcd_goto_xy(0,1);
			print("reached");
			play("o5 c#" );
			delay_ms(1000);
			p1.Ycurrent = 4;
			o1.packageAmount--;
			p1.amountOfX--;
		}
		
		if(amount.amountOfThree>0)
		{
			turnToY(3,crossing);
			
			while(p1.Ycurrent!=3) //drive until the y coords is reached
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
			
			amount.amountOfThree--;
			clear();
			print("order");
			lcd_goto_xy(0,1);
			print("reached");
			play("o5 c#" );
			delay_ms(1000);
			p1.Ycurrent = 3;
			o1.packageAmount--;
			p1.amountOfX--;
		}
		
		
		if(amount.amountOfTwo>0)
		{
			turnToY(2,crossing);
			
			while(p1.Ycurrent!=2) //drive until the y coords is reached
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
				else if(facing == minY)
				{
					p1.Ycurrent--;
				}
			}
			
			amount.amountOfTwo--;
			clear();
			print("order");
			lcd_goto_xy(0,1);
			print("reached");
			play("o5 c#" );
			delay_ms(1000);
			p1.Ycurrent = 2;
			o1.packageAmount--;
			p1.amountOfX--;
		}
		
		
		if(amount.amountOfOne>0)
		{
			turnToY(1,crossing);
			
			while(p1.Ycurrent!=1) //drive until the y coords is reached
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
			
			amount.amountOfOne--;
			clear();
			print("order");
			lcd_goto_xy(0,1);
			print("reached");
			play("o5 c#" );
			delay_ms(1000);
			p1.Ycurrent = 1;
			o1.packageAmount--;
			p1.amountOfX--;
		}
		
		
		if(amount.amountOfZero>0)
		{
			turnToY(0,crossing);
			
			while(p1.Ycurrent!=0) //drive until the y coords is reached
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
			
			amount.amountOfZero--;
			clear();
			print("order");
			lcd_goto_xy(0,1);
			print("reached");
			play("o5 c#" );
			delay_ms(1000);
			p1.Ycurrent = 0;
			o1.packageAmount--;
			p1.amountOfX--;
		}
	}
}

void TurnBack()
{
	int crossing = 0;
	switch(facing)
	{
		case plusX:
		turn(1);
		facing=minY;
		break;
		
		case plusY:
		turn(2);
		facing=minY;
		break;
		
		case minX:
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

void turnToY(int y,int ccrossing)
{
	switch(facing) //turn facing minus X
	{
		case minX:
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
		
		case plusX:
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
				clear();
				print("help");
				lcd_goto_xy(0,1);
				print("me");
				play("o5 c#" );
				delay_ms(10000);
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
