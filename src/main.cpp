#include "main.h"
#include "autoselector.h"
#include "autoroutines.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::MotorGroup left_mg({1, -2, 3}, pros::MotorGears::blue);
pros::MotorGroup right_mg({-4, 5, -6}, pros::MotorGears::blue);

void initialize() {
	autoselector::init();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	switch (autoselector::get()) {
		case autoselector::Routine::red_left:     break;  // TODO: call your routine
		case autoselector::Routine::red_right:    break;
		case autoselector::Routine::blue_left:    break;
		case autoselector::Routine::blue_right:   break;
		case autoselector::Routine::skills:       break;
		case autoselector::Routine::quick_skills: break;
	}
}

void opcontrol() {
	while (true) {
		int forward = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		left_mg.move(forward + turn);
		right_mg.move(forward - turn);

		pros::delay(20);
	}
}