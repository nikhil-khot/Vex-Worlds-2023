#pragma once
#include "graphics.hpp"
#include "main.h"
#include <array>

//Graphics Fields

//Image Declaration
LV_IMG_DECLARE(Autonomous_Button_Pressed);
LV_IMG_DECLARE(Autonomous_Button_Released);
LV_IMG_DECLARE(Autonomous_Button_Toggled_Pressed);
LV_IMG_DECLARE(Autonomous_Button_Toggled_Released);

LV_IMG_DECLARE(Diagnostics_Button_Pressed);
LV_IMG_DECLARE(Diagnostics_Button_Released);
LV_IMG_DECLARE(Diagnostics_Button_Toggled_Pressed);
LV_IMG_DECLARE(Diagnostics_Button_Toggled_Released);

LV_IMG_DECLARE(Sensors_Button_Pressed);
LV_IMG_DECLARE(Sensors_Button_Released);
LV_IMG_DECLARE(Sensors_Button_Toggled_Pressed);
LV_IMG_DECLARE(Sensors_Button_Toggled_Released);

LV_IMG_DECLARE(Temperature_Button_Pressed);
LV_IMG_DECLARE(Temperature_Button_Released);
LV_IMG_DECLARE(Temperature_Button_Toggled_Pressed);
LV_IMG_DECLARE(Temperature_Button_Toggled_Released);

LV_IMG_DECLARE(Back_Button_Pressed);
LV_IMG_DECLARE(Back_Button_Released);

//Menu Functions
extern void autonMenuInit();
extern void autonMenuUpdate();

extern void diagnosticMenuInit();
extern void diagnosticMenuUpdate();

extern void sensorMenuInit();
extern void sensorMenuUpdate();

extern void tempMenuInit();
extern void tempMenuUpdate();

extern void graphicsInit();
