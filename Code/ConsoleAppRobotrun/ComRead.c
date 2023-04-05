#include <pololu/3pi.h>
#include "ComRead.h"
#include "Charging.h"
#include "MazeSolve.h"
#include "FindLine.h"
#include "StockRoom.h"

int getOrder()
{
	read_next_byte(); //waits for startbit
	clear();
	int data = read_next_byte();
	switch(data)
	{
		case(char)0x30:
		//xOrder[orderIndex] = 0;
		return 0;
		
		break;
		
		case(char)0x31:
		//xOrder[orderIndex] = 1;
		return 1;
		break;
		
		case(char)0x32:
		//xOrder[orderIndex] = 2;
		return 2;
		break;
		
		case(char)0x33:
		//xOrder[orderIndex] = 3;
		return 3;
		break;
		
		
		case(char)0x34:
		//xOrder[orderIndex] = 4;
		return 4;
		break;
	}
}

void saveMe()
{
	int orderAmount = getOrder();
	for(int orderIndex = 0; orderIndex < orderAmount; orderIndex++)
	{
		//char help = read_next_byte();
		//if(read_next_byte() == 0x30)
		o1.Xorders[orderIndex] = getOrder();
		o1.Yorders[orderIndex] = getOrder();
		
	}
	
	for(int i = 0; i < orderAmount; i++)
	{
		clear();
		print_long(o1.Xorders[i]);
		print_character(',');
		print_long(o1.Yorders[i]);
		delay_ms(2000);	
	}
	
	o1.packageAmount = orderAmount;
}

void comCheck()
{
	//send_battery_millivolts();
	//send_state();
}

void send_battery_millivolts()
{
	int message[1];
	message[0] = read_battery_millivolts();
	serial_send_blocking((char *)message, 2);
}

void send_state()
{/*
	int message[1];
	message[0] = cSTATE;
	serial_send_blocking((char *)message, 2);*/
}
