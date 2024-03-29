#include "FindLine.h"
#include "StockRoom.h"
#include "MazeSolve.h"
#include "Charging.h"
#include "ComRead.h"
#include "ManualDrive.h"
#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include <pololu/PololuQTRSensors.h>

//the startup screen
const char startup_line1[] PROGMEM = "RobotRun";
const char startup_line2[] PROGMEM = "KARBONKE";
const char startup_line3[] PROGMEM = " Floefs";
const char StartupMelody[] PROGMEM = "T180 O5 MS L8 EERERCE4 L4 GR<GR ";

int detectObstacle()
{
	int proximity = 0;
	for(int i = 0; i < 4; i++){
		proximity += analog_read(7);
		print_long(proximity);
	}
	proximity = proximity/4;
	if(proximity >= 400)
	{
		set_motors(0,0);
		return 1;
	}
	else
	{
		return 0;
	}
}

void initDistance()
{
	DDRC  &= ~(1<< PORTC5);
	PORTC &= ~(1<< PORTC5);
}


void initRobot()
{
	unsigned int percentage;
	pololu_3pi_init(2000);
	
	//play welcome line
	print_from_program_space(startup_line1);
	lcd_goto_xy(0,1);
	print_from_program_space(startup_line2);
	play_from_program_space(StartupMelody);
	delay_ms(1000);
	
	clear();
	print_from_program_space(startup_line3);
	delay_ms(2000);
	
	clear();
	print("Press B");
	wait_for_button_press(BUTTON_B);
	lcd_goto_xy(0,1);
	batteryRead(&percentage);
	print_long(percentage);
	print("%");
	wait_for_button_release(BUTTON_B);
	play("T 180 MLCEG"); //play sound to display start of calibration
	initDistance();
	delay_ms(600);
	//calibration
	play("L4 MSD.D.D R8 ! O5 G2. R8" );
	for(int calibrationCounter = 0; calibrationCounter < 113; calibrationCounter++)
	{
		print("Calib-");
		lcd_goto_xy(0,1);
		print("rating  ");
		if(calibrationCounter < 30 || calibrationCounter > 85)
		{
			set_motors(30,-30);
		}
		else
		{
			set_motors(-30,30);
		}
		calibrate_line_sensors(IR_EMITTERS_ON);
		delay_ms(25);
	}
	clear();
	set_motors(0,0);
}

void spin()
{
	set_motors(125,-125);
}

void checkReachedTurn()
{
	unsigned int sensors[5];
	while(1)
	{
		read_line(sensors, IR_EMITTERS_ON);
		if(sensors[2] >= 750)
		{
			clear();
			print("T Stop");
			break;
		}
	}
}

void turn(int turnTo)
{
	unsigned int sensors[5];
	clear();
	
	int notDone = 1;
	while(notDone)
	{
		if(turnTo == 0)
		{
			set_motors(75, 75);
			clear();
			print("ahead");
			delay_ms(100);
			set_motors(0,0);
		}
		else
		{
			if(turnTo == 2)
			{
				set_motors(75,-75);
			}
			else if(turnTo == 1)
			{
				set_motors(75, -75);
				print("1");
			}
			else
			{
				set_motors(-75, 75);
			}
		//	recieveOrderToBreak();
			delay_ms(150);
			read_line(sensors, IR_EMITTERS_ON);
			if(sensors[2] <= 250)
			{
				checkReachedTurn();
				if(turnTo == 2)
				{
					delay_ms(150);
					//recieveOrderToBreak();
					checkReachedTurn();
					set_motors(0,0);
				}
				else
				{
					set_motors(0,0);
				}
			}
			else
			{
				set_motors(0,0);
			}
		}
		notDone = 0;
	}
}

void followCharge(int *endPointReached)
{
	unsigned int sensors[5];
	int integral = 0;
	int last_proportional = 0;
	while(1)
	{
	//	recieveOrderToBreak();
		int object = detectObstacle();
		if(object != 0)
		{
			while(object){
				set_motors(0,0);
				play("G5");
				delay_ms(2500);
				object = detectObstacle();
			}
		}
		
		unsigned int position = read_line(sensors,IR_EMITTERS_ON); // read all IR_EMITTERS into sensors array each sensor has a value between 0 and 1000 the bigger the number the less reflective
		
		//up to and including line 153 is from the PID from pololu from page: https://www.pololu.com/docs/0J21/7.c
		// The "proportional" term should be 0 when we are on the line.
		int proportional = ((int)position) - 2000;
		
		// Compute the derivative (change) and integral (sum) of the
		// position.
		int derivative = proportional - last_proportional;
		integral += proportional;
		
		// Remember the last position.
		last_proportional = proportional;
		
		if(sensors[0] >= 500 && sensors[1] >= 500 && sensors[2] >= 500 && sensors[3] >= 500 && sensors[4] >= 500)
		{
			set_motors(50,-50);
			*endPointReached = 1;
			delay_ms(500);
			turn(1);
			delay_ms(600);
			break;
		}
		else if(sensors[1] >= 750 || sensors[4] >= 750)
		{
			set_motors(90,90);
		}
		else
		{
			//this part is from the pololu site on page: https://www.pololu.com/docs/0J21/7.c
			int power_difference = proportional/20 + integral/10000 + derivative*3/2;
			
			// Compute the actual motor settings.  We never set either motor
			// to a negative value.
			const int max = 90;
			if(power_difference > max)
			power_difference = max;
			if(power_difference < -max)
			power_difference = -max;
			
			if(power_difference < 0)
			set_motors((max+power_difference), max);
			else
			set_motors(max, (max-power_difference));
		}
	}
}

