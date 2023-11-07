//
// Created by jonyl on 2023/9/10.
//

#include "config.h"

String wifi_ssid = "";
String wifi_pswd = "";
const char* auth = "05aaa0279110";
const int SCREEN_WIDTH = 32; //屏幕宽
const int SCREEN_HEIGHT = 8; //屏幕高
const char* ntpServer = "ntp.aliyun.com";
const long gmtOffset_sec = 8 * 3600;
const int daylightOffset_sec = 0;
String UserKey = "3c446a5a055846a08e479b2ec283b110";
String location_code = "101260307";
Adafruit_NeoMatrix matrix(SCREEN_WIDTH, SCREEN_HEIGHT, PIN_LIGHT, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG, NEO_GRB + NEO_KHZ800);
int Brightness = 80;
int joystick_x;
int joystick_y;
int BlinkerX = 128;
int BlinkerY = 128;
String BlinkerButtonState_confirm;
String BlinkerButtonState_exit;
String now_state = "menu";
int menu_index = 1;
int info_index = 1;
int connectTimeOut = 10;
bool is_APmode = false;
