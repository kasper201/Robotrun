#include "manual.h"
#include <pololu/3pi.h>

void recieveOrderToBreak()
{
	char byteStop = read_next_byte();
	if(byteStop == 0xFF)
	{
		set_motors(0,0);
		wait_for_button_press(BUTTON_B);
		wait_for_button_release(BUTTON_B);
	}
	else
	{
		
	}
}
