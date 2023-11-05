#include "main.h"

// =========== INITIALIZATION ========== //
pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::Motor motor_left_A(17, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor motor_left_B(16, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor motor_left_C(15, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor motor_right_A(20, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor motor_right_B(19, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor motor_right_C(18, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor motor_launch(1, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor motor_intake(2, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

// PISTONS
// pros::ADIDigitalOut piston_left_wing(1);
// pros::ADIDigitalOut piston_right_wing(1);

void update_input();
void tank_dirve(int leftInput, int rightInput);
void tank_drive_left_side(int input);
void tank_drive_right_side(int input);
void intake(int speed);
void launcher(int speed);
void operator_control();
// void piston_wings();

// ======================================= //

	int analogLeftY;
	int analogRightY;
	const int launcherSpeed = 120;
	const int intakeSpeed = 80;

	int buttonLauncher;

	int buttonIntakeIn;
	int buttonIntakeOut;
	int buttonIntakeOff;

	// int buttonPistonOut;
	// int buttonPistonIn;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
		
	pros::delay(20);
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

		update_inputs();
		tank_dirve(analogLeftY, analogRightY);
		launcher(launcherSpeed);
		intake(intakeSpeed);
	
		pros::delay(20);
	}
}

// Updates all the inputs for the processes
void update_inputs() {
	// ANALOG returns the speed not true or false.
	analogLeftY = controller.get_analog(ANALOG_LEFT_Y);
	analogRightY = controller.get_analog(ANALOG_RIGHT_Y);
	
	buttonLauncher = controller.get_digital(DIGITAL_A);

	buttonIntakeIn = controller.get_digital(DIGITAL_R1);
	buttonIntakeOut = controller.get_digital(DIGITAL_R2);
	buttonIntakeOff = controller.get_digital(DIGITAL_L1);

	// buttonPistonOut = controller.get_digital(DIGITAL_UP);
	// buttonPistonIn = controller.get_digital(DIGITAL_DOWN);
}

void tank_drive(int leftInput, int rightInput) {
	tank_drive_left_side(leftInput);
	tank_drive_right_side(rightInput);
}

void tank_drive_left_side(int input) {
	motor_left_A = input;
	motor_left_B = input;
	motor_left_C = -input;
}

void tank_drive_right_side(int input) {
	motor_right_A = -input;
	motor_right_B = input;
	motor_right_C = input;
}

// Launch Motor : type --> HOLD
void launcher(int speed) {
	if(buttonLauncher) {
		motor_launch = launcherSpeed;
		pros::delay(10);
	}
	else {
		motor_launch = 0;
		pros::delay(10);
	}
}

// Intake Motor : type --> TOGGLE
void intake(int speed) {
	if(buttonIntakeIn) {
		motor_intake = speed;
		pros::delay(10);
	}
	if(buttonIntakeOut) {
		motor_intake = -speed;
		pros::delay(10);
	}
	if(buttonIntakeOff) {
		motor_intake = 0;
		pros::delay(10);
	}
}

// void piston_wings() {
// 	if(buttonPistonOut) {
// 		piston_left_wing.set_value(HIGH);
// 		piston_right_wing.set_value(HIGH);
// 		pros::delay(100);
// 	}
// 	if(buttonPistonIn) {
// 		piston_left_wing.set_value(LOW);
// 		piston_right_wing.set_value(LOW);
// 		pros::delay(100);
// 	}
// }