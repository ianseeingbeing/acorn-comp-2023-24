#include "main.h"

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// left drivetrain
pros::Motor motor_left_a(17);
pros::Motor motor_left_b(16);
pros::Motor motor_left_c(15);

// right drivetrain
pros::Motor motor_right_a(20);
pros::Motor motor_right_b(19);
pros::Motor motor_right_c(18);

// launcher
pros::Motor motor_launch(1);
pros::Motor motor_launch_lift(1);

// intake
pros::Motor motor_intake(2);

// pistons
pros::ADIDigitalOut piston_flap_a(1);
// pros::ADIDigitalOut piston_flap_b(1);

void update_input();
// void tank_dirve(int, int);
void intake(int, int);
void launcher(int, int);
void flaps(int);