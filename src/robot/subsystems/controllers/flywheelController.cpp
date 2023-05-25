#include "robot/subsystems/controllers/flywheelController.hpp"
#include "pros/rtos.hpp"
#include "robot/globals.hpp"

//For Adi


double flywheelTarget, flywheelOutput, flywheelInput, flywheelError;
bool flywheelActive;
const double kP = 10, kV = 3.33333, threshold = 150;
//const double kP = 0.5, kV = 0.03528, threshold = 100;

void setFlywheel(double iTarget){
    flywheelTarget = iTarget;
}

void toggleFlywheel(){
    flywheelActive = !flywheelActive;
}

double getFlywheelTarget(){
    return (flywheelTarget / 36.0);
}
double getFlywheelOutput(){
    return (flywheel.get_actual_velocity() / 6.0);
}
double getFlywheelInput(){
    return (flywheelInput * 100.0 / 127.0);
}

void waitUntilFlywheelSettled(){
    while(flywheelError>=25){
        pros::delay(20);
    }
    pros::delay(20);
}

void flywheelInit(){
    flywheelTarget = 2900;
    flywheelInput = 0;
    flywheelOutput = 0;
    flywheelActive = true;
}

void asyncFlywheelController(void* param){
    while(true){
		flywheelOutput = flywheel.get_actual_velocity()*6.0;
		flywheelError = flywheelTarget - flywheelOutput;

		if(flywheelError > threshold){
			flywheelInput = 12000;
		}else if(flywheelError < -threshold){
			flywheelInput = 0;
		}else{
			flywheelInput = kV * flywheelTarget + kP * flywheelError;
		}

		if(flywheelInput>12000){
			flywheelInput = 12000;
		}else if(flywheelInput < 0){
			flywheelInput = 0;
		}
		if(flywheelActive)
			flywheel.move_voltage(flywheelInput);
		else
		 	flywheel.move_voltage(0);
		pros::delay(20);
	}
}

// void asyncFlywheelController(void* param){
//     while(true){
//         flywheelError = flywheelTarget - flywheel.get_actual_velocity() * 6.0;
        
//         if (flywheelError > threshold){
//             flywheelInput = 127;
//         } 
//         else if (flywheelError < -threshold){
//              flywheelInput = 0;
//         } 
//         else{
//             flywheelInput = (kV * flywheelTarget) + (kP * flywheelError);
//         }

//         if (flywheelInput > 127){
//             flywheelInput = 127;
//         } else if (flywheelInput < 0){
//             flywheelInput = 0;
//         }
//         if(flywheelActive){
//          flywheel.move(flywheelInput);
//         }else {
//             flywheel.move(0);
//         }
//         pros::delay(20);
//     }
// }