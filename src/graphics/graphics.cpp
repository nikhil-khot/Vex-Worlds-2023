#include "display/lv_core/lv_obj.h"
#include "display/lv_misc/lv_color.h"
#include "display/lv_objx/lv_chart.h"
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include "display/lv_objx/lv_label.h"
#include "display/lvgl.h"
#include "graphics/graphics.hpp"
#include "graphics/managers/autonManager.hpp"
#include "graphics/managers/displayManager.hpp"
#include "robot/globals.hpp"
#include "robot/subsystems/controllers/flywheelController.hpp"
#include <sstream>
#include <string.h>
using namespace std;

//MENU BUTTONS
lv_obj_t * autonomousButton;
  lv_obj_t * autonButtonMatrix;
  lv_obj_t * autonomousName;
  lv_obj_t * autonomousDesc;
  static const char * btnm_map[] = {"1", "2", "3", "\n",
                                    "4", "5", "6", "\n",
                                    "7", "8", "9", "\n",
                                    "10", "11", "12",""};
lv_obj_t * diagnosticsButton;
  lv_obj_t * chart;
  lv_chart_series_t * targetSeries;
    std::array<double, 20> targetSeriesPoints;
  lv_chart_series_t * inputSeries;
    std::array<double, 20> inputSeriesPoints;
  lv_chart_series_t * outputSeries;
    std::array<double, 20> outputSeriesPoints;
lv_obj_t * sensorsButton;
lv_obj_t * temperatureButton;
  lv_obj_t * tempGauge;
  static lv_style_t gaugeStyle;

lv_obj_t * backButton;

//STYLES
static lv_style_t buttonBackgroundStyle;
static lv_style_t buttonReleasedStyle;
static lv_style_t buttonPressedStyle;
static lv_style_t buttonToggleStyle;
static lv_style_t chartStyle;

//COLORS
lv_color_t DARK_BUT_NOT_BLACK;
lv_color_t NOT_QUITE_BLACK;
lv_color_t KINDA_GRAY;
lv_color_t WANNABE_WHITE;
lv_color_t CHARTREUSE;
lv_color_t CRIMSON;
lv_color_t MARIGOLD;
lv_color_t ORANGE;
lv_color_t HOT_PINK;
lv_color_t AQUA;
lv_color_t LAVENDER;
lv_color_t BLURPLE;
lv_color_t OLIVE;

//Telemetry Graphics Functions
lv_obj_t * drawRectangle( int x, int y, int width, int height, int radius, int borderWidth, lv_color_t infillColor, lv_color_t gradColor, lv_color_t outlineColor) {
  lv_obj_t * obj1 = lv_obj_create(lv_scr_act(), NULL);

  lv_style_t *style1 = (lv_style_t *)malloc( sizeof( lv_style_t ));
  lv_style_copy(style1, &lv_style_plain_color);    /*Copy a built-in style to initialize the new style*/
  style1->body.empty = 0;
  style1->body.main_color = infillColor;
	style1->body.grad_color=gradColor;
	style1->body.border.color = outlineColor;
  style1->body.border.width = borderWidth;
	style1->body.radius=radius;
  style1->body.border.part = LV_BORDER_FULL;

  lv_obj_set_style(obj1, style1);
  lv_obj_set_pos(obj1, x, y);
  lv_obj_set_size(obj1, width, height);

  return obj1;
}

lv_obj_t * drawRectangle( int x, int y, int width, int height, int radius, int borderWidth, lv_color_t infillColor) {
  lv_obj_t * obj1 = lv_obj_create(lv_scr_act(), NULL);

  lv_style_t *style1 = (lv_style_t *)malloc( sizeof( lv_style_t ));
  lv_style_copy(style1, &lv_style_plain_color);    /*Copy a built-in style to initialize the new style*/
  style1->body.empty = 0;
  style1->body.main_color = infillColor;
	style1->body.grad_color=infillColor;
	style1->body.border.color = infillColor;
  style1->body.border.width = borderWidth;
	style1->body.radius=radius;
  style1->body.border.part = LV_BORDER_FULL;

  lv_obj_set_style(obj1, style1);
  lv_obj_set_pos(obj1, x, y);
  lv_obj_set_size(obj1, width, height);

  return obj1;
}

