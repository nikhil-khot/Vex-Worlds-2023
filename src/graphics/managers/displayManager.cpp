#include "graphics/managers/displayManager.hpp"
#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_chart.h"
#include "graphics/graphics.hpp"

//Display Fields
int menuIndex;
bool menuIndexChanged;

//Display Initialization
void displayInit(){
  menuIndex=0;
  menuIndexChanged=true;
}

//Asynchronous Display Task
void asyncDisplay(void* param){
  while(true){
    if(menuIndexChanged){
      lv_obj_clean(lv_scr_act());
      graphicsInit();
      if(menuIndex==0){
        autonMenuInit();
      }else if(menuIndex==1){
        diagnosticMenuInit();
      }else if(menuIndex==2){
        sensorMenuInit();
      }else if(menuIndex==3){
        tempMenuInit();
      }
      menuIndexChanged=false;
    }
    if(menuIndex==0){
      autonMenuUpdate();
    }else if(menuIndex==1){
      diagnosticMenuUpdate();
    }else if(menuIndex==2){
      sensorMenuUpdate();
    }else if(menuIndex==3){
      tempMenuUpdate();
    }
    pros::delay(200);
  }
}
