#include "main.h"

pros::Motor left_back (20, MOTOR_GEARSET_18);
pros::Motor left_mid (18, MOTOR_GEARSET_18);
pros::Motor right_back (19, MOTOR_GEARSET_18, true);
pros::Motor right_mid (17, MOTOR_GEARSET_18, true);

pros::Motor tray(16, MOTOR_GEARSET_36, true);
pros::Motor arm(3, MOTOR_GEARSET_18);
pros::Motor left_roller(1, MOTOR_GEARSET_18, true);
pros::Motor right_roller(2, MOTOR_GEARSET_18);

//Math
int
sgn(int input) {
  if (input>0)
    return 1;
  else if (input < 0)
    return -1;
  return 0;
}
int
clipnum(int input, int clip) {
  if (input > clip)
    return clip;
  else if (input < clip)
    return -clip;
  return input;
}

void
reset() {
  left_roller.set_brake_mode(MOTOR_BRAKE_HOLD);
  right_roller.set_brake_mode(MOTOR_BRAKE_HOLD);
  arm.set_brake_mode(MOTOR_BRAKE_HOLD);
  arm.set_zero_position(0);
  tray.set_zero_position(0);
}

//Set motors
void
set_tank(int input_l, int input_r) {
  left_mid.move(input_l);
  left_back.move(input_l);
  right_mid.move(input_r);
  right_back.move(input_r);
}

void
set_tray(int input) {
  tray.move(input);
}

void
set_arm(int input) {
  arm.move(input);
}

void
set_rollers(int input) {
  left_roller.move(input);
  right_roller.move(input);
}

//PID
int t_target;
void
set_tray_pid(int input) {
  t_target = input;
}
void
tray_pid(void*) {
	while (true) {
		set_tray((t_target-tray.get_position())*0.5);
		pros::delay(20);
	}
}

int a_target;
void
set_arm_pid(int input) {
  a_target = input;
}
void
arm_pid(void*) {
  while (true) {
    set_arm((a_target-arm.get_position())*0.5);
    pros::delay(20);
  }
}
