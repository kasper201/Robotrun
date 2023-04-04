void floefsWakes()
{
	int vooruit;
	int rechts;
	int links;
	int achteruit;
	int knop;
	knop == serial_read();
	switch(knop)
	{
		case 1: //rechts
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
		
		
		case 2: //links
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
		
		
		case 3: //achteruit
		achteruit = -50;
		if(achteruit != -150)
		{
			achteruit--;
			delay_ms(5);
		}
		set_motors(achteruit,achteruit);
		break;
		
		
		case 4: //vooruit
		vooruit = 50;
		if(vooruit != 150)
		{
			vooruit++;
			delay_ms(5);
		}
		set_motors(vooruit,vooruit);
		break;
		
		
		case 5: //geen knop
		rechts = 0;
		links = 0;
		vooruit = 0;
		achteruit = 0;
		set_motors(00,00);
		break;
	}
}
