void passingToCharge()
{
	int crossing=0;
	followLine(&crossing, 0);
	turn(1);
	while(crossing!=1)
	{
		crossing=0;
		followLine(&crossing, 0);
		if(crossing!=0)
		{
			turn(0);
		}
	}
	turn(1);
	set_motors(50, 50);
	delay_ms(200);
}

passingToCharge2()
{
	int crossing=0;
	followLine(&crossing, 0);
	turn(3);
	while(crossing!=1)
	{
		crossing=0;
		followLine(&crossing, 0);
		if(crossing!=0)
		{
			turn(0);
		}
	}
	turn(3);
	while(crossing!=7)
	{
		crossing=0;
		followLine(&crossing, 0);
	}
}

void batteryLevel()
{
	unsigned int read_battery_millivolts_3pi()
	{
		return readAverage(6,10)*5000L*3/2/1023;
	}
}

void timeToCharge()
{
	clear();
	print("FLOEFS");
	lcd_goto_xy(0,1);
	print("SLEEPS");
	play("o5 c#" );
	delay_ms(10000);
}
