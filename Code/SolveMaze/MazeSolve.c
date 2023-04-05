void solveMaze(int *mazeLocation)
{
	*mazeLocation %= 2;
	static int stockroom = 0;
	int inMaze = 1;
	static int irouteKnown = 0;
	static int i = 0;
		
	if(irouteKnown == 1)
	{
		routeKnown(&stockroom);
	}
	else
	{
		while(1)
		{
			int crossing = 0;
			followLine(&crossing, inMaze);
			if(crossing == 7)
			{
				break;
			}
			else if(crossing == 2)
			{
				set_motors(0,0);
				turn(0);
				arrayToStockroom[i] = 0;
			}
			else if(crossing == 99)
			{
				set_motors(0,0);
				turn(1);
				delay_ms(20);
				arrayToStockroom[i] = 2;
			}
			else if(crossing == 69)
			{
				*mazeLocation += 2;
				break;
			}
			else
			{
				set_motors(0,0);
				turn(1);
				arrayToStockroom[i] = 1;
			}
			i++;
			simplify(crossing, &i);		
		}
		size_t size = sizeof(arrayToStockroom) / sizeof(arrayToStockroom[0]);
		stockroom = 1;
		convertArray(size);
		irouteKnown = 1;
	}	
	*mazeLocation = stockroom;
}
