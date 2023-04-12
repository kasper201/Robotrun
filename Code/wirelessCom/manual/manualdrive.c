#include <pololu/3pi.h>
#include "manual.h"

char buffer[100];

void drive()
{
	int escaped = 0;
	pololu_3pi_init(2000);
	play_mode(PLAY_CHECK);
	clear();

	// start receiving data at 115.2 kbaud
	serial_set_baud_rate(9600);
	serial_receive_ring(buffer, 100);
	
	int vooruit = 100;
	int rechts = -50;
	int rechtsL = 50;
	int links = -50;
	int linksR = 50;
	int achteruit = -100;
	
	
	while(escaped == 0)
	{
		read_next_byte();
		delay_us(1);
		char command = read_next_byte();
		switch(command)
		{
			case (char)0x34: //rechts
			vooruit = 100;
			achteruit = -100;
			links = -50;
			linksR = 50;
			if(rechtsL != 150)
			{
				rechts--;
				rechtsL++;
				delay_ms(5);
			}
			set_motors(rechtsL,rechts);
			break;
		
		
			case (char)0x33: //links
			vooruit = 100;
			achteruit = -100;
			rechts = -50;
			rechtsL = 50;
			if(links != -150)
			{
				linksR++;
				links--;
				delay_ms(5);
			}
			set_motors(links,linksR);
			break;
		
		
			case (char)0x32: //achteruit
			rechts = -50;
			rechtsL = 50;
			links = -50;
			linksR = 50;
			vooruit = 100;
			if(achteruit != -200)
			{
				achteruit--;
				delay_ms(5);
			}
			set_motors(achteruit,achteruit);
			break;
		
		
			case (char)0x31: //vooruit
			rechts = -50;
			rechtsL = 50;
			links = -50;
			linksR = 50;
			achteruit = -100;
			if(vooruit != 200)
			{
				vooruit++;
				delay_ms(5);
			}
			set_motors(vooruit,vooruit);
			break;
		
		
			case (char)0x35: //geen knop
			rechts = -50;
			rechtsL = 50;
			links = -50;
			linksR = 50;
			achteruit = -100;
			vooruit = 100;
			set_motors(0,0);
			break;
			
			case (char)0x36:
			escaped = 1;
			break;
		
			default:
			clear();
			print("Bad cmd");
			lcd_goto_xy(0,1);
			print_hex_byte(command);
			play("o7l16crc");
			break; // bad command
			
			if(buffer[99] != 0)
			{
				for(int i = 0; i < 100; i++)
				{
					buffer[i] = 0;
				}
			}
		}
	}
}

unsigned char read_index = 0;

char read_next_byte()
{
	while(serial_get_received_bytes() == read_index)
	{
		play_check();		
	}
	char ret = buffer[read_index];
	read_index ++;
	if(read_index >= 100)
	read_index = 0;
	return ret;
}
