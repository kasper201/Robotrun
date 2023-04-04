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
#include <pololu/3pi.h>

int main()
{
	enum STATE{init, maze, stockroom, charge, manual, home, lost};
	enum STATE cSTATE = init;
	
	while(1)
	{
		switch(cSTATE)  // alle cSTATE staan er al maar de rest van je case dien je zelf nog aan te vullen en je zult if/else statments moeten gaan maken voor de cSTATE
		{
			case init: //init state
			clear();
			initRobot();
			cSTATE = stockroom;
			break;
			
			
			case maze: //maze state
			solveMaze();
			cSTATE = stockroom;
			cSTATE = home;
			if(1==2)
			{
				cSTATE = manual;
			}
			if(1==2)
			{
				cSTATE = lost;
			}
			break;
			
			
			case stockroom: //stockroom state
			stockroomRoutine();
			cSTATE = maze;	
			if(1==2)
			{
				cSTATE = manual;
			}
			if(1==2)
			{
				cSTATE = lost;
			}
			break;
			
			
			case charge: //charge state
			solveMaze();
			int ChargePoint = 0;
			passingToCharge();
			followCharge(ChargePoint);
			if(1==2)
			{
				cSTATE = manual;
			}
			if(1==2)
			{
				cSTATE = lost;
			}
			break;
			
			
			case manual: //manual state
			floefsWakes();
			cSTATE = init;
			break;
			
			
			case home: //home state
			floefsSlaapt();
			cSTATE = maze;
			if(1==2)
			{
				cSTATE = manual;
			}
			if(1==2)
			{
				cSTATE = lost;
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
