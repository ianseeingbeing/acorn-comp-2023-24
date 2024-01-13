#pragma once

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;

void drive_example();
void turn_example();
void drive_and_turn();
void wait_until_change_speed();
void swing_example();
void combining_movements();
void interfered_example();

void default_constants();
void one_mogo_constants();
void two_mogo_constants();

// custom 
void drive(int);
void turn(int);
void auton_team_goal();
void auton_opp_goal();
void auton_opp_goal_side_2();
void skills();