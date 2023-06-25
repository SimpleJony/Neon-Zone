#include <Arduino.h>
#include <Adafruit_NeoMatrix.h>
#include <time.h>
#include <WiFi.h>
#include <LightControlTest.cpp>
#include <WifiTest.cpp>
#define NUM_LED 256 //定义led数量
#define PIN_LIGHT 1 //定义WS2812模块 GPIO

const int SCREEN_WIDTH = 32; //屏幕宽
const int SCREEN_HEIGHT = 8; //屏幕高
const int Brightness = 200;
const char *ntpServer = "ntp.aliyun.com";
const long gmtOffset_sec = 8 * 3600;
const int daylightOffset_sec = 0;
const char* ssid = "Simplicity";
const char* pswd = "18722722085";

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32,8,PIN_LIGHT,NEO_MATRIX_TOP + NEO_MATRIX_LEFT+NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,NEO_GRB + NEO_KHZ800);

void showTime(int r,int g,int b);

void printLocalTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.println(&timeinfo, "%F %T %A"); // 格式化输出
}

void setup(){
    Serial.begin(115200);
    connectWifi();
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();
}

void loop(){
    delay(1000);
    printLocalTime();
    showTime(124,77,255);
}

/*
    showTime函数实现，用来在屏幕上显示当前时间
    Date: 2023.6.23
    Author: Jony
*/
void showTime(int r,int g,int b){
    struct tm nowtime;
    matrix.clear();
    delay(500);
    while (true) {
        //显示小时
        drawNumber(2,2,(nowtime.tm_hour / 10),r,g,b,Brightness);
        drawNumber(6,2,(nowtime.tm_hour % 10),r,g,b,Brightness);
        matrix.drawPixel(10,3,matrix.Color(r,g,b));
        matrix.drawPixel(10,5,matrix.Color(r,g,b));
        //显示分钟
        drawNumber(13,2,(nowtime.tm_min / 10),r,g,b,Brightness);
        drawNumber(17,2,(nowtime.tm_min % 10),r,g,b,Brightness);
        matrix.drawPixel(21,3,matrix.Color(r,g,b));
        matrix.drawPixel(21,5,matrix.Color(r,g,b));
        //显示秒数
        drawNumber(24,2,(nowtime.tm_sec / 10),r,g,b,Brightness);
        drawNumber(28,2,(nowtime.tm_sec % 10),r,g,b,Brightness);
        matrix.show();
        delay(100);
    } 
}

