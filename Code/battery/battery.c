#include "battery.h"
#include <pololu/3pi.h>
#include <math.h>

void batteryRead( unsigned int *percentage)
{
	int average;
	unsigned int voltage = read_battery_millivolts_3pi();
	print_long(voltage);
	for(int i = 0; i < 10; i++)
	{
		average += voltage;
	}
	*percentage = average % 10;
}
