#include "main.h"

// launcher
pros::Motor motor_launch(7, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor motor_launch_lift(6, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_DEGREES);

// intake
pros::Motor motor_intake(4, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_DEGREES);

// pistons
pros::ADIDigitalOut piston_flap_a(1);
pros::ADIDigitalOut piston_flap_b(2);

void update_drivetrain_state(std::string &drive) {
	if (master.get_digital(DIGITAL_DOWN)) {
    pros::delay(500);
		if ("tank" == drive) {
      drive = "splitArcade";
    } 
    else {
      drive = "tank";
    }
		pros::delay(500);	
  }
  if (drive == "tank") {
    chassis.tank();
  }
  if (drive == "splitArcade") {
    chassis.arcade_flipped(ez::SPLIT);
  }
}

void update_flaps_state(std::string &state) {
	if (master.get_digital(DIGITAL_UP)) {
    pros::delay(400);
    if (state == "up") {
      state = "down";
      piston_flap_a.set_value(HIGH);
      piston_flap_b.set_value(HIGH);
    }
    else {
      state = "up";
      piston_flap_a.set_value(LOW);
      piston_flap_b.set_value(LOW);
    }
    pros::delay(100); 
	}
}

int update_launcher_input() {
	if (master.get_digital(DIGITAL_A)) {
		return 1; // on
	}
	return 0; // off
}

int update_launcher_lift_input() {
	if (master.get_digital(DIGITAL_L1)) {
		return 1; // up
	}
	if (master.get_digital(DIGITAL_L2)) {
		return 2; // down
	}
	return 0; // off
}

int update_intake_input() {
	if (master.get_digital(DIGITAL_R1)) {
		return 1; // consume
	} 
	else if (master.get_digital(DIGITAL_R2)) {
		return 2; // eject
	}
	else if (master.get_digital(DIGITAL_X)) {
		return 0; // off
	}
	return -1; // error
}

// ===== LOGISTICS =====

// Launch Motor : type --> HOLD
void launcher(int speed, int state) {
	if (state == 1) {
		motor_launch = speed; //
	}
	if (state != 1) {
		motor_launch = 0; //
	}
	pros::delay(10);
}

// Launcher Lift Motor : type --> HOLD
void launcher_lift(int speed, int state) {
	if (state == 1) { // up
		motor_launch_lift = speed;
	}
	if (state == 2) { // down
		motor_launch_lift = -speed;
	}
	if (state < 1) {
		motor_launch_lift = 0;
	}
	pros::delay(10);
}

// Intake Motor : type --> TOGGLE
void intake(int speed, int state) {
	if (state == 1) {
		motor_intake = -speed; // in
		pros::delay(10);
	}
	if (state == 2) {
		motor_intake = speed; // out
		pros::delay(10);
	}
	if (state == 0) {
		motor_intake = 0;
		pros::delay(10);
	}
	pros::delay(10);
}