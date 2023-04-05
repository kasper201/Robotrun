/* ROBO_RUN - an application for the Pololu 3pi Robot
*
* This application uses the Pololu AVR C/C++ Library.  For help, see:
* -User's guide: http://www.pololu.com/docs/0J20
* -Command reference: http://www.pololu.com/docs/0J18
*
* Created: 3/2/2023 10:40:48 AM
*  Author: mikvb
*/
#include "FindLine.h"
#include "StockRoom.h"
#include "MazeSolve.h"
#include "Charging.h"
#include "ComRead.h"
#include <pololu/3pi.h>

enum STATE{init, maze, stockroom, charge, manual, home, lost};
enum STATE cSTATE = init;

int main()
{
	while(1)
	{
		int percentage = 60;
		o1.packageAmount = 2;
		int backOrNot;
		
		switch(cSTATE)  // alle cSTATE staan er al maar de rest van je case dien je zelf nog aan te vullen en je zult if/else statments moeten gaan maken voor de cSTATE
		{
			case init: //init state
			clear();
			initRobot();
			followLine(0,0);
			set_motors(0,0);
			cSTATE = home;
			break;
			
			
			case maze: //maze state
			solveMaze(&backOrNot);
			if(backOrNot == 1)
			{
				cSTATE = stockroom;
			}
			else if(backOrNot == 0)
			{
				cSTATE = home;
			}
			break;
			
			
			case stockroom: //stockroom state
			stockroomRoutine();
			delay_ms(100);
			cSTATE = maze;
			break;
			
			
			case charge: //charge state
			solveMaze(0);
			int *ChargePoint = 0;
			passingToCharge();
			followCharge(ChargePoint);
			timeToCharge();
			passingToCharge2();
			solveMaze(0);
			cSTATE = home;
			break;
			
			
			case manual: //manual state
			//floefsWakes();
			cSTATE = init;
			break;
			
			
			case home: //home state
			clear();
			print("FLOEFS");
			lcd_goto_xy(0,1);
			print("WAKES");
			delay_ms(1000);
			if(percentage<60)
			{
				cSTATE = charge;
			}
			if(o1.packageAmount>0)
			{
				cSTATE = maze;
			}
			break;
			
			
			case lost: //lost state
			clear();
			print("HELP|:(");
			lcd_goto_xy(0,1);
			print("FLOEFS");
			play("o5 c#" );
			delay_ms(300);
			if(1==2)
			{
				cSTATE = manual;
			}
			break;
		}
	}
	return 0;
}
