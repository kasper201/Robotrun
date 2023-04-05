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

void batteryRead( unsigned int *percentage)
{
	int average;
	
	print_long(voltage);
	for(int i = 0; i < 10; i++)
	{
		unsigned int voltage = read_battery_millivolts_3pi();
		average += voltage;
	}
	*percentage = (read_battery_millivolts_3pi()/50);
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
