#include "main.h"

void update_drivetrain_state(std::string&);
void update_wings_state(std::string&);

std::string update_launcher_input();
std::string update_launcher_lift_input();
std::string update_intake_input();

void launcher(std::string state);
void launcher_lift(std::string state);
void intake(std::string state);

void wings(std::string state);