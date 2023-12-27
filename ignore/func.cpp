#include "main.h"

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// left drivetrain
pros::Motor motor_left_a(17, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor motor_left_b(16, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor motor_left_c(15, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);

// right drivetrain
pros::Motor motor_right_a(20, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor motor_right_b(19, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor motor_right_c(18, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);

// launcher
pros::Motor motor_launch(1, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor motor_launch_lift(1, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);

// intake
pros::Motor motor_intake(2, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);

// pistons
pros::ADIDigitalOut piston_flap_a(1);
// pros::ADIDigitalOut piston_flap_b(1);


// void tank_drive(int leftInput, int rightInput) {
//     motor_left_a = leftInput;
//     motor_left_b = leftInput;
//     motor_left_c = -leftInput;

// 	motor_right_a = -rightInput;
// 	motor_right_b = rightInput;
// 	motor_right_c = rightInput;
// }

// Launch Motor : type --> HOLD
void launcher(int speed, int button) {
	if(button) {
		motor_launch = speed;
		pros::delay(10);
	}
	else {
		motor_launch = 0;
		pros::delay(10);
	}
}

// Intake Motor : type --> TOGGLE
void intake(int speed, int button) {
	if(button == 1) {
		motor_intake = speed;
		pros::delay(10);
	}
	if(button == -1) {
		motor_intake = -speed;
		pros::delay(10);
	}
	if(button == 0) {
		motor_intake = 0;
		pros::delay(10);
	}
}

void flaps(int button) {
	if(button) {
		piston_flap_a.set_value(HIGH);
		pros::delay(100);
	}
	if(button) {
		piston_flap_a.set_value(LOW);
		pros::delay(100);
	}
}