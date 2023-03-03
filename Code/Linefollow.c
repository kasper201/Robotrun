/*
The code will output if the left sensor found a line and if the right sensor has found a line, this will most likely be done using pointers making them necessary for the input aswell.
Further more the code will output the thickness of the line
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
	unsigned int sensors[5]; // the other 2 will be done differently and are currently out of the scope of this code
	
	pololu_3pi_init(2000);
	load_custom_characters();
	
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
			set_motors(50,-50);
		}
		else{
			set_motors(-50,50);
		}
		calibrate_line_sensors(IR_EMITTERS_ON);
		delay_ms(25);
	}
	set_motors(0,0);
	
	
	print("Press B");
	lcd_goto_xy(0,1);
	print("to start");
	while(!button_is_pressed(BUTTON_B))
	{
		//unsigned int PositionLine = read_line(sensors,IR_EMITTERS_ON); // read all IR_EMITTERS into a value between 0 and 4000.
		display_readings(sensors);
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

}

// This is the main function and will be left out when done
int main()
{
	initRobot();
	
	while(1){
		set_motors(0,0);
	}
	
}
