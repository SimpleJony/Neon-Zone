//
// Created by jonyl on 2023/9/10.
//
#include "ShowThings.h"

WeatherNow weatherNow;
/*
    showTime函数实现，用来在屏幕上显示当前时间
    Date: 2023.6.23
    Author: Jony
*/
void showTime(int r,int g,int b){
    matrix.clear();
    delay(500);
    while (now_state == "time") {
        int buttonState_e  = digitalRead(16);
        if (BlinkerButtonState_exit == "tap" || buttonState_e == 0){
            BlinkerButtonState_exit = "null";
            matrix.clear();
            now_state = "info";
            ShowInfo();
        }
        //获取时间
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        time_t now = time(nullptr); // 获取当前时间的UNIX时间戳
        struct tm* nowtime = localtime(&now); // 将UNIX时间戳转换为本地时间结构体
        //显示小时
        drawNumber(2,1,(nowtime->tm_hour / 10),r,g,b,Brightness);
        drawNumber(6,1,(nowtime->tm_hour % 10),r,g,b,Brightness);
        matrix.drawPixel(10,2,matrix.Color(r,g,b));
        matrix.drawPixel(10,5,matrix.Color(r,g,b));
        //显示分钟
        drawNumber(12,1,(nowtime->tm_min / 10),r,g,b,Brightness);
        drawNumber(16,1,(nowtime->tm_min % 10),r,g,b,Brightness);
        matrix.drawPixel(20,2,matrix.Color(r,g,b));
        matrix.drawPixel(20,5,matrix.Color(r,g,b));
        //显示秒数
        drawNumber(22,1,(nowtime->tm_sec / 10),r,g,b,Brightness);
        drawNumber(26,1,(nowtime->tm_sec % 10),r,g,b,Brightness);
        matrix.show();
        delay(1000);
        matrix.clear();
    }
}

void showWeather(){
    matrix.clear();
    int weatherCode = weatherNow.getIcon();
    int temperature = weatherNow.getTemp();
    int buttonState_e;
    drawNumber(14,1,temperature / 10,0,183,239,Brightness);
    drawNumber(19,1,temperature % 10,0,183,239,Brightness);
    for (int i=24;i<=26;i++){
        matrix.drawPixel(i,1,matrix.Color(0,183,239));
        matrix.drawPixel(i,3,matrix.Color(0,183,239));
    }
    matrix.drawPixel(24,2,matrix.Color(0,183,239));
    matrix.drawPixel(26,2,matrix.Color(0,183,239));
    for (int i=1;i<=6;i++){
        matrix.drawPixel(28,i,matrix.Color(0,183,239));
    }
    for (int i=29;i<=30;i++){
        matrix.drawPixel(i,1,matrix.Color(0,183,239));
        matrix.drawPixel(i,6,matrix.Color(0,183,239));
    }

    switch (weatherCode){
        case 100:case 150:
            drawSunny();
            break;
        case 101:case 102:case 103:case 104:case 151:case 152:case 153:
            drawCloud();
            break;
        case 300:case 301:case 302:case 303:case 304:case 305:case 306:case 307:case 308:case 309:case 310:case 311:case 312:case 313:case 314:case 315:case 316:case 317:case 318:case 350:case 351:case 399:
            drawRain();
            break;
        case 400:case 401:case 402:case 403:case 404:case 405:case 406:case 407:case 408:case 409:case 410:case 456:case 457:case 499:
            drawSnow();
            break;
        default:
            drawUnknown();
            break;
    }
    matrix.show();
    while (buttonState_e != 0){
        buttonState_e = digitalRead(16);
    }
    while (now_state == "weather"){
        if (BlinkerButtonState_exit == "tap" || buttonState_e == 0){
            BlinkerButtonState_exit = "null";
            matrix.clear();
            now_state = "info";
            ShowInfo();
        }
    }
}

void showCountDown(){
    matrix.clear();
    int day_left = CountDown();
    int buttonState_e;
    drawNumber(9,1,day_left / 100,0,183,239,Brightness);
    drawNumber(13,1,(day_left % 100) / 10,0,183,239,Brightness);
    drawNumber(17,1,day_left % 10,0,183,239,Brightness);
    matrix.show();
    while (buttonState_e != 0){
        buttonState_e = digitalRead(16);
    }
    while (now_state == "countdown"){
        if (BlinkerButtonState_exit == "tap" || buttonState_e == 0){
            BlinkerButtonState_exit = "null";
            matrix.clear();
            now_state = "info";
            ShowInfo();
        }
    }
}