#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include "StockRoom.h"

void stockroomRoutine()
{
	int packageAmount = 0;
	int crossing = 0;
	facing = minX;
	p1.Xcurrent = 0;
	p1.Ycurrent = 0;
	followLine(&crossing, 0);
	crossing = 0;
	clear();
	print("order");
	lcd_goto_xy(0,1);
	print("reached");
	play("o5 c#" );
	delay_ms(3000);
	while(packageAmount != 0)//there are still orders to be completed
	{
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
		
		nextRound(); //decides witch packages are next
		findPackageX(); //go to the X
		findPackageY();	//get all the packages on this X
		
		amount.amountOfZero = 0;
		amount.amountOfOne = 0;
		amount.amountOfTwo = 0;
		amount.amountOfThree = 0;
	}
	TurnBack();//drive back to the maze
}

void nextRound();
{
	p1.Xpackage = 0;
	while(amount.amountOfZero==0 && amount.amountOfOne==0 && amount.amountOfTwo==0 && amount.amountOfThree==0)
	{
		for(int teller=0; teller<32; teller++)
		{
			if(o1.Xorders[teller]==p1.Xpackage)
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
		if(amount.amountOfZero==0 && amount.amountOfOne==0 && amount.amountOfTwo==0 && amount.amountOfThree==0)
		{
			p1.Xpackage++;
		}
	}
}

void findPackageX()
{
	int crossing = 0;
	while(p1.Xcurrent<p1.Xpackage && p1.Xcurrent!=p1.Xpackage) //drive until the X coords is reached
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
	while(amount.amountOfZero!=0 && amount.amountOfOne!=0 && amount.amountOfTwo!=0 && amount.amountOfThree!=0)
	{
		if(amount.amountOfThree>0)
		{
			switch(facing) //turn facing minus X
			{
				case minX:
				if(p1.Ycurrent<3)
				{
					turn(1);
				}
				else
				{
					turn(3)
				}
				facing = plusY;
				break;
				
				case minY:
				if(p1.Ycurrent<3)
				{
					turn(2);
				}
				else
				{
					turn(0)
				}
				facing = plusY;
				break;
				
				case plusX:
				if(p1.Ycurrent<3)
				{
					turn(3);
				}
				else
				{
					turn(1)
				}
				facing = plusY;
				break;
				
				case plusY:
				if(p1.Ycurrent<3)
				{
					turn(0);
				}
				else
				{
					turn(2)
				}
				facing = plusY;
				break;
			}
			
			while(p1.Ycurrent<=3) //drive until the y coords is reached
			{
				crossing = 0;
				followLine(&crossing, 0);
				if(crossing != 0)
				{
					turn(0);
				}
			}
			
			amount.amountOfThree--;
			clear();
			print("order");
			lcd_goto_xy(0,1);
			print("reached");
			play("o5 c#" );
			delay_ms(300);
		}
		
		
		if(amount.amountOfTwo>0)
		{
			switch(facing) //turn facing minus X
			{
				case minX:
				if(p1.Ycurrent<2)
				{
					turn(1);
				}
				else
				{
					turn(3)
				}
				facing = plusY;
				break;
				
				case minY:
				if(p1.Ycurrent<2)
				{
					turn(2);
				}
				else
				{
					turn(0)
				}
				facing = plusY;
				break;
				
				case plusX:
				if(p1.Ycurrent<2)
				{
					turn(3);
				}
				else
				{
					turn(1)
				}
				facing = plusY;
				break;
				
				case plusY:
				if(p1.Ycurrent<2)
				{
					turn(0);
				}
				else
				{
					turn(2)
				}
				facing = plusY;
				break;
			}
			
			while(p1.Ycurrent<=2) //drive until the y coords is reached
			{
				crossing = 0;
				followLine(&crossing, 0);
				if(crossing != 0)
				{
					turn(0);
				}
			}
			
			amount.amountOfTwo--;
			clear();
			print("order");
			lcd_goto_xy(0,1);
			print("reached");
			play("o5 c#" );
			delay_ms(300);
		}
		
		
		if(amount.amountOfOne>0)
		{
			switch(facing) //turn facing minus X
			{
				case minX:
				if(p1.Ycurrent<1)
				{
					turn(1);
				}
				else
				{
					turn(3)
				}
				facing = plusY;
				break;
				
				case minY:
				if(p1.Ycurrent<1)
				{
					turn(2);
				}
				else
				{
					turn(0)
				}
				facing = plusY;
				break;
				
				case plusX:
				if(p1.Ycurrent<1)
				{
					turn(3);
				}
				else
				{
					turn(1)
				}
				facing = plusY;
				break;
				
				case plusY:
				if(p1.Ycurrent<1)
				{
					turn(0);
				}
				else
				{
					turn(2)
				}
				facing = plusY;
				break;
			}
			
			while(p1.Ycurrent<=1) //drive until the y coords is reached
			{
				crossing = 0;
				followLine(&crossing, 0);
				if(crossing != 0)
				{
					turn(0);
				}
			}
			
			amount.amountOfOne--;
			clear();
			print("order");
			lcd_goto_xy(0,1);
			print("reached");
			play("o5 c#" );
			delay_ms(300);
		}
		
		
		if(amount.amountOfZero>0)
		{
			switch(facing) //turn facing minus X
			{
				case minX:
				if(p1.Ycurrent<0)
				{
					turn(1);
				}
				else
				{
					turn(3)
				}
				facing = plusY;
				break;
				
				case minY:
				if(p1.Ycurrent<0)
				{
					turn(2);
				}
				else
				{
					turn(0)
				}
				facing = plusY;
				break;
				
				case plusX:
				if(p1.Ycurrent<0)
				{
					turn(3);
				}
				else
				{
					turn(1)
				}
				facing = plusY;
				break;
				
				case plusY:
				if(p1.Ycurrent<0)
				{
					turn(0);
				}
				else
				{
					turn(2)
				}
				facing = plusY;
				break;
			}
			
			while(p1.Ycurrent<=0) //drive until the y coords is reached
			{
				crossing = 0;
				followLine(&crossing, 0);
				if(crossing != 0)
				{
					turn(0);
				}
			}
			
			amount.amountOfZero--;
			clear();
			print("order");
			lcd_goto_xy(0,1);
			print("reached");
			play("o5 c#" );
			delay_ms(300);
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

