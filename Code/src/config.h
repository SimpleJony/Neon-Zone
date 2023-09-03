//
// Created by jonyl on 2023/8/18.
//

#ifndef CODE_CONFIG_H
#define CODE_CONFIG_H
#define PIN_LIGHT 5 //定义WS2812模块 GPIO
#define adc0 6
#define adc1 7
#include <Arduino.h>
#include <Adafruit_NeoMatrix.h>

const char* ssid = "TP-LINK_6312甜馨2";
const char* pswd = "12345678";
const char* auth = "05aaa0279110";
const int SCREEN_WIDTH = 32; //屏幕宽
const int SCREEN_HEIGHT = 8; //屏幕高
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(SCREEN_WIDTH,SCREEN_HEIGHT,PIN_LIGHT,NEO_MATRIX_TOP + NEO_MATRIX_LEFT+NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,NEO_GRB + NEO_KHZ800); //灯矩阵定义
const char *ntpServer = "ntp.aliyun.com";
const long gmtOffset_sec = 8 * 3600;
const int daylightOffset_sec = 0;
int Brightness = 80; //亮度设置
String UserKey = "3c446a5a055846a08e479b2ec283b110";
String location_code = "101260307";
int joystick_x,joystick_y;
int BlinkerX=128,BlinkerY=128;

#endif //CODE_CONFIG_H
