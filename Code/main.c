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
	bool &mazeBorder;
	bool &chargeBorder;
	enum STATE{init, maze, stockroom, charge, manual, home, lost};
	enum STATE cSTATE = init;
	
	while(1 /*ERROR == noERROR*/) //ERROR moet nog geschreven worden
	{
		switch(cSTATE)  // alle cSTATE staan er al maar de rest van je case dien je zelf nog aan te vullen en je zult if/else statments moeten gaan maken voor de cSTATE
		{
			case init: //init state
			initRobot();
			startDrivingAfter();
			cSTATE = home;
			cSTATE = manual;
			cSTATE = lost;
			break;
			
			case maze: //maze state
			int inMaze = 1;
			int inMaze = 0;
			cSTATE = stockroom
			cSTATE = home;
			cSTATE = manual;
			cSTATE = lost;
			break;
			
			case stockroom: //stockroom state
			if(manualOverWrite == true) //if there is an manual overwrite switch state
			{
				cSTATE = manual;
			}
			
			if(floefsLost == true) //if the robot thinks its lost switch state
			{
				cSTATE = lost;
			}
			
			if(battery == 0) //if the battery is low drive to the charging station
			{
				passingToCharge();
			}
			else //standard stockroom routine
			{
				stockroomRoutine();
				cSTATE = maze;	
			}
			break;
			
			case charge: //charge state
			cSTATE = stockroom
			cSTATE = manual;
			cSTATE = lost;
			break;
			
			case manual: //manual state
			cSTATE = lost;
			break;
			
			case home: //home state
			cSTATE = maze;
			cSTATE = manual;
			cSTATE = lost;
			break;
			
			case lost: //lost state
			cSTATE = manual;
			break;
		}	
	}
	return 0;
}