void followLine(int *typeOfCrossing, int inMaze) //0 if no crossing 99 if off of line
{
	unsigned int sensors[5];
	unsigned char noCrossing = 1;
	int integral = 0;
	int last_proportional = 0;
	int object;
	
	while(noCrossing)
	{
	//	recieveOrderToBreak();
		object = detectObstacle();
		if(object != 0)
		{
			while(object){
				set_motors(0,0);
				play("G5");
				delay_ms(2500);
				object = detectObstacle();
			}
		}
		clear();
		unsigned int position = read_line(sensors,IR_EMITTERS_ON); // read all IR_EMITTERS into sensors array each sensor has a value between 0 and 1000 the bigger the number the less reflective
		
		//up to and including line 153 is from the PID from pololu from page: https://www.pololu.com/docs/0J21/7.c
		// The "proportional" term should be 0 when we are on the line.
		int proportional = ((int)position) - 2000;
		
		// Compute the derivative (change) and integral (sum) of the
		// position.
		int derivative = proportional - last_proportional;
		integral += proportional;
		
		// Remember the last position.
		last_proportional = proportional;
		
		if(sensors[0] >= 750 && sensors[4] >= 750 && sensors[1] <= 250 && sensors[3] <= 250) //checks if T-split normal
		{
			*typeOfCrossing = 1;//T-normal
			if(sensors[2] >= 750 )
			{
				set_motors(75,75);
				continue;
			}
			else
			{
				print("T-norm");
				noCrossing = 0;//exits loop
				break;//security
			}
		}
		else if(sensors[0] >= 750 && sensors[2] >= 750 && sensors[4] <= 250 ) //checks if T-split on its side to the left
		{
			*typeOfCrossing = 2;//T-left
			if(sensors[1] >= 750 || sensors[2] <= 250 )
			{
				set_motors(75,75);
				continue;
			}
			else
			{
				print("T-left");
				noCrossing = 0;//exits loop
				break;//security
			}
		}
		else if(sensors[4] >= 750 && sensors[2] >= 750 && sensors[0] <= 250) //checks if T-split on its side to the right
		{
			*typeOfCrossing = 3;//T-right
			if(sensors[3] >= 750 || sensors[2] <= 250)
			{
				set_motors(75,75);
				continue;
			}
			else
			{
				print("T-right");
				noCrossing = 0;//exits loop
				break;//security
			}
		}
		else if(sensors[0] >= 250 && sensors[2] <= 50 && sensors[4] >= 250) // 01110
		{
			*typeOfCrossing = 7; // found end of maze
			print("end of");
			lcd_goto_xy(0,1);
			print("maze");
			set_motors(75,75);
			delay_ms(250);
			set_motors(0,0);
			delay_ms(1000);
			break;
			
		}
		else if(sensors[0] >= 750 && sensors[2] >= 750 && sensors[4] >= 750) //checks if at a cross-crossing 1*1*1
		{
			*typeOfCrossing = 4;//Cross
			if(sensors[1] >= 500 && sensors[3] >= 500)
			{
				set_motors(75,75);
				continue;
			}
			else
			{
				print("Cross");
				noCrossing = 0;//exits loop
				break;//security
			}
		}
		else if(sensors[0] >= 750 && sensors[2] <= 250 && sensors[4] <= 250 && inMaze == 0) //check if at corner to left 1*0*0
		{
			*typeOfCrossing = 5; //corner to left
			print("corner");
			lcd_goto_xy(0,1);
			print(" left");
			noCrossing = 0;
			break;//security
		}
		else if(sensors[0] >= 750 && sensors[2] <= 250 && sensors[4] <= 250 && inMaze == 1) //check if at corner to left and take it if in maze 1*0*0
		{
			turn(3);
		}
		else if(sensors[4] >= 750 && sensors[2] <= 250 && sensors[0] <= 250 && inMaze == 0) //check if at corner to right 0*0*1
		{
			*typeOfCrossing = 6; //corner to right
			print("corner");
			lcd_goto_xy(0,1);
			print("right");
			noCrossing = 0;
			break;//security
		}
		else if(sensors[4] >= 750 && sensors[2] <= 250 && sensors[0] <= 250 && inMaze == 0) //check if at corner to right and take it if in maze 0*0*1
		{
			turn(1);
		}
		else if(sensors[0] <= 50 && sensors[1] <= 50 && sensors[2] <= 50 && sensors[3] <= 50 && sensors[4] <= 50)//off the planeto 00000
		{
			*typeOfCrossing = 99;//not on any line
			print("of the");
			lcd_goto_xy(0,1);
			print("line");
			noCrossing = 0;//exits loop
			break;//security
		}
		else
		{
			*typeOfCrossing = 0; //no Crossing
			noCrossing = 1;
		}
		
		//this part is from the Pololu site on page: https://www.pololu.com/docs/0J21/7.c
		int power_difference = proportional/20 + integral/10000 + derivative*3/2;
		
		// Compute the actual motor settings.  We never set either motor
		// to a negative value.
		const int max = 90;
		if(power_difference > max)
		power_difference = max;
		if(power_difference < -max)
		power_difference = -max;
		
		if(power_difference < 0)
		set_motors((max+power_difference), max);
		else
		set_motors(max, (max-power_difference));
	}
	set_motors(0,0);
}
