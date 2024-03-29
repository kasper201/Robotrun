#include "FindLine.h"
#include "StockRoom.h"
#include "MazeSolve.h"
#include "Charging.h"
#include "ComRead.h"
#include "ManualDrive.h"
#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include <pololu/PololuQTRSensors.h>

char buffer[100];
unsigned char read_index = 0;

char readNextByte()
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

int getOrder() // get order from wixel
{
	play_mode(PLAY_CHECK);
	clear();

	serial_set_baud_rate(9600); //make sure you're receiving at 9600 baudrate
	serial_receive_ring(buffer, 100);
	
	readNextByte(); //waits for startbit
	clear();
	int data = readNextByte();
	switch(data)
	{
		case(char)0x30:
		return 0;
		break;
		
		case(char)0x31:
		return 1;
		break;
		
		case(char)0x32:
		return 2;
		break;
		
		case(char)0x33:
		return 3;
		break;
		
		case(char)0x34:
		return 4;
		break;
		
		case(char)0x39:
		return 5;
		break;
	}
}

int batteryLvlSim()
{
	play_mode(PLAY_CHECK);
	clear();

	serial_set_baud_rate(9600); //make sure you're receiving at 9600 baudrate
	serial_receive_ring(buffer, 100);
	
	readNextByte(); //waits for startbit
	clear();
	int data = readNextByte();
	switch(data)
	{
	case(char)0x31:
	return 10;
	break;
	
	case(char)0x32:
	return 20;
	break;

	case(char)0x33:
	return 30;
	break;
	
	case(char)0x34:
	return 40;
	break;
	
	case(char)0x35:
	return 50;
	break;
	
	case(char)0x36:
	return 60;
	break;
	
	case(char)0x37:
	return 70;
	break;
	
	case(char)0x38:
	return 80;
	break;
	
	case(char)0x39:
	return 90;
	break;
	}
}

void receiveOrder(int *batterySim) // receive order in integer form
{
	int orderAmount = getOrder();
	clear();
	if(orderAmount == 5)
	{
		*batterySim = batteryLvlSim();
		print_long(batterySim);
	}
	else
	{
		print_long(orderAmount);
		delay_ms(1000);
		for(int orderIndex = 0; orderIndex < orderAmount; orderIndex++)
		{
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
	clear();
	print("re-");
	lcd_goto_xy(0,1);
	print("ceived");
	delay_ms(1000);
	clear();
}

void receiveOrderToBreak()
{
	play_mode(PLAY_CHECK);

	serial_set_baud_rate(9600); //make sure you're receiving at 9600 baudrate
	serial_receive_ring(buffer, 100);
	
	readNextByte(); // discard start byte
	char byteStop = readNextByte(); //write byte into byteStop for detection to stop
	if(byteStop == 0xFF)
	{
		set_motors(0,0);
		clear();
		print("Emerge-");
		lcd_goto_xy(0,1);
		print("ncy");
		wait_for_button_press(BUTTON_B); // wait on button press to try to continue, otherwise reboot
		wait_for_button_release(BUTTON_B);
	}
	else if(byteStop == 0xFE)
	{
		//just continue if stop button is not pressed
	}
}

void batteryRead(unsigned int *percentage)
{
	double average = 0;

	for(int i = 0; i < 10; i++)
	{
		double millivolts = read_battery_millivolts();
		average += millivolts;
	}
	average = average / 10;
	*percentage = average/6000*100;
}
