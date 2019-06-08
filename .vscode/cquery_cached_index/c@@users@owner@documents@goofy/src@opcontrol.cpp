#include "main.h"

void
tray_control(void*) {
	pros::Controller master(CONTROLLER_MASTER);
	pros::Task tray_t(tray_pid);
	bool b_toggle = false;
	while (true) {
		if (master.get_digital(DIGITAL_Y)) {
			b_toggle = !b_toggle;

			if (b_toggle) {
				for(int i=0;i<1700;i=i+3) {
					set_tray_pid(i);
					pros::delay(5);
				}
			} else {
				set_tray_pid(0);
			}

			while (master.get_digital(DIGITAL_Y)) {
				pros::delay(1);
			}
		}

		pros::delay(20);
	}
}

//Make the right paddle a shift key, making everything into a descore position.
/*
void
arm_control(void*) {
	pros::Controller master(CONTROLLER_MASTER);
	pros::Task arm_t(arm_pid);
	static int HIGH_POLE = 2450, LOW_POLE = 1000, DOWN = 0;
	int b_toggle = DOWN;
	while (true) {
		if (master.get_digital(DIGITAL_R1)) {
			if (b_toggle == DOWN || b_toggle == LOW_POLE) {
				b_toggle = HIGH_POLE;
			} else {
				b_toggle = DOWN;
			}
			set_arm_pid(b_toggle);
			while (master.get_digital(DIGITAL_R1)) {
				pros::delay(1);
			}
		}
		if (master.get_digital(DIGITAL_R2)) {
			if (b_toggle == DOWN || b_toggle == HIGH_POLE) {
				b_toggle = LOW_POLE;
			} else {
				b_toggle = DOWN;
			}
			set_arm_pid(b_toggle);
			while (master.get_digital(DIGITAL_R2)) {
				pros::delay(1);
			}
		}
		pros::delay(20);
	}
}
*/

void
arm_control(void*) {
	pros::Controller master(CONTROLLER_MASTER);
	pros::Task arm_t(arm_pid);
	bool was_pid;
	while (true) {
		if (master.get_digital(DIGITAL_B)) {
			was_pid = true;
			arm_t.resume();
			set_arm_pid(2300);
		} else if (master.get_digital(DIGITAL_DOWN)) {
			was_pid = true;
			arm_t.resume();
			set_arm_pid(1800);
		} else {
			if (master.get_digital(DIGITAL_R1)||master.get_digital(DIGITAL_R2)) {
				was_pid = false;
				set_arm((master.get_digital(DIGITAL_R1)-master.get_digital(DIGITAL_R2))*127);
			} else {
				if (!was_pid) {
					set_arm(0);
				}
			}
		}

		if (!was_pid) {
			arm_t.suspend();
		}

		pros::delay(20);
	}
}

void
opcontrol() {
	pros::Controller master(CONTROLLER_MASTER);
	pros::Task tray_control_t(tray_control);

	pros::Task t(arm_control);
	while (true) {
		set_tank(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));

		//set_arm((master.get_digital(DIGITAL_R1)-master.get_digital(DIGITAL_R2))*127);

		if (master.get_digital(DIGITAL_L1)) {
			set_rollers(127);
		} else if (master.get_digital(DIGITAL_L2)) {
			set_rollers(-127);
		} else if (master.get_digital(DIGITAL_RIGHT)) {
			set_rollers(60);
		} else {
			set_rollers(0);
		}

		pros::delay(20);
	}
}
