#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 120; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
														 // If this is 127 and the robot tries to heading correct, it's only correcting by
														 // making one side slower.  When this is 87%, it's correcting by making one side
														 // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 100;
const int SWING_SPEED = 100;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
	chassis.set_slew_min_power(80, 80);
	chassis.set_slew_distance(7, 7);
	chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
	chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
	chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
	chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
	chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
	chassis.set_slew_min_power(80, 80);
	chassis.set_slew_distance(7, 7);
	chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
	chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
	chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
	chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
	chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
	chassis.set_slew_min_power(80, 80);
	chassis.set_slew_distance(7, 7);
	chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
	chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
	chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
	chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
	chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

// exit conditions
void modified_exit_condition() {
	chassis.set_exit_condition(chassis.turn_exit, 1, 3, 5, 7, 5, 50);
	chassis.set_exit_condition(chassis.swing_exit, 1, 3, 5, 7, 5, 50);
	chassis.set_exit_condition(chassis.drive_exit, 1, 50, 5, 75, 5, 50);
}




///
// Drive Example
///
void drive_example() {
	// The first parameter is target inches
	// The second parameter is max speed the robot will drive at
	// The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
	// for slew, only enable it when the drive distance is greater then the slew distance + a few inches


	chassis.set_drive_pid(24, DRIVE_SPEED, true);
	chassis.wait_drive();

	chassis.set_drive_pid(-12, DRIVE_SPEED);
	chassis.wait_drive();

	chassis.set_drive_pid(-12, DRIVE_SPEED);
	chassis.wait_drive();
}



///
// Turn Example
///
void turn_example() {
	// The first parameter is target degrees
	// The second parameter is max speed the robot will drive at


	chassis.set_turn_pid(90, TURN_SPEED);
	chassis.wait_drive();

	chassis.set_turn_pid(45, TURN_SPEED);
	chassis.wait_drive();

	chassis.set_turn_pid(0, TURN_SPEED);
	chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
	chassis.set_drive_pid(24, DRIVE_SPEED, true);
	chassis.wait_drive();

	chassis.set_turn_pid(45, TURN_SPEED);
	chassis.wait_drive();

	chassis.set_turn_pid(-45, TURN_SPEED);
	chassis.wait_drive();

	chassis.set_turn_pid(0, TURN_SPEED);
	chassis.wait_drive();

	chassis.set_drive_pid(-24, DRIVE_SPEED, true);
	chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
	// wait_until will wait until the robot gets to a desired position


	// When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
	chassis.set_drive_pid(24, DRIVE_SPEED, true);
	chassis.wait_until(6);
	chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
	chassis.wait_drive();

	chassis.set_turn_pid(45, TURN_SPEED);
	chassis.wait_drive();

	chassis.set_turn_pid(-45, TURN_SPEED);
	chassis.wait_drive();

	chassis.set_turn_pid(0, TURN_SPEED);
	chassis.wait_drive();

	// When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
	chassis.set_drive_pid(-24, DRIVE_SPEED, true);
	chassis.wait_until(-6);
	chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
	chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
	// The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
	// The second parameter is target degrees
	// The third parameter is speed of the moving side of the drive


	chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
	chassis.wait_drive();

	chassis.set_drive_pid(24, DRIVE_SPEED, true);
	chassis.wait_until(12);

	chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
	chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
	chassis.set_drive_pid(24, DRIVE_SPEED, true);
	chassis.wait_drive();

	chassis.set_turn_pid(45, TURN_SPEED);
	chassis.wait_drive();

	chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
	chassis.wait_drive();

	chassis.set_turn_pid(0, TURN_SPEED);
	chassis.wait_drive();

	chassis.set_drive_pid(-24, DRIVE_SPEED, true);
	chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
	for (int i=0; i<attempts-1; i++) {
		// Attempt to drive backwards
		printf("i - %i", i);
		chassis.set_drive_pid(-12, 127);
		chassis.wait_drive();

		// If failsafed...
		if (chassis.interfered) {
			chassis.reset_drive_sensor();
			chassis.set_drive_pid(-2, 20);
			pros::delay(1000);
		}
		// If robot successfully drove back, return
		else {
			return;
		}
	}
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
	 tug(3);
	 return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .

void auton() {
	if (auton_switch.get_value_calibrated() < 50) { 
		auton_near_side(); // tiwst tward back
	}
	else if (auton_switch.get_value_calibrated() > 4045) {
		auton_far_side(); // twist tward intake
	}
	else {
		auton_skills(); // put in center
	}
}

// simplify auton
void drive(int pid) {
	chassis.set_drive_pid(pid, DRIVE_SPEED);
	chassis.wait_drive();
}

void turn(int deg) {
	chassis.set_turn_pid(deg, TURN_SPEED);
	chassis.wait_drive();
}

void swing(std::string direction, int degree) {
	if (direction == "left") {
		chassis.set_swing_pid(ez::LEFT_SWING, degree, TURN_SPEED);
	}
	else if (direction == "right") {
		chassis.set_swing_pid(ez::RIGHT_SWING, degree, TURN_SPEED);
	}
	chassis.wait_drive();
}

// bot is opposite where team stands
void auton_far_side() { // next to goal
    // grab ball
    intake("on");
    drive(280);

    // push colored-preload and intake into goal
    drive(-1100);
    turn(135);
    drive(650);
	wings("high");
    turn(95);
	intake("off");
    drive(560);
    drive(-680);
	wings("low");

	// grap and release solo right ball


    // grab top-center ball
    turn(45);
    intake("on");
    drive(1695);
    swing("right", 0);
	turn(180);
	wings("high");

    // push center and top-right ball into goal 
    intake("off");
    drive(1000);
	wings("low");
    drive(-400);
}

// bot is next to where team stands
void auton_near_side() {
    // push colored-preload into goal
    turn(-30);
    drive(-1075);
    turn(0);
    drive(350);

    // collect bar ball
    turn(-45);
    drive(620);
    turn(-90);
    intake("on");
    drive(1050);
    turn(90);

    drive(875);
    turn(135);
    drive(925);
    turn(180);
    intake("off");
    drive(310);
    drive(-400);

    // touch bar
    turn(135);
    drive(-700);
    turn(90);
    drive(-1000);
}

void auton_skills() {
	// push ball into goal
	turn(-30);
	drive(-1075);
	turn(0);
	drive(350);
	turn(-291);
    
    // match loading
    launcher_lift("up");
	wings("high");
	motor_launch = 127;
	
    pros::delay(38000); // 38s
    launcher_lift("down");
	wings("low");
	motor_launch = 0;
   
    pros::delay(1000);
    launcher_lift("off");

    //get to center field
    drive(-950);
    turn(-0);
	drive(-800);

    // push near side over
    turn(75);
	drive(-600);
    drive(100);
    turn(90);
    drive(650);
    turn(-90);
    drive(2100);

    // push far side into goal
    drive(-300);
    wings("high");
    drive(1000);
    wings("low");
    drive(-600);

    // get stuff on the side
    // turn(0);
    // wings("high");
    // drive(1000);
    // turn(-45);
    // drive(800);
    // swing("right", -180);
    // drive(700);

}

void test() {
	
}