#include "main.h"
#include "robot/globals.hpp"
#include "robot/subsystems/controllers/flywheelController.hpp"
#include "robot/subsystems/managers/pneumaticManager.hpp"
#include <string>

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
 
    void opcontrol() {

        double intakeVoltage = 0;
        // *Max Flywheel RPM is 3600
        double flywheelRPM = 2900;

        bool blooperState = true;
        bool compressionState = false;
        bool endgameState = false;
        double elapsedTime = 0;
        double isEndgame = false;

        blooper.set_value(blooperState);

        while (true) {
            chassis.tank();

            //Angle Adjuster + Flywheel Control
            if(master.get_digital_new_press(DIGITAL_DOWN)){
                blooperState = !blooperState;
            }
            blooper.set_value(blooperState);

            //Intake/Roller Control
            if(master.get_digital(DIGITAL_R1)){
			    intakeVoltage = 12000;
			    compressionState = false;
		    } else if(master.get_digital(DIGITAL_L2)){
		    	compressionState = false;
		    	intakeVoltage = -12000;
		    }else if(master.get_digital(DIGITAL_R2)){
		    	compressionState = true;
		    	intakeVoltage = -12000;
		    } else {
		    	intakeVoltage=0;
		    	compressionState = false;
		    }
            compression.set_value(compressionState);

            if(master.get_digital(DIGITAL_LEFT)){
                intake.move_relative(-450, 600);
                pros::delay(1000);
            }else {
                intake.move_voltage(intakeVoltage);
            }

            //Flywheel Tuner
            if(master.get_digital_new_press(DIGITAL_RIGHT))
                flywheelRPM += 25;
            if(master.get_digital_new_press(DIGITAL_Y))
                flywheelRPM -= 25;


            if(master.get_digital_new_press(DIGITAL_L1)){
                if(flywheelRPM == 2900){
			    	flywheelRPM = 2800;
                    blooperState = false;
                }else if(flywheelRPM == 2800){
			    	flywheelRPM = 3600;
                    blooperState = false;
		    	}else if(flywheelRPM == 3600){
		    		flywheelRPM = 2900;
                    blooperState = true;
                }else{
		    	 	flywheelRPM = 2900;
                    blooperState = true;
                }
	    	}
            if(master.get_digital_new_press(DIGITAL_B)){
                toggleFlywheel();
            }
            setFlywheel(flywheelRPM);


            elapsedTime += 0.02;
            if(elapsedTime>=95) {
			    isEndgame = true;
		    }
            if(isEndgame && (master.get_digital_new_press(DIGITAL_Y) || master.get_digital_new_press(DIGITAL_RIGHT))){
			    endgameState = true;
		    }
            if(master.get_digital(DIGITAL_RIGHT) && master.get_digital(DIGITAL_Y)){
			    endgameState = true;
		    }
            if(master.get_digital_new_press(DIGITAL_RIGHT) && master.get_digital_new_press(DIGITAL_Y)){
			    endgameState = true;
		    }
            topEndgame.set_value(endgameState);
	    	bottomEndgame.set_value(endgameState);

            pros::delay(20);
            

            
            
            master.set_text(0,0, "Flywheel: " + std::to_string(flywheelRPM));
            //master.set_text(0,0, "E: " + std::to_string(endgameState) + " C: " + std::to_string(compressionState) + " B: " + std::to_string(blooperState));
		    //pros::lcd::set_text(3, "Xx Niggy Kitty xX");
         
        }
        
    }
