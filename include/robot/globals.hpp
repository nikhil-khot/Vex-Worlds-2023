#pragma once
#include "main.h"
#include "pros/adi.hpp"
#include "pros/distance.hpp"

//Controller
extern Controller master;

//Motors
extern pros::Motor flywheel, intake;
extern pros::Motor motors[8];

//Pneumatics
extern pros::ADIDigitalOut topEndgame, bottomEndgame, blooper, compression;

//Chassis
extern Drive chassis;

extern string nameString;



