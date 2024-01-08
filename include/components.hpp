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
int update_launcher_input();
int update_launcher_lift_input();
int update_intake_input();

void launcher(int, int);
void launcher_lift(int, int);
void intake(int, int);