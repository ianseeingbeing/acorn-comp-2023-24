#include "main.h"

const int LAUNCH_SPEED = 120;
const int LAUNCH_LIFT_SPEED = 44;
const int INTAKE_SPEED = 80;

int update_launcher_input();
int update_launcher_lift_input();
int update_intake_input();
int update_flap_input();

void tank_drive(int, int);
void launcher(int, int);
void launcher_lift(int, int);
void intake(int, int);
void flaps(int);

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// left drivetrain
pros::Motor motor_left_a(10, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor motor_left_b(9, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor motor_left_c(8, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);

// right drivetrain
pros::Motor motor_right_a(1, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor motor_right_b(2, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor motor_right_c(3, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);

// launcher
pros::Motor motor_launch(5, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor motor_launch_lift(6, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);

// intake
pros::Motor motor_intake(20, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);

// pistons
pros::ADIDigitalOut piston_flap_a(1);
// pros::ADIDigitalOut piston_flap_b(1);


/*
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	while (true) {

		tank_drive(controller.get_analog(ANALOG_LEFT_Y), controller.get_analog(ANALOG_RIGHT_Y));	
		launcher(LAUNCH_SPEED, update_launcher_input());
		launcher_lift(LAUNCH_LIFT_SPEED, update_launcher_lift_input());
		intake(INTAKE_SPEED, update_intake_input());
		flaps(update_flap_input());
	
	}
}

int update_launcher_input() {
	if (controller.get_digital(DIGITAL_A)) {
		return 1; // on
	}
	return 0; // off
}

int update_launcher_lift_input() {
	if (controller.get_digital(DIGITAL_Y)) {
		return 1; // up
	}
	if (controller.get_digital(DIGITAL_B)) {
		return 2; // down
	}
	return 0; // off
}

int update_intake_input() {
	if (controller.get_digital(DIGITAL_R1)) {
		return 1; // consume
	} 
	else if (controller.get_digital(DIGITAL_R2)) {
		return 2; // eject
	}
	else if (controller.get_digital(DIGITAL_L1)) {
		return 0; // off
	}
	return -1; // error
}

int update_flap_input() {
	if (controller.get_digital(DIGITAL_UP)) {
		return 1; // up
	}
	if (controller.get_digital(DIGITAL_DOWN)) {
		return 2; // down
	}
	return 0; // off
}

void tank_drive(int leftInput, int rightInput) {

    motor_left_a = leftInput;
    motor_left_b = leftInput;
    motor_left_c = -leftInput;

	motor_right_a = -rightInput;
	motor_right_b = -rightInput;
	motor_right_c = rightInput;
}

// Launch Motor : type --> HOLD
void launcher(int speed, int state) {
	if (state) {
		motor_launch = speed;
		pros::delay(10);
	}
	else {
		motor_launch = 0;
		pros::delay(10);
	}
}

// Launcher Lift Motor : type --> TOGGLE
void launcher_lift(int speed, int state) {
	if (state == 1) {
		motor_launch_lift = speed;
	}
	if (state == 2) {
		motor_launch_lift = -speed;
	}
	motor_launch_lift = 0;
	pros::delay(10);
}

// Intake Motor : type --> TOGGLE
void intake(int speed, int state) {
	if (state == 1) {
		motor_intake = speed;
		pros::delay(10);
	}
	if (state == 2) {
		motor_intake = -speed;
		pros::delay(10);
	}
	if (state == 0) {
		motor_intake = 0;
		pros::delay(10);
	}
}

// Flap Pistons : type --> TOGGLE
void flaps(int state) {
	if (state) {
		piston_flap_a.set_value(HIGH);
		pros::delay(100);
	}
	if (state) {
		piston_flap_a.set_value(LOW);
		pros::delay(100);
	}
}