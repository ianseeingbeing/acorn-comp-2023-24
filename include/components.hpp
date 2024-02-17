#include "main.h"

extern const std::vector<int> leftChassisMotors;
extern const std::vector<int> rightChassisMotors;

// chassis
extern Drive chassis;

// launcher
extern pros::Motor motor_launch;
extern pros::Motor motor_launch_lift;

// intake
extern pros::Motor motor_intake;

// pistons
extern pros::ADIDigitalOut piston_flaps;

// potentiometer
extern pros::ADIAnalogIn auton_switch;