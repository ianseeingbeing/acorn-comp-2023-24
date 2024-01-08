#include "main.h"

const int LAUNCH_SPEED = -127;
const int LAUNCH_LIFT_SPEED = 80;
const int INTAKE_SPEED = 110;

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

std::string update_launcher_input() {
	if (master.get_digital(DIGITAL_A)) {
		return "on";
	}
	return "off";
}

std::string update_launcher_lift_input() {
	if (master.get_digital(DIGITAL_L1)) {
		return "up";
	}
	if (master.get_digital(DIGITAL_L2)) {
		return "down";
	}
	return "off";
}

std::string update_intake_input() {
	if (master.get_digital(DIGITAL_R1)) {
		return "on";
	} 
	else if (master.get_digital(DIGITAL_R2)) {
		return "reverse";
	}
	else if (master.get_digital(DIGITAL_X)) {
		return "off";
	}
	return "error";
}

// ===== LOGISTICS =====

// Launch Motor : type --> HOLD
void launcher(std::string state) {
	if (state == "on") {
		motor_launch = LAUNCH_SPEED;
	}
	else if (state == "off") {
		motor_launch = 0; 
	}
	pros::delay(10);
}

// Launcher Lift Motor : type --> HOLD
void launcher_lift(std::string state) {
	if (state == "up") {
		motor_launch_lift = LAUNCH_LIFT_SPEED;
	}
	else if (state == "down") {
		motor_launch_lift = -LAUNCH_LIFT_SPEED;
	}
	else if (state == "off") {
		motor_launch_lift = 0;
	}
	pros::delay(10);
}

// Intake Motor : type --> TOGGLE
void intake(std::string state) {
	if (state == "on") {
		motor_intake = -INTAKE_SPEED;
	}
	else if (state == "reverse") {
		motor_intake = INTAKE_SPEED;
	}
	else if (state == "off") {
		motor_intake = 0;
	}
	pros::delay(10);
}

void right_piston(std::string state) {
    if (state == "on") {
        piston_flap_a.set_value(HIGH);
    }
    else if (state == "off") {
        piston_flap_a.set_value(LOW);
    }
}

void left_piston(std::string state) {
    if (state == "on") {
        piston_flap_b.set_value(HIGH);
    }
    else if (state == "off") {
        piston_flap_b.set_value(LOW);
    }
}