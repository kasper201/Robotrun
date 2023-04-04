void floefsWakes()
{
	pololu_3pi_init(2000);
	play_mode(PLAY_CHECK);
	clear();

	// start receiving data at 115.2 kbaud
	serial_set_baud_rate(9600);
	serial_receive_ring(buffer, 100);
	
	int vooruit;
	int rechts;
	int links;
	int achteruit;
	int knop;
	knop == serial_read();
	
	char command = read_next_byte();
	
	switch(command)
	{
		case (char)0x34: //rechts
		rechts = -50;
		links = 50;
		if(links != 150)
		{
			rechts--;
			links++;
			delay_ms(5);
		}
		set_motors(links,rechts);
		break;
		
		
		case (char)0x33: //links
		rechts = 50;
		links = -50;
		if(links != -150)
		{
			rechts++;
			links--;
			delay_ms(5);
		}
		set_motors(links,rechts);
		break;
		
		
		case (char)0x32: //achteruit
		achteruit = -50;
		if(achteruit != -150)
		{
			achteruit--;
			delay_ms(5);
		}
		set_motors(achteruit,achteruit);
		break;
		
		
		case (char)0x31:: //vooruit
		vooruit = 50;
		if(vooruit != 150)
		{
			vooruit++;
			delay_ms(5);
		}
		set_motors(vooruit,vooruit);
		break;
		
		
		case (char)0x35: //geen knop
		rechts = 0;
		links = 0;
		vooruit = 0;
		achteruit = 0;
		set_motors(0,0);
		break;
		
		default:
		clear();
		print("Bad cmd");
		lcd_goto_xy(0,1);
		print_hex_byte(command);
		play("o7l16crc");
		continue; // bad command
	}
}
