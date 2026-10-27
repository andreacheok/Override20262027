#pragma once
#include "main.h"

extern pros::Controller master;

extern pros::MotorGroup left_mg;
extern pros::MotorGroup right_mg;

extern pros::Motor intake;

extern pros::MotorGroup lift;

extern pros::adi::DigitalOut claw_clamp;
extern pros::adi::DigitalOut claw; // to lift up the claw thingy

extern pros::Imu imu;
