#pragma once
#include "main.h"

extern pros::Controller master;

//not strictly necessary
extern pros::Motor left_front;
extern pros::Motor left_back;
extern pros::Motor left_top; //5.5 W
extern pros::Motor right_front;
extern pros::Motor right_back;
extern pros::Motor right_top; //5.5 W

extern pros::MotorGroup left_mg;
extern pros::MotorGroup right_mg;

extern pros::Motor intake;

//not strictly necessary
extern pros::Motor lift_right;
extern pros::Motor lift_left;

extern pros::MotorGroup lift;

extern pros::adi::DigitalOut claw_clamp;
extern pros::adi::DigitalOut claw; // to lift up the claw thingy

extern pros::Imu imu;
