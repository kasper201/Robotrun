/* Robotrun - an application for the Pololu 3pi Robot
 *
 * This application uses the Pololu AVR C/C++ Library.  For help, see:
 * -User's guide: http://www.pololu.com/docs/0J20
 * -Command reference: http://www.pololu.com/docs/0J18
 *
 * Created: 3/18/2023 11:16:12 AM
 *  Author: Kaspe
 */

#include <pololu/3pi.h>
#include "FindLine.h"

void routeKnown(int sizeArray, int turnArray[], int **state)
{
	int inMaze = 1;
	int resetCrossing = 0;
	if(*(*(state)) == 0)//if stockStart == 0 robot will go from start to stockroom otherwise if stockStart == 1 the robot will go from stockroom to start
	{
		for(int i = 0; i <= sizeArray; i++)
		{
			followLine(&resetCrossing, inMaze);
			turn(turnArray[i]);
			set_motors(50,50);
			delay_ms(50);
			**state = 1;
		}
	}
	
	else
	{
		for(int i = sizeArray; i >= 0; i--)
		{
			followLine(&resetCrossing, inMaze);
			turn(turnArray[i]);
			set_motors(50,50);
			delay_ms(50);
			**state = 0;
		}
	}
}

void solveMaze(int *irouteKnown, int sizeArray, int (*turnArray)[sizeArray], int *state) //set when implementing the code the state to Stockroom((5,0, facing -x) do this together with Mik
{
	int crossing;
	int inMaze = 1;
	int foundEnd = 0;
	int whatkindofcrossing[64];
	int deadEndsFound = 0;
	if(*irouteKnown == 1)//if route known just drive like the old array
	{
		routeKnown(sizeArray, *turnArray, &state);
	}
	else
	{
		int turnValue = 1;
		int i = 0;
		while(foundEnd != 1) //go on untill end of maze found
		{
			crossing = 0;
			followLine(&crossing, inMaze);//drive till crossing or dead end found
			whatkindofcrossing[i] = crossing; //save what type of crossing
			if(crossing == 7)
			{
				foundEnd = 1;
			}
			else if(crossing == 2) // if able to go left and straight go straight
			{
				turn(0);
				*turnArray[i] = 0;
			}
			else if(crossing == 99) // if end of line turn around
			{
				turn(2);
				if(turnValue == 0) // if straight was wrong go left
				{
					turnValue = 3;
				}
				else if(turnValue == 1) // if right was wrong go straight
				{
					turnValue = 0;
				}
				else
				{
					i--;
					if((*turnArray[i-1] == 1) && whatkindofcrossing[i-1] != 1) // if last turn was to go to right thats wrong so go straight unless unable to go straight (seen from if its a new route)
					{
						turnValue = 0;
					}
					else if((*turnArray[i-1] == 1) && whatkindofcrossing[i-1] == 1)
					{
						turnValue = 3;
					}
					else if((*turnArray[i-1] == 0) && whatkindofcrossing[i-1] != 2) // if last turn was to go straight go left unless unable to go left (seen from if you restart the route
					{
						turnValue = 3;
					}
					else 
					{
						// won't work.... I probably could make it work indefinetely but that would require some more clever thinking
					}
				}
				i--;
				continue; //go back to the top to take next turn
			}
			else //normal crossing and able to go right so go right
			{
				turn(1);
				*turnArray[i] = turnValue; //save turn value. this value changes based on if its been at a dead end
			}
			i++;
			deadEndsFound++;
		}
		if(deadEndsFound > 0)
		{
			*irouteKnown = 0;
		}
		else
		{
			*irouteKnown = 1;
		}
		*state = 1;
	}
}

int main()
{ 
	initRobot();
	
	int array[] = {1,3,1,2,2};//will become empty in actual code, this is just for testing purposes
	int sizeArray = sizeof(array)/sizeof(int);
	int state = 0;
	int irouteKnown = 0;
	while(1)
	{
		solveMaze(&irouteKnown, sizeArray, &array, &state);
	}
}
