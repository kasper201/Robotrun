#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include "StockRoom.h"

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
		while(p1.Xcurrent<p1.Xpackage && p1.Xcurrent!=p1.Xpackage) //drive until the X coords is reached
		{
			followLine(&crossing, 0);
			if(crossing != 0)
			{
				turn(0);
				p1.Xcurrent++;
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
	for(int teller = 0; teller<32; teller++)
	{
		if(o1.Xorders[teller]==p1.Xcurrent)
		{
			switch(o1.Yorders[teller])
			{
				case 0:
				amount.amountOfZero++;
				break;
				case 1:
				amount.amountOfOne++;
				break;
				case 2:
				amount.amountOfTwo++;
				break;
				case 3:
				amount.amountOfThree++;
				break;
			}
		}
	}
	while(/*there are still orders on this x*/)
	{
		if(p1.Ycurrent==p1.Ypackage)
		{
			clear();
			print("order");
			lcd_goto_xy(0,1);
			print("reached");
			play("o5 c#" );	
		}
		else
		{
			clear();
			print("XCoords");
			lcd_goto_xy(0,1);
			print("reached");
			GetY();
		}	
	}	
	amount.amountOfZero = 0;
	amount.amountOfOne = 0;
	amount.amountOfTwo = 0;
	amount.amountOfThree = 0;
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
	p1.Xcurrent=0;
	p1.Ycurrent=0;
	while(*mazeBorder != true)
	{
		followLine(&crossing, 0);
		if(crossing != 0)
		{
			turn(0);
		}
	}
}

void GetY()
{
	if(amount.amountOfThree>0)
	{
		switch(facing) //turn facing minus X
		{
			case minY:
			turn(1);
			facing = plusY;
			break;
			case plusX:
			turn(2);
			facing = plusY;
			break;
			case plusY:
			turn(3);
			facing = plusY;
			break;
		}
		while(p1.Ycurrent<p1.Ypackage) //drive until the y coords is reached
		{
			followLine(&crossing, 0);
			if(crossing != 0)
			{
				turn(0);
			}
		}
		clear();
		print("order");
		lcd_goto_xy(0,1);
		print("reached");
		play("o5 c#" );
	}
	if(amount.amountOfTwo>0)
	{
		while(p1.Ycurrent<p1.Ypackage) //drive until the y coords is reached
		{
			followLine(&crossing, 0);
			if(crossing != 0)
			{
				turn(0);
			}
		}
		clear();
		print("order");
		lcd_goto_xy(0,1);
		print("reached");
		play("o5 c#" );
	}
	if(amount.amountOfOne>0)
	{
		while(p1.Ycurrent<p1.Ypackage) //drive until the y coords is reached
		{
			followLine(&crossing, 0);
			if(crossing != 0)
			{
				turn(0);
			}
		}
		clear();
		print("order");
		lcd_goto_xy(0,1);
		print("reached");
		play("o5 c#" );
	}
	if(amount.amountOfZero>0)
	{
		while(p1.Ycurrent<p1.Ypackage) //drive until the y coords is reached
		{
			followLine(&crossing, 0);
			if(crossing != 0)
			{
				turn(0);
			}
		}
		clear();
		print("order");
		lcd_goto_xy(0,1);
		print("reached");
		play("o5 c#" );
	}
}
