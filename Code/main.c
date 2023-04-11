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

enum STATE{init, stockroom, charge, manual, home, lost};
enum STATE cSTATE = init;

int main()
{
	int percentage = 80;
	while(1)
	{
		switch(cSTATE)
		{
			case init: //init state
			clear();
			initRobot();
			delay_ms(100);
			clear();
			print("FLOEFS");
			lcd_goto_xy(0,1);
			print("WAKES");
			delay_ms(100);
			followLine(0,0);
			set_motors(0,0);
			delay_ms(100);
			cSTATE = home;
			break;
			
			case home: // the state when it has no orders yet
			clear();
			print("FLOEFS");
			lcd_goto_xy(0,1);
			print("HOME");
			delay_ms(500);
			receiveOrder();
			if(percentage<60)
			{
				cSTATE = charge;
			}
			if(o1.packageAmount>0 && percentage>=60)
			{
				cSTATE = stockroom;
			}
			break;
			
			case stockroom:
			stockroomRoutine();
			cSTATE = home;
			break;
			
			case charge:
			chargeRoutine();
			cSTATE = home;
			break;
			
			case manual: //manual state
			drive();
			cSTATE = init;
			break;
			
			case lost: //lost state
			clear();
			print("HELP|:(");
			lcd_goto_xy(0,1);
			print("FLOEFS");
			play("o5 c#" );
			delay_ms(300);
			cSTATE = manual;
			break;
			
			default:
			spin();
			break;
		}
	}
}
