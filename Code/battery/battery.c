#include "battery.h"
#include <pololu/3pi.h>
#include <math.h>

void batteryRead( unsigned int *percentage)
{
	int average;
	
	print_long(voltage);
	for(int i = 0; i < 10; i++)
	{
		unsigned int voltage = read_battery_millivolts_3pi();
		average += voltage;
	}
	*percentage = average % 10;
}
