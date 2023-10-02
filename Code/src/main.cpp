#define BLINKER_PRINT Serial
#define BLINKER_WIFI
#define BLINKER_ESP_TASK
#define BLINKER_MIOT_LIGHT
#include <Arduino.h>
#include <Blinker.h>
#undef ARDUINOJSON_DEFINE_PROGMEM_ARRAY
#include "Draw/DrawThings.h"
#include "Draw/ShowThings.h"
#include "Draw/DrawAnimation.h"
#include "Draw/ShowMenu.h"
#include "BlinkerControl/XiaoAiControl.h"
#include "Tools/config.h"

// 函数声明
void onBoot();

void setup(){
    Serial.begin(9600);
    onBoot();
}

void loop(){
    ShowMenu();
    //snakeGame();
    //codeRain();
    //showWeather();
    delay(200);
}

/*
    onBoot函数实现，在开机时执行相应命令
    Date: 2023.7.31
    Author: Jony
*/
void onBoot(){
    #if defined(BLINKER_PRINT)
    BLINKER_DEBUG.stream(BLINKER_PRINT);
    #endif
    Blinker.begin(auth,ssid,pswd);
    BLINKER_TAST_INIT();
    Blinker_callback();
    matrix.begin();
    matrix.setBrightness(Brightness);
    matrix.show();
    rainbowLight();
    delay(2000);
    matrix.clear();
    delay(1000);
    //connectWifi();
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    weatherNow.config(UserKey,location_code);
    weatherNow.get();
    matrix.clear();
}
