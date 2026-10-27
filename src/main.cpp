#include "main.h"
#include "auto/autoselector.hpp"
#include "auto/autoroutines.hpp"
#include "robotconfig.h"


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
	left_mg.set_brake_mode_all(pros::MotorBrake::brake);
	right_mg.set_brake_mode_all(pros::MotorBrake::brake);

	while (true) {
		float throttle = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);   // Axis3
		if (throttle < 5 && throttle > -5) {
			throttle = 0;
		}
		throttle = throttle / 1.27f;

		float turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);      // Axis1
		if (turn < 5 && turn > -5) {
			turn = 0;
		}
		turn = turn / 1.27f;

		throttle = pow(throttle, 3) / 10000;
		turn = pow(turn, 3) / 10000;

		float leftpow = throttle - turn;
		float rightpow = throttle + turn;

		if (leftpow == 0) {
			left_mg.brake();
		}
		if (rightpow == 0) {
			right_mg.brake();
		}

		// VEXcode used volts (leftpow * 0.12); PROS uses millivolts, so multiply by 120 instead
		left_mg.move_voltage(leftpow * 120);
		right_mg.move_voltage(rightpow * 120);

		pros::delay(20);
	}
}
