/*
The code will output if the left sensor found a line and if the right sensor has found a line, this will most likely be done using pointers making them necessary for the input aswell.
Further more the code will output the thickness of the line and maybe sensors 6 and 7 for object detection
*/

#include <pololu/3pi.h>
#include <avr/pgmspace.h>

//the startup screen
const char startup_line1[] PROGMEM = "RobotRun";
const char startup_line2[] PROGMEM = "KARBONKEL";
const char startup_line3[] PROGMEM = " Floefs";
const char StartupMelody[] PROGMEM = "T180 O5 MS L8 EERERCE4 L4 GR<GR ";

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
	//calibration
	for(int calibrationCounter = 0; calibrationCounter < 113; calibrationCounter++)
	{
		print("Cali-");
		lcd_goto_xy(0,1);
		print("brating ");
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

void followLine(int *TypeOfCrossing, int TurnTo) //0 if no crossing otherwise 1 up to and including 4
{
	unsigned int sensors[5];
	unsigned char noCrossing = 1;
	
	while(noCrossing)
	{
		int delaycheck = 100;
		clear();
		read_line(sensors,IR_EMITTERS_ON); // read all IR_EMITTERS into sensors array each sensor has a value between 0 and 1000 the bigger the number the less reflective
		int leftSpeed = 150-((sensors[1]/10) * 0.8);
		int rightSpeed = 150-((sensors[3]/10) * 0.8);
		
		if(sensors[0] >= 750 && sensors[4] >= 750 && sensors[2] <= 250 && sensors[1] <= 250 && sensors[3] <= 250) //checks if T-split normal
		{
			*TypeOfCrossing = 1;//T-normal
			delay_ms(delaycheck);
			if(sensors[0] >= 500 || sensors [4] >= 500)
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
			*TypeOfCrossing = 2;//T-left
			delay_ms(delaycheck);
			if(sensors[0] >= 500 || sensors[2] >= 500)
			{
				continue;
			}
			else
			{
				print("T-left");
				noCrossing = 0;//exits loop
			}
		}
		else if(sensors[4] >= 750 && sensors[2] >= 750 && sensors[1] <= 750 && sensors[3] <= 750 && sensors[0] <= 250) //checks if T-split on its side to the right
		{
			*TypeOfCrossing = 3;//T-right
			if(sensors[4] >= 500 || sensors[2] >= 500)
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
			*TypeOfCrossing = 4;//Cross
			if(sensors[1] >= 800 && sensors[3] >= 800)
			{
				continue;
			}
			else
			{	
				print("Cross");
				noCrossing = 0;//exits loop
			}
		}
		else if(sensors[0] <= 250 && sensors[1] <= 250 && sensors[2] <= 250 && sensors[3] <= 250 && sensors[4] <= 250)//off the planeto
		{
			*TypeOfCrossing = 5;//not on any line
			print("off of");
			lcd_goto_xy(0,1);
			print("line");
			noCrossing = 0;//exits loop
		}
		else
		{
			*TypeOfCrossing = 0; //no Crossing
		}
		
		if(sensors[0] >= 750 && sensors[2] <= 250 && sensors[4] <= 250){ // Check if the left most bottom sensor is the only big turn sensor above line
			leftSpeed = -60;
			rightSpeed = 60;
		}
		else if(sensors[0] <= 250 && sensors[2] <= 250 && sensors[4] >= 750){ //Check if the right most bottom sensor is the only big turn sensor above line
			rightSpeed = -60;
			leftSpeed = 60;
		}
		
		set_motors(leftSpeed, rightSpeed);
	}
}
// This is the main function and will be left out when done
int main()
{
	int TypeOfCrossing = 0;
	int turnTo = 0;
	initRobot();
	
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
	delay(3300);
	
	followLine(&TypeOfCrossing, turnTo);
	
	while(1){
		set_motors(0,0);
	}
	
}
