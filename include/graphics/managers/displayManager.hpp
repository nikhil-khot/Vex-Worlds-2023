#pragma once
#include "main.h"

//Display Fields
extern int menuIndex;
extern bool menuIndexChanged;

//Display Initialization
extern void displayInit();

//Asynchronous Display Task
extern void asyncDisplay(void* param);
