#define BLINKER_PRINT Serial
#define BLINKER_WIFI
#define BLINKER_ESP_TASK
#define BLINKER_MIOT_LIGHT
#include <Arduino.h>
#include <Blinker.h>
#include <WiFi.h>
#include "Draw/ShowThings.h"
#include "Draw/DrawAnimation.h"
#include "Draw/ShowMenu.h"
#include "BlinkerControl/XiaoAiControl.h"
#include "Tools/config.h"
#include "SoftAP/SoftAP.h"

// 函数声明
void onBoot();

void setup(){
    Serial.begin(115200);
    onBoot();
}

void loop(){
    checkDNS();
    if (WiFi.status() == WL_CONNECTED){
        if (is_APmode){
            ESP.restart();
        }
        ShowMenu();
    }
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
    matrix.begin();
    matrix.setBrightness(Brightness);
    matrix.show();
    rainbowLight();
    delay(2000);
    matrix.clear();
    delay(1000);
    drawWifi();
    drawArrow();
    connectWifi(connectTimeOut);
    if (WiFi.status() == WL_CONNECTED){
        matrix.clear();
        drawWifi();
        drawSuccess();
        delay(1000);
        Blinker.begin(auth,WiFi.SSID().c_str(),WiFi.psk().c_str());
        BLINKER_TAST_INIT();
        Blinker_callback();
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        weatherNow.config(UserKey,location_code);
        weatherNow.get();
        matrix.clear();
    }
}
