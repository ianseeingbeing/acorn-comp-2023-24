#include "main.h"

// launcher
extern pros::Motor motor_launch;
extern pros::Motor motor_launch_lift;

// intake
extern pros::Motor motor_intake;

// pistons
extern pros::ADIDigitalOut piston_flap_a;
extern pros::ADIDigitalOut piston_flap_b;

void update_drivetrain_state(std::string&);
void update_flaps_state(std::string&);
std::string update_launcher_input();
std::string update_launcher_lift_input();
std::string update_intake_input();

void launcher(std::string state);
void launcher_lift(std::string state);
void intake(std::string state);

void right_piston(std::string state);
void left_piston(std::string state);