lv_obj_t * printText(int x, int y,const char* text){
  lv_obj_t * obj1 = lv_label_create(lv_scr_act(), NULL);

  lv_label_set_text(obj1, text);
  lv_obj_set_pos(obj1, x, y);

  return obj1;
}

lv_obj_t * createImageButton(int x, int y, const void *srcRel, const void *srcPrs, const void *srcTglRel, const void *srcTglPrs) {
  lv_obj_t * obj1 = lv_imgbtn_create(lv_scr_act(), nullptr);

  lv_imgbtn_set_src(obj1, LV_BTN_STATE_REL, &srcRel);
  lv_imgbtn_set_src(obj1, LV_BTN_STATE_PR, &srcPrs);
  lv_imgbtn_set_src(obj1, LV_BTN_STATE_TGL_REL, &srcTglRel);
  lv_imgbtn_set_src(obj1, LV_BTN_STATE_TGL_PR, &srcTglPrs);
  lv_imgbtn_set_toggle(obj1, true);
  lv_obj_set_pos(obj1, x, y);

  return obj1;
}

static lv_res_t menuButtonCallback(lv_obj_t * obj){
  lv_imgbtn_set_state(autonomousButton,LV_BTN_STATE_REL);
  lv_imgbtn_set_state(diagnosticsButton,LV_BTN_STATE_REL);
  lv_imgbtn_set_state(sensorsButton,LV_BTN_STATE_REL);
  lv_imgbtn_set_state(temperatureButton,LV_BTN_STATE_REL);
  if(obj == autonomousButton){
    menuIndex=0;
    lv_imgbtn_set_state(autonomousButton,LV_BTN_STATE_TGL_REL);
  }else if(obj == diagnosticsButton){
    menuIndex=1;
    lv_imgbtn_set_state(diagnosticsButton,LV_BTN_STATE_TGL_REL);
  }else if(obj == sensorsButton){
    menuIndex=2;
    lv_imgbtn_set_state(sensorsButton,LV_BTN_STATE_TGL_REL);
  }else if(obj == temperatureButton){
    menuIndex=3;
    lv_imgbtn_set_state(temperatureButton,LV_BTN_STATE_TGL_REL);
  }
  menuIndexChanged=true;
  return LV_RES_OK;
}

static lv_res_t btnm_action(lv_obj_t * btnm, const char *txt)
{
  std::stringstream strValue;
  int intValue;

  strValue << txt;
  strValue >> intValue;

  intValue -= 1;

  autonIndex=intValue;

  lv_label_set_text(autonomousName, autonNames[autonIndex]);
  lv_label_set_text(autonomousDesc, autonDescs[autonIndex]);

  return LV_RES_OK;
}

