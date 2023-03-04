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
	unsigned int counter;
	unsigned int sensors[7]; // sensors 6 and 7 are not used in this code but will probably be returned
	
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
	for(int calibrationCounter=0; calibrationCounter<113; calibrationCounter++)
	{
		if(calibrationCounter < 30 || calibrationCounter > 85){
			set_motors(30,-30);
		}
		else{
			set_motors(-30,30);
		}
		calibrate_line_sensors(IR_EMITTERS_ON);
		delay_ms(25);
	}
	set_motors(0,0);
}

void followLine(int *TypeOfCrossing) 
{
	int leftCorner = 0;
	int rightCorner = 0;
	unsigned char noCrossing = 1;
	
	print("Press B");
	lcd_goto_xy(0,1);
	print("to start");
	while(!button_is_pressed(BUTTON_B))
	{
		
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
	delay(3500);
	
	while(noCrossing)
	{
		read_line(sensors,IR_EMITTERS_ON); // read all IR_EMITTERS into sensors array each sensor has a value between 0 and 1000 the bigger the number the less reflective
		int leftSpeed = 200-(sensors[1]/10);
		int rightSpeed = 200-(sensors[3]/10);
		
		if(sensors[0] >= 750 && sensors[4] >= 750 && sensors[2] <= 250){ //checks if T-split normal
			noCrossing = 0;
		}
		else if(sensors[0] >= 750 && sensors[2] >= 750 && sensors[4] <= 250){ //checks if T-split on its side to the left
			noCrossing = 0;
		}
		else if(sensors[4] >= 750 && sensors[2] >= 750 && sensor[0] <= 250){ //checks if T-split on its side to the right
			noCrossing = 0;
		}
		else if(sensors[0] >= 750 && sensors[2] >= 750 && sensors[4] >= 750){ //checks if at a cross-crossing
			noCrossing = 0;
		}
		
		else if(sensors[0] >= 750 && sensors[2] <= 250 && sensors[4] <= 250){ // Check if the left msot bottom sensor is the only big turn sensor above line
			leftSpeed = -20;
		}
		else if(sensors[0] <= 250 && sensors[2] <= 250 && sensors[4] >= 750 &&){ //Check if the right most bottom sensor is the only big turn sensor above line
			rightSpeed = -20;
		}
		
		set_motors(leftSpeed, rightSpeed);
	}
}
// This is the main function and will be left out when done
int main()
{
	initRobot();
	followLine();
	
	while(1){
		set_motors(0,0);
	}
	
}
