#include "robotconfig.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::MotorGroup left_mg({-11,-12,13}, pros::MotorGears::blue); //* -11 front, -12 back, 13 5.5
pros::MotorGroup right_mg({-14,-16,17}, pros::MotorGears::blue); //* -14 front, -16 back, 17 5.5



