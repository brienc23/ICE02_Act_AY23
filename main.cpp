/*********************************************************************************
SCY202 ICE 02 - Actuation: Task 1 Example Program
Name(s):  <UPDATE THIS WITH YOUR INFO>
Date:

Pseudo-Code:

	Inlcude mbed.h, Motor.h, platform/mbed_thread.h libraries
	Declare Serial port to PC
	Declare Motor object
	Declare potentiomater and joystick
	Define timers t and tlog for control and data logging
	Define all other variables

	Initialize Motor speed to zero
    	Ask user for control frequency, stored in freq
    	Check that the user entered correct frequency, if not, ask again
	Initialize t and tlog

	while(true)
		Read the potentiometer and convert to duty cyle
		Set the speed of the Motor based on duty cycle
		Print tlog and duty cycle 
		if (Joystick is pressed)
			Break while loop
		end-if
		Wait for 1/freq - t seconds
		reset timer t
	end-while
	Set the speed of Motor back to zero
**********************************************************************************/
 
/********************************"Pre-Processors" ********************************/
#include "mbed.h"                    // Include mbed library (Pin and C/C++ API)
#include "Motor.h"                   // Include Motor library (Motor API) if you didn't clone this project from the github repo
                                     // you will will have to File -> "Add Mbed Library to Active Project" from the following URL
                                     // https://os.mbed.com/users/simon/code/Motor/
#include "platform/mbed_thread.h"

Serial pc(USBTX, USBRX); // Declare serial port object to pc
Motor mot(p23, p24, p25);   // Declare motor object VERIFY THAT YOUR BOARD IS PLUGGED INTO THESE PINS, adjust one or the other
AnalogIn pot(p19);   // Declare Analog input to read in the potentionmer value from the App board
DigitalIn joy(p14);   // Declare a Digital Input to read in the joystick center press 

Timer t;        //Timer to regulate control sequence
Timer tlog;     //Timer to log data
float dt;       //A variable to regulate the time

// Variables
float ValueOfPotent  = 0;
float ValueOfJoy  = 0;
float dutycycle = 0;
float freq = 0;   //Default frequency, to be changed by user
 
/************************** Beginning of Main Program *****************************/
int main()
{
    mot.speed(0.0);//Set motor speed to zero (initialize motor)
    
    while(freq <1 || freq >100){
        pc.printf("\nEnter a speed in Hz that you would like to control the motor speed [1-100 Hz]: "); // Ask user for control frequency
        pc.scanf("%f", &freq);  // read in a value and store in the freq variable
        pc.printf("%0.2f", freq); // print it back to the user
        
        if (freq <1 || freq >100){  //Check that the user entered correct frequency, if not, ask again
            pc.printf("\n\t%f is an invalid value, please enter a positive frequency in Hz less than 100 cycles/sec.\n", freq);
        }
    }
    // Once we have a correct frequency
    float Ts = 1.0/freq; //Set period between executions (inverse of frequency)
    // Provide instructions to user... like how to stop the program
    pc.printf("\nStarting Motor running at %0.2f Hz. \nYou can stop the motor by pressing down on the joystick button.\n\n", freq);
    thread_sleep_for(2000);     //Allow sometime in between (a time buffer)
    t.start();   //Initialize timers
    tlog.start();
    
    while(1) {
         
        ValueOfPotent = pot.read();  // Read the current potentiometer value
        dutycycle = 2.0*ValueOfPotent-1; // Convert the pot value to duty cycle [-1, 1]
        mot.speed(dutycycle); // Set the speed of the motor based on duty cycle
        
        // Print the time and dc values to TeraTerm, use tlog.read() to read the time
        pc.printf("%0.5f, %0.3f\n", tlog.read(), dutycycle);

        ValueOfJoy = joy.read();  //Check if the joystick is being pressed
        
        if (ValueOfJoy == 1) { break;} // Break from the while loop if the joystick is pressed down
        
        //**************The following piece of code regulates the frequency of execution
        //Should not be changed
        dt = Ts-t.read();
        t.stop();
        t.reset();
        if (dt > 0) {
            thread_sleep_for(1000*dt); 		//wait for delta t in milliseconds
        } 
        t.start();
        //*************End of piece of code that regulates frequency
    }

    pc.printf("\n\nShutting Motor Down, reset mbed to restart program,\n");
    mot.speed(0.0); //Set the speed of the motor back to zero
}
/***************************** End of Main Program ******************************/