//
// Created by jonyl on 2023/8/18.
//

#ifndef CODE_CONFIG_H
#define CODE_CONFIG_H
#include <Arduino.h>
#include <Adafruit_NeoMatrix.h>
#include <time.h>
#include <OneButton.h>
#include "Weather/WeatherNow.h"
#include "Weather/HttpsGetUtils.h"
#define PIN_LIGHT 5 //定义WS2812模块 GPIO
#define adc0 6
#define adc1 7
#define button_confirm 14
#define button_exit 16

extern Adafruit_NeoMatrix matrix;
extern OneButton button_c;
extern OneButton button_e;
extern int Brightness;
extern int joystick_x;
extern int joystick_y;
extern int BlinkerX;
extern int BlinkerY;
extern String BlinkerButtonState_confirm;
extern String BlinkerButtonState_exit;
extern String now_state;
extern int menu_index;
extern int info_index;

extern String wifi_ssid;
extern String wifi_pswd;
extern const char* auth;
extern const int SCREEN_WIDTH; //屏幕宽
extern const int SCREEN_HEIGHT; //屏幕高
extern const char* ntpServer;
extern const long gmtOffset_sec;
extern const int daylightOffset_sec;
extern String UserKey;
extern String location_code;
extern int connectTimeOut;
extern bool is_APmode;
extern int weatherRetryTime;
extern tm target_date;
extern bool state_c;
extern bool state_e;

#endif //CODE_CONFIG_H
