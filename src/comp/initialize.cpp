#include "graphics/managers/autonManager.hpp"
#include "graphics/managers/displayManager.hpp"
#include "graphics/graphics.hpp"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "robot/globals.hpp"
#include "robot/subsystems/controllers/flywheelController.hpp"
#include "robot/subsystems/managers/pneumaticManager.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
	autonInit();
	pneumaticInit();
	displayInit();
	graphicsInit();
	autonMenuInit();
	flywheelInit();

	blooper.set_value(false);
	flywheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	chassis.set_slew_min_power(70, 70);
	chassis.set_slew_distance(7, 7);
	chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
	chassis.set_pid_constants(&chassis.forward_drivePID, 0.5, 0, 5, 0);
	chassis.set_pid_constants(&chassis.backward_drivePID, 0.61, 0, 5, 0);
	chassis.set_pid_constants(&chassis.turnPID, 5.3, 0.003, 41, 15);
	chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);

	chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  	chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  	chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);

	pros::Task flywheelTask (asyncFlywheelController);
	pros::Task dispTask (asyncDisplay);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
