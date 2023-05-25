#pragma once
#include "main.h"

//Pneumatics Initialization
extern void pneumaticInit();

//Pneumatic State Getters
extern bool getBlooperState();
extern bool getEndgameState();
extern bool getCompressionState();

//Pneumatic State Togglers
extern void toggleEndgame();
extern void toggleBlooper();
extern void toggleCompression();