#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include "StockRoom.h"
#include "Charging.h"
#include "MazeSolve.h"
#include "FindLine.h"

struct am{int amountOfZero, amountOfOne, amountOfTwo, amountOfThree, amountOfFour;};
struct am amount;

void stockroomRoutine()
{
	int crossing = 0;
	delay_ms(100);
	solveMaze();
	delay_ms(100);
	followLine(&crossing, 0);
	crossing = 0;
	
	facing = minX;
	p1.Xcurrent = 0;
	p1.Ycurrent = 0;
	p1.Xpackage = 2;
	amount.amountOfZero = 0;
	amount.amountOfOne = 0;
	amount.amountOfTwo = 1;
	amount.amountOfThree = 1;
	amount.amountOfFour = 0;
	p1.amountOfX = 3;
	
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
		delay_ms(500);
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
		}
		//nextRound(); //decides witch packages are next
		findPackageX(); //go to the X
		delay_ms(500);
		findPackageY();	//get all the packages on this X
		
		amount.amountOfZero = 0;
		amount.amountOfOne = 0;
		amount.amountOfTwo = 0;
		amount.amountOfThree = 0;
		amount.amountOfFour = 0;
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

void nextRound()
{
	o1.Xorders[0] = 2;
	o1.Xorders[1] = 0;
	o1.Xorders[2] = 4;
	o1.Xorders[3] = 0;
		
	o1.Yorders[0] = 0;
	o1.Yorders[1] = 3;
	o1.Yorders[2] = 0;
	o1.Yorders[3] = 2;
	p1.Xpackage = 0;
	while(amount.amountOfZero==0 && amount.amountOfOne==0 && amount.amountOfTwo==0 && amount.amountOfThree==0 && amount.amountOfFour==0) // if no packages are at any of the Y coords of this X, continue looping till it is true or end has been reached.
	{
		for(int teller = 0; teller < 4; teller++)
		{
			if(o1.Xorders[teller] == p1.Xpackage)
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
					case 4:
					amount.amountOfFour++;
					break;
				}
			}
		}
		if(amount.amountOfZero==0 && amount.amountOfOne==0 && amount.amountOfTwo==0 && amount.amountOfThree==0 && amount.amountOfFour==0)
		{
			p1.Xpackage++;
		}
		if(p1.Xpackage==5)
		{
			o1.packageAmount = 0;
		}
	}
}

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
			switch(facing) //turn facing minus X
			{
				case minX:
				if(p1.Ycurrent<4)
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
				if(p1.Ycurrent<4)
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
				if(p1.Ycurrent<4)
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
				if(p1.Ycurrent<4)
				{
					turn(0);
					facing = plusY;
				}
				else
				{
					turn(2);
					facing = minY;
				}
				break;
			}
			
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
			delay_ms(300);
			p1.Ycurrent = 4;
			o1.packageAmount--;
			p1.amountOfX--;
		}
		
		if(amount.amountOfThree>0)
		{
			switch(facing) //turn facing minus X
			{
				case minX:
				if(p1.Ycurrent<3)
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
				if(p1.Ycurrent<3)
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
				if(p1.Ycurrent<3)
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
				if(p1.Ycurrent<3)
				{
					turn(0);
					facing = plusY;
				}
				else
				{
					turn(2);
					facing = minY;
				}
				break;
			}
			
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
			delay_ms(300);
			p1.Ycurrent = 3;
			o1.packageAmount--;
			p1.amountOfX--;
		}
		
		
		if(amount.amountOfTwo>0)
		{
			switch(facing) //turn facing minus X
			{
				case minX:
				if(p1.Ycurrent<2)
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
				if(p1.Ycurrent<2)
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
				if(p1.Ycurrent<2)
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
				if(p1.Ycurrent<2)
				{
					turn(0);
					facing = plusY;
				}
				else
				{
					turn(2);
					facing = minY;
				}
				break;
			}
			
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
			delay_ms(300);
			p1.Ycurrent = 2;
			o1.packageAmount--;
			p1.amountOfX--;
		}
		
		
		if(amount.amountOfOne>0)
		{
			switch(facing) //turn facing minus X
			{
				case minX:
				if(p1.Ycurrent<1)
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
				if(p1.Ycurrent<1)
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
				if(p1.Ycurrent<1)
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
				if(p1.Ycurrent<1)
				{
					turn(0);
					facing = plusY;
				}
				else
				{
					turn(2);
					facing = minY;
				}
				break;
			}
			
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
			delay_ms(300);
			p1.Ycurrent = 1;
			o1.packageAmount--;
			p1.amountOfX--;
		}
		
		
		if(amount.amountOfZero>0)
		{
			switch(facing) //turn facing minus X
			{
				case minX:
				if(p1.Ycurrent<0)
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
				if(p1.Ycurrent<0)
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
				if(p1.Ycurrent<0)
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
				if(p1.Ycurrent<0)
				{
					turn(0);
					facing = plusY;
				}
				else
				{
					turn(2);
					facing = minY;
				}
				break;
			}
			
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
			delay_ms(300);
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
	}
	while(crossing!=1 && crossing!=5 && crossing!=7)
	{
		crossing = 0;
		followLine(&crossing, 0);
		if(crossing != 0)
		{
			turn(0);
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
