#include "pros/rtos.hpp"
#include "robot/globals.hpp"
#include "graphics/managers/autonManager.hpp"
#include "robot/subsystems/controllers/flywheelController.hpp"
#include "robot/subsystems/managers/pneumaticManager.hpp"
#include <algorithm>

void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

void featherDisks(){
    intake.move_relative(-330, 600);
    pros::delay(950);
    intake.move_relative(-500, 600);
    pros::delay(450);
   // compression.set_value(true);
    pros::delay(500);
    intake.move_voltage(-12000);
    pros::delay(750);
    //compression.set_value(false);
}

void featherDisks2(){
    intake.move_relative(-330, 600);
    pros::delay(950);
    intake.move_relative(-500, 600);
    pros::delay(450);
   compression.set_value(true);
    pros::delay(500);
    intake.move_voltage(-12000);
    pros::delay(750);
    compression.set_value(false);
}


void autonomous() {



    switch(autonIndex){
        case 0: 

            

            //FRELIMS
            setFlywheel(3600);
            intake.move_voltage(12000);
            chassis.set_drive_pid(31,110,true,true);
            chassis.wait_drive();
            chassis.set_drive_pid(-1.5,110,false,true);
            chassis.wait_drive();
            pros::delay(1300);
            chassis.set_turn_pid(-64,110);
            chassis.wait_drive();
            featherDisks2();
            pros::delay(200);
            chassis.set_drive_pid(-8,110,false,true);
            chassis.wait_drive();
            setFlywheel(3200);
            chassis.set_drive_pid(-5,35,false,true);
            chassis.wait_until(-1.5);
            intake.move_voltage(0);
            chassis.set_drive_pid(1.5,110,false,true);
            chassis.wait_drive();
            chassis.set_turn_pid(-118,110);
            chassis.wait_drive();
            chassis.set_drive_pid(73.5,66,true,true);
            intake.move_voltage(12000);
            chassis.wait_drive();
            pros::delay(200);
            chassis.set_turn_pid(-29,110);
            chassis.wait_drive();
            featherDisks2();
            pros::delay(200);
            // chassis.set_turn_pid(12,110);
            // chassis.wait_drive();
            // intake.move_voltage(12000);
            // chassis.set_drive_pid(11.5,110,false,true);
            // chassis.wait_drive();
            // pros::delay(100);
            // chassis.set_turn_pid(-33.5,110);
            // chassis.wait_drive();
            // featherDisks();


            break;
        case 1:

            //AWP
            setFlywheel(3240);
            intake.move_voltage(-12000);
            chassis.set_drive_pid(-5,35,false,true);
            chassis.wait_until(-1.7);
            chassis.set_drive_pid(1,110,false,true);
            chassis.wait_drive();
            intake.move_voltage(12000);
            chassis.set_drive_pid(30,127,true,true);
            chassis.wait_drive();
            pros::delay(250);
            chassis.set_drive_pid(28,110,true,true);
            chassis.wait_drive();
            pros::delay(450);
            chassis.set_turn_pid(-82,110);
            chassis.wait_drive();
            featherDisks();
            pros::delay(300);
            chassis.set_turn_pid(-4,110);
            setFlywheel(3360);
            chassis.wait_drive();
            intake.move_voltage(12000);
            chassis.set_drive_pid(72,90,true,true);
            chassis.wait_drive();
            pros:delay(100);
            chassis.set_turn_pid(-115,110);
            chassis.wait_drive();
            featherDisks();
            pros::delay(300);
            chassis.set_turn_pid(-190,110);
            chassis.wait_drive();
            intake.move_voltage(0);
            chassis.set_drive_pid(-35.5,110,true,true);
            chassis.wait_drive();
            intake.move_voltage(-12000);
            chassis.set_drive_pid(-5,35,false,true);
            pros::delay(400);
            intake.move_voltage(0);
            chassis.set_drive_pid(0,0,false,true);
            

            break;
        case 2:
            

            //DRELIMS
            setFlywheel(3600);
            intake.move_voltage(12000);
            chassis.set_drive_pid(5,110,false,true);
            chassis.wait_drive();
            chassis.set_turn_pid(38,110);
            chassis.wait_drive();
            pros::delay(1250);
            featherDisks();
            pros::delay(100);
            chassis.set_drive_pid(-5.5,110,false,true);
            chassis.wait_drive();
            setFlywheel(3275);
            chassis.set_drive_pid(-5,35,false,true);
            chassis.wait_until(-1.7);
            intake.move_voltage(0);
            chassis.set_drive_pid(2.5,110,false,true);
            chassis.wait_drive();
            chassis.set_turn_pid(98.5,110);
            chassis.wait_drive();
            intake.move_voltage(12000);
            chassis.set_drive_pid(31,110,true,true);
            chassis.wait_drive();
            pros::delay(150);
            chassis.set_drive_pid(26,110,true,true);
            chassis.wait_drive();
            pros::delay(200);
            chassis.set_turn_pid(10,110);
            chassis.wait_drive();
            featherDisks();
            break;
        case 3:
           
            

            

            break;
        case 4:
            
            break;
        case 5:
           
            break;
        case 6:

            break;
        case 7:
            
            break;
        case 8: 

            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
    }
}
