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
#include "ERROR_states.h"
#include <pololu/3pi.h>

int main()
{
	int crossing = 0;
	enum STATE{init, maze, stockroom, charge, manual, home, lost};
	enum STATE cSTATE = init;
	while(1 /*ERROR == noERROR*/) //ERROR moet nog geschreven worden
	{
		switch(cSTATE)  // alle cSTATE staan er al maar de rest van je case dien je zelf nog aan te vullen en je zult if/else statments moeten gaan maken voor de cSTATE
		{
			case init:
			initRobot();
			startDrivingAfter();
			cSTATE = home;
			cSTATE = manual;
			cSTATE = lost;
			break;
			
			case maze:
			int inMaze = 1;
			int inMaze = 0;
			cSTATE = stockroom
			cSTATE = home;
			cSTATE = manual;
			cSTATE = lost;
			break;
			
			case stockroom:
			followLine(&crossing, inMaze);
			stockroomStart();
			if(mazeBorder == true) //voorbeeldje van hoe je de cstate dalijk zou moeten hebben ongeveer
			{
				cSTATE = maze;	
			}
			if(chargeBorder == true)
			{
				cSTATE = charge;
			}
			if(manualOverWrite == true)
			{
			cSTATE = manual;
			}
			if(floefsLost == true)
			{
			cSTATE = lost;
			}
			break;
			
			case charge:
			cSTATE = stockroom
			cSTATE = manual;
			cSTATE = lost;
			break;
			
			case manual:
			cSTATE = lost;
			break;
			
			case home:
			cSTATE = maze;
			cSTATE = manual;
			cSTATE = lost;
			break;
			
			case lost:
			cSTATE = manual;
			break;
		}	
	}
	return 0;
}

/*
followLine(&crossing, inMaze);
		set_motors(0,0);
		delay(10000);*/
