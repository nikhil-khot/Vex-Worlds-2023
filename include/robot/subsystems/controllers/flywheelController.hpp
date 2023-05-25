#pragma once
#include "main.h"

//Flywheel Setters
extern void toggleFlywheel();
extern void setFlywheel(double iTarget);

//Flywheel Getters
extern double getFlywheelTarget();
extern double getFlywheelInput();
extern double getFlywheelOutput();
extern void waitUntilFlywheelSettled();

//Flywheel Initialization
extern void flywheelInit();

//Asynchronous Flywheel Controller
extern void asyncFlywheelController(void* param);