//Autonomous Menu Functions
void autonMenuInit(){
  autonButtonMatrix = lv_btnm_create(lv_scr_act(), NULL);
    lv_btnm_set_map(autonButtonMatrix, btnm_map);
    lv_btnm_set_toggle(autonButtonMatrix, true, autonIndex);
    lv_btnm_set_action(autonButtonMatrix, btnm_action);
    lv_obj_set_size(autonButtonMatrix, 207, 205);
    lv_obj_set_pos(autonButtonMatrix, 59, 30);
    lv_btnm_set_style(autonButtonMatrix, LV_BTNM_STYLE_BG, &buttonBackgroundStyle);
    lv_btnm_set_style(autonButtonMatrix, LV_BTNM_STYLE_BTN_REL, &buttonReleasedStyle);
    lv_btnm_set_style(autonButtonMatrix, LV_BTNM_STYLE_BTN_PR, &buttonPressedStyle);
    lv_btnm_set_style(autonButtonMatrix, LV_BTNM_STYLE_BTN_TGL_REL, &buttonToggleStyle);
    lv_btnm_set_style(autonButtonMatrix, LV_BTNM_STYLE_BTN_TGL_PR, &buttonToggleStyle);


  autonomousName = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_long_mode(autonomousName, LV_LABEL_LONG_BREAK);
    lv_label_set_align(autonomousName,LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(autonomousName, autonNames[autonIndex]);
    lv_obj_set_width(autonomousName, 195);
    lv_obj_align(autonomousName, NULL, LV_ALIGN_IN_TOP_MID, 131, 30);


  autonomousDesc = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_long_mode(autonomousDesc, LV_LABEL_LONG_BREAK);
    lv_label_set_style(autonomousDesc, &buttonPressedStyle);
    lv_label_set_align(autonomousDesc,LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(autonomousDesc, autonDescs[autonIndex]);
    lv_obj_set_width(autonomousDesc, 195);
    lv_obj_align(autonomousDesc, NULL, LV_ALIGN_IN_TOP_MID, 131, 60);
}

void autonMenuUpdate(){
  //TIMER
}

//Diagnostic Menu Functions
void diagnosticMenuInit(){
  /*Create a style for the chart*/
  static lv_style_t chartStyle;
  lv_style_copy(&chartStyle, &lv_style_pretty);
  chartStyle.body.main_color = DARK_BUT_NOT_BLACK;
  chartStyle.body.grad_color = DARK_BUT_NOT_BLACK;
  chartStyle.body.border.color =WANNABE_WHITE;
  chartStyle.body.border.width = 2;
  chartStyle.body.border.opa = 100;
  chartStyle.line.color = WANNABE_WHITE;
  chartStyle.line.opa = 100;
  chartStyle.line.rounded = false;

  /*Create a chart*/
  chart = lv_chart_create(lv_scr_act(), NULL);
  lv_obj_set_size(chart, 389, 175);
  lv_obj_set_style(chart, &chartStyle);
  lv_obj_set_pos(chart,59,30);
  lv_chart_set_type(chart, LV_CHART_TYPE_LINE); /*Show lines and points too*/
  lv_chart_set_point_count(chart,20);
  lv_chart_set_div_line_count(chart, 10, 3);
  lv_chart_set_series_width(chart, 2); /*Line width and point radious*/
  lv_chart_set_range(chart, 0, 110);

  for(int i=0; i < targetSeriesPoints.size();i++){
    targetSeriesPoints[i] = getFlywheelTarget();
  }

  for(int i=0; i < inputSeriesPoints.size();i++){
    inputSeriesPoints[i] = getFlywheelInput();
  }

  for(int i=0; i < outputSeriesPoints.size();i++){
    outputSeriesPoints[i] = getFlywheelOutput();
  }

  /*Add data series*/
  targetSeries = lv_chart_add_series(chart, CRIMSON);
      targetSeries->points[0] = getFlywheelTarget(); 
  inputSeries = lv_chart_add_series(chart, LV_COLOR_PURPLE);
    inputSeries->points[0] = getFlywheelInput();
  outputSeries = lv_chart_add_series(chart, MARIGOLD);
    outputSeries->points[0] = getFlywheelOutput();

  drawRectangle(59, 212, 20, 20, 2, 1, CRIMSON,CRIMSON, WANNABE_WHITE);
  drawRectangle(149, 212, 20, 20, 2, 1, LV_COLOR_PURPLE,LV_COLOR_PURPLE, WANNABE_WHITE);
  drawRectangle(219, 212, 20, 20, 2, 1, MARIGOLD,MARIGOLD, WANNABE_WHITE);

  printText(84, 212, "Target");
  printText(174, 212, "Input");
  printText(244, 212, "Output");
    
  for(int i=0;i<12;i++){
    int number= 110-i*10;
    stringstream strs;
    strs << number;
    string temp_str = strs.str();
    char* char_type = (char*) temp_str.c_str();
    printText(451, 25 + i*15, char_type);
  }

  lv_chart_refresh(chart); /*Required after direct set*/
}

void diagnosticMenuUpdate(){
  for(int i=0; i < targetSeriesPoints.size()-1;i++){
    targetSeriesPoints[i] = targetSeriesPoints[i+1];
    inputSeriesPoints[i] = inputSeriesPoints[i+1];
    outputSeriesPoints[i] = outputSeriesPoints[i+1];
  }

  targetSeriesPoints[targetSeriesPoints.size()-1]= getFlywheelTarget();
  inputSeriesPoints[inputSeriesPoints.size()-1]= getFlywheelInput();
  outputSeriesPoints[outputSeriesPoints.size()-1]= getFlywheelOutput();

  for(int i=0; i < targetSeriesPoints.size();i++){
    targetSeries->points[i] = targetSeriesPoints[i];
    inputSeries->points[i] = inputSeriesPoints[i];
    outputSeries->points[i] = outputSeriesPoints[i];
  }

  lv_chart_refresh(chart);
}

//Sensor Menu Functions
void sensorMenuInit(){

}

void sensorMenuUpdate(){
  
}

//Temperature Menu Functions
void tempMenuInit(){
  lv_style_copy(&gaugeStyle, &lv_style_pretty_color);
  gaugeStyle.body.main_color = LV_COLOR_BLUE; /*Line color at the beginning*/
  gaugeStyle.body.grad_color = LV_COLOR_RED; /*Line color at the end*/
  gaugeStyle.body.padding.hor = 10; /*Scale line length*/
  gaugeStyle.body.padding.inner = 8 ; /*Scale label padding*/
  gaugeStyle.body.border.color = WANNABE_WHITE; /*Needle middle circle color*/
  gaugeStyle.line.width = 3;
  gaugeStyle.text.color = WANNABE_WHITE;
  gaugeStyle.line.color = LV_COLOR_RED; /*Line color after the critical value*/
  /*Describe the color for the needles*/
  /*Create a gauge*/

  static lv_color_t needle_colors[] = {CHARTREUSE, MARIGOLD, ORANGE, HOT_PINK, AQUA, LAVENDER, BLURPLE, OLIVE};
  tempGauge = lv_gauge_create(lv_scr_act(), NULL);
  lv_gauge_set_style(tempGauge, &gaugeStyle);
  lv_gauge_set_needle_count(tempGauge, 8, needle_colors);
  lv_gauge_set_range(tempGauge, 10, 80);
  lv_gauge_set_scale(tempGauge, 280, 36, 8);
  lv_obj_align(tempGauge, NULL, LV_ALIGN_CENTER, 0, 20);
  lv_obj_set_size(tempGauge, 207, 205);
  lv_obj_set_pos(tempGauge, 59, 40);

  lv_gauge_set_value(tempGauge, 0, 10);
  lv_gauge_set_value(tempGauge, 1, 20);
  lv_gauge_set_value(tempGauge, 2, 30);
  lv_gauge_set_value(tempGauge, 3, 40);
  lv_gauge_set_value(tempGauge, 4, 50);
  lv_gauge_set_value(tempGauge, 5, 60);
  lv_gauge_set_value(tempGauge, 6, 70);
  lv_gauge_set_value(tempGauge, 7, 80);

  drawRectangle(290, 30, 20, 20, 5, 1, CHARTREUSE,CHARTREUSE, WANNABE_WHITE);
  drawRectangle(290, 56, 20, 20, 5, 1, MARIGOLD,MARIGOLD, WANNABE_WHITE);
  drawRectangle(290, 82, 20, 20, 5, 1, ORANGE,ORANGE, WANNABE_WHITE);
  drawRectangle(290, 108, 20, 20, 5, 1, HOT_PINK,HOT_PINK, WANNABE_WHITE);
  drawRectangle(290, 134, 20, 20, 5, 1, AQUA,AQUA, WANNABE_WHITE);
  drawRectangle(290, 160, 20, 20, 5, 1, LAVENDER,LAVENDER, WANNABE_WHITE);
  drawRectangle(290, 186, 20, 20, 5, 1, BLURPLE,BLURPLE, WANNABE_WHITE);
  drawRectangle(290, 212, 20, 20, 5, 1, OLIVE,OLIVE, WANNABE_WHITE);

  printText(320, 30, "Left Back Drive");
  printText(320, 56, "Left Middle Drive");
  printText(320, 82, "Left Front Drive");
  printText(320, 108, "Right Back Drive");
  printText(320, 134, "Right Middle Drive");
  printText(320, 160, "Right Front Drive");
  printText(320, 186, "Flyhweel");
  printText(320, 212, "Intake/Indexer");
}

void tempMenuUpdate(){
  //Update Color of Motor Label with styles
  for(int i=0;i<8;i++){
      lv_gauge_set_value(tempGauge, i, motors[i].get_temperature());
  }
}

//Graphics Initialization
void graphicsInit(){
  DARK_BUT_NOT_BLACK = LV_COLOR_MAKE(35, 39, 42);
  NOT_QUITE_BLACK = LV_COLOR_MAKE(44, 47, 51);
  KINDA_GRAY = LV_COLOR_MAKE(48, 53, 56);
  WANNABE_WHITE = LV_COLOR_MAKE(143, 149, 145);
  CHARTREUSE = LV_COLOR_MAKE(67,181,129);
  CRIMSON = LV_COLOR_MAKE(220,20,60);
  MARIGOLD = LV_COLOR_MAKE(248,195,0);
  ORANGE = LV_COLOR_MAKE(245, 119, 49);
  HOT_PINK = LV_COLOR_MAKE(255, 20, 147);
  AQUA = LV_COLOR_MAKE(0, 255, 255);
  LAVENDER = LV_COLOR_MAKE(166, 82, 187);
  BLURPLE = LV_COLOR_MAKE(114, 137, 218);
  OLIVE = LV_COLOR_MAKE(128,128,0);


  drawRectangle(0, 0, 480, 240, 0, 1, DARK_BUT_NOT_BLACK); //Outline
  drawRectangle(50, 21, 440, 219, 5, 1, NOT_QUITE_BLACK); //Background
  drawRectangle(5, 21, 40, 3, 2, 1, WANNABE_WHITE); //Border

  printText(4,2,"N.K.");


  autonomousButton =lv_imgbtn_create(lv_scr_act(), nullptr);
    lv_imgbtn_set_action(autonomousButton, LV_BTN_ACTION_CLICK, menuButtonCallback);
    lv_imgbtn_set_src(autonomousButton, LV_BTN_STATE_REL, &Autonomous_Button_Released);
    lv_imgbtn_set_src(autonomousButton, LV_BTN_STATE_PR, &Autonomous_Button_Pressed);
    lv_imgbtn_set_src(autonomousButton, LV_BTN_STATE_TGL_REL, &Autonomous_Button_Toggled_Released);
    lv_imgbtn_set_src(autonomousButton, LV_BTN_STATE_TGL_PR, &Autonomous_Button_Toggled_Pressed);
    lv_imgbtn_set_toggle(autonomousButton, true);
    lv_obj_set_pos(autonomousButton, 5, 29);


  diagnosticsButton =lv_imgbtn_create(lv_scr_act(), nullptr);
    lv_imgbtn_set_action(diagnosticsButton, LV_BTN_ACTION_CLICK, menuButtonCallback);
    lv_imgbtn_set_src(diagnosticsButton, LV_BTN_STATE_REL, &Diagnostics_Button_Released);
    lv_imgbtn_set_src(diagnosticsButton, LV_BTN_STATE_PR, &Diagnostics_Button_Pressed);
    lv_imgbtn_set_src(diagnosticsButton, LV_BTN_STATE_TGL_REL, &Diagnostics_Button_Toggled_Released);
    lv_imgbtn_set_src(diagnosticsButton, LV_BTN_STATE_TGL_PR, &Diagnostics_Button_Toggled_Pressed);
    lv_imgbtn_set_toggle(diagnosticsButton, true);
    lv_obj_set_pos(diagnosticsButton, 5,74);

  sensorsButton =lv_imgbtn_create(lv_scr_act(), nullptr);
    lv_imgbtn_set_action(sensorsButton, LV_BTN_ACTION_CLICK, menuButtonCallback);
    lv_imgbtn_set_src(sensorsButton, LV_BTN_STATE_REL, &Sensors_Button_Released);
    lv_imgbtn_set_src(sensorsButton, LV_BTN_STATE_PR, &Sensors_Button_Pressed);
    lv_imgbtn_set_src(sensorsButton, LV_BTN_STATE_TGL_REL, &Sensors_Button_Toggled_Released);
    lv_imgbtn_set_src(sensorsButton, LV_BTN_STATE_TGL_PR, &Sensors_Button_Toggled_Pressed);
    lv_imgbtn_set_toggle(sensorsButton, true);
    lv_obj_set_pos(sensorsButton, 5, 119);

  temperatureButton =lv_imgbtn_create(lv_scr_act(), nullptr);
    lv_imgbtn_set_action(temperatureButton, LV_BTN_ACTION_CLICK, menuButtonCallback);
    lv_imgbtn_set_src(temperatureButton, LV_BTN_STATE_REL, &Temperature_Button_Released);
    lv_imgbtn_set_src(temperatureButton, LV_BTN_STATE_PR, &Temperature_Button_Pressed);
    lv_imgbtn_set_src(temperatureButton, LV_BTN_STATE_TGL_REL, &Temperature_Button_Toggled_Released);
    lv_imgbtn_set_src(temperatureButton, LV_BTN_STATE_TGL_PR, &Temperature_Button_Toggled_Pressed);
    lv_imgbtn_set_toggle(temperatureButton, true);
    lv_obj_set_pos(temperatureButton, 5, 164);

    if(menuIndex==0){
      lv_imgbtn_set_state(autonomousButton,LV_BTN_STATE_TGL_REL);
    }else if(menuIndex==1){
      lv_imgbtn_set_state(diagnosticsButton,LV_BTN_STATE_TGL_REL);
    }else if(menuIndex==2){
      lv_imgbtn_set_state(sensorsButton,LV_BTN_STATE_TGL_REL);
    }else if(menuIndex==3){
      lv_imgbtn_set_state(temperatureButton,LV_BTN_STATE_TGL_REL);
    }

  backButton =lv_imgbtn_create(lv_scr_act(), nullptr);
    lv_imgbtn_set_src(backButton, LV_BTN_STATE_REL, &Back_Button_Released);
    lv_imgbtn_set_src(backButton, LV_BTN_STATE_PR, &Back_Button_Pressed);
    lv_imgbtn_set_toggle(backButton, false);
    lv_obj_set_pos(backButton, 5, 209);
    lv_imgbtn_set_state(backButton,LV_BTN_STATE_REL);



    /*Create a new style for the button matrix back ground*/
    lv_style_copy(&buttonBackgroundStyle, &lv_style_plain);
    buttonBackgroundStyle.body.main_color = DARK_BUT_NOT_BLACK;
    buttonBackgroundStyle.body.grad_color = DARK_BUT_NOT_BLACK;
    buttonBackgroundStyle.body.padding.hor = 0;
    buttonBackgroundStyle.body.padding.ver = 0;
    buttonBackgroundStyle.body.padding.inner = 0;

  /*Create 2 button styles*/
    lv_style_copy(&buttonReleasedStyle, &lv_style_btn_rel);
    buttonReleasedStyle.body.main_color = DARK_BUT_NOT_BLACK;
    buttonReleasedStyle.body.grad_color = DARK_BUT_NOT_BLACK;
    buttonReleasedStyle.body.border.color = WANNABE_WHITE;
    buttonReleasedStyle.body.border.width = 1;
    buttonReleasedStyle.body.border.opa = LV_OPA_50;
    buttonReleasedStyle.body.radius = 5;
    buttonReleasedStyle.text.color = WANNABE_WHITE;

    lv_style_copy(&buttonPressedStyle, &lv_style_btn_pr);
    buttonPressedStyle.body.main_color = KINDA_GRAY;
    buttonPressedStyle.body.grad_color = KINDA_GRAY;
    buttonPressedStyle.text.color = WANNABE_WHITE;
    buttonPressedStyle.body.border.color = WANNABE_WHITE;

    lv_style_copy(&buttonToggleStyle, &lv_style_btn_pr);
    buttonToggleStyle.body.main_color = KINDA_GRAY;
    buttonToggleStyle.body.grad_color = KINDA_GRAY;
    buttonToggleStyle.text.color = WANNABE_WHITE;
    buttonToggleStyle.body.border.color = CHARTREUSE;

  lv_style_copy(&chartStyle, &lv_style_pretty);
  chartStyle.body.main_color = DARK_BUT_NOT_BLACK;
  chartStyle.body.grad_color = DARK_BUT_NOT_BLACK;
  chartStyle.body.border.color =WANNABE_WHITE;
  chartStyle.body.border.width = 2;
  chartStyle.body.border.opa = 100;
  chartStyle.line.color = WANNABE_WHITE;
  chartStyle.line.opa = 100;
  chartStyle.line.rounded = false;
}
