/*
The code will output if the left sensor found a line and if the right sensor has found a line, this will most likely be done using pointers making them necessary for the input aswell.
Further more the code will output the thickness of the line and maybe sensors 6 and 7 for object detection
*/

#include <pololu/3pi.h>
#include <avr/pgmspace.h>

//the startup screen
const char startup_line1[] PROGMEM = "RobotRun";
const char startup_line2[] PROGMEM = "KARBONKE";
const char startup_line3[] PROGMEM = " Floefs";
const char StartupMelody[] PROGMEM = "T180 O5 MS L8 EERERCE4 L4 GR<GR ";

void startDrivingAfter()
{
	while(!button_is_pressed(BUTTON_B))
	{
		print("Press B");
		lcd_goto_xy(0,1);
		print("to start");
	}
	while(button_is_pressed(BUTTON_B)){
		clear();
		print("Let go");
		lcd_goto_xy(0,1);
		print("to start");
		delay_ms(1000);
	}
	
	clear();
	print("GO!!");
	play("L4 MSD.D.D R8 ! O5 G2. R8" );
	delay(3200);
}

void initRobot()
{
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
	clear();
	wait_for_button_release(BUTTON_B);
	play("T 180 MLCEG"); //play sound to display start of calibration
	delay_ms(500);
	//calibration
	for(int calibrationCounter = 0; calibrationCounter < 113; calibrationCounter++)
	{
		print("Calib-");
		lcd_goto_xy(0,1);
		print("rating  ");
		if(calibrationCounter < 30 || calibrationCounter > 85){
			set_motors(30,-30);
		}
		else{
			set_motors(-30,30);
		}
		calibrate_line_sensors(IR_EMITTERS_ON);
		delay_ms(25);
	}
	clear();
	set_motors(0,0);
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
	
	if(turnTo == 0)
	{
	}
	else
	{
		if(turnTo < 3)
		{
			set_motors(50, -40);
		}
		else
		{
			set_motors(-40, 50);
		}
		delay_ms(100);
		read_line(sensors, IR_EMITTERS_ON);
		if(sensors[2] <= 250)
		{
			checkReachedTurn();
			if(turnTo == 2)
			{
				delay_ms(150);
				checkReachedTurn();
				set_motors(0,0);
			}
			else
			{
				set_motors(0,0);
			}
		}
	}
}

void followLine(int *typeOfCrossing, int *turnTo) //0 if no crossing 99 if off of line
{
	unsigned int sensors[5];
	unsigned char noCrossing = 1;
	int integral = 0;
	int last_proportional = 0;
	
	if(*typeOfCrossing != 0)
	{
		turn(*turnTo);
		*typeOfCrossing = 0;
		*turnTo = 0;
	}
	else
	{
		*typeOfCrossing = 0;
	}
	
	while(noCrossing)
	{
		clear();
		unsigned int position = read_line(sensors,IR_EMITTERS_ON); // read all IR_EMITTERS into sensors array each sensor has a value between 0 and 1000 the bigger the number the less reflective
		
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
				continue;
			}
			else
			{
				print("T-norm");
				noCrossing = 0;//exits loop
			}
		}
		else if(sensors[0] >= 750 && sensors[2] >= 750 && sensors[4] <= 250 ) //checks if T-split on its side to the left
		{
			*typeOfCrossing = 2;//T-left
			if(sensors[1] >= 750 || sensors[2] <= 250 )
			{
				continue;
			}
			else
			{
				print("T-left");
				noCrossing = 0;//exits loop
			}
		}
		else if(sensors[3] >= 750 && sensors[2] >= 750 && sensors[0] <= 250) //checks if T-split on its side to the right
		{
			*typeOfCrossing = 3;//T-right
			if(sensors[3] >= 750 || sensors[2] <= 250)
			{
				continue;
			}
			else
			{
				print("T-right");
				noCrossing = 0;//exits loop
			}
		}
		else if(sensors[0] >= 750 && sensors[2] >= 750 && sensors[4] >= 750) //checks if at a cross-crossing
		{
			*typeOfCrossing = 4;//Cross
			if(sensors[1] >= 900 && sensors[3] >= 900)
			{
				continue;
			}
			else
			{
				print("Cross");
				noCrossing = 0;//exits loop
			}
		}
		else if(sensors[0] <= 50 && sensors[1] <= 50 && sensors[2] <= 50 && sensors[3] <= 50 && sensors[4] <= 50)//off the planeto
		{
			*typeOfCrossing = 99;//not on any line
			print("off of");
			lcd_goto_xy(0,1);
			print("line");
			noCrossing = 0;//exits loop
		}
		else
		{
			*typeOfCrossing = 0; //no Crossing
			noCrossing = 1;
		}
		
		// m1 - m2.  If this is a positive number the robot will turn
		// to the right.  If it is a negative number, the robot will
		// turn to the left, and the magnitude of the number determines
		// the sharpness of the turn.
		int power_difference = proportional/20 + integral/10000 + derivative*3/2;
		
		// Compute the actual motor settings.  We never set either motor
		// to a negative value.
		const int max = 60;
		if(power_difference > max)
		power_difference = max;
		if(power_difference < -max)
		power_difference = -max;
		
		if(power_difference < 0)
		set_motors(1.5*(max+power_difference), 1.5*max);
		else
		set_motors(1.5*max, 1.5*(max-power_difference));
	}
}
// This is the main function and will be left out when done
int main()
{
	int typeOfCrossing = 0;
	int turnTo = 2;
	initRobot();
	serial_set_baud_rate(115200);
	
	startDrivingAfter();
	
	while(1)
	{
		//followLine(&typeOfCrossing, &turnTo);
		turn(turnTo);
		set_motors(0,0);
		wait_for_button_press(BUTTON_B);
		wait_for_button_release(BUTTON_B);
	}
	
}
