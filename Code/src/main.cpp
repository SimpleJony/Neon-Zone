#define BLINKER_PRINT Serial
#define BLINKER_WIFI
#define BLINKER_ESP_TASK
#define BLINKER_MIOT_LIGHT
#include <Arduino.h>
#include <Blinker.h>
#include <WiFi.h>
#include <EEPROM.h>
#include "Draw/ShowThings.h"
#include "Draw/DrawAnimation.h"
#include "Draw/ShowMenu.h"
#include "BlinkerControl/XiaoAiControl.h"
#include "Tools/config.h"
#include "SoftAP/SoftAP.h"

EEPROMClass IS_FIRST_BOOT("eeprom0");
bool is_first_boot = false;
// 函数声明
void onBoot();
void EEPROMInit();

void setup(){
    Serial.begin(115200);
    onBoot();
}

void loop(){
    checkDNS();
    if (WiFi.status() == WL_CONNECTED){
        if (is_first_boot){
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
    EEPROMInit();
    drawWifi();
    connectWifi(connectTimeOut);
    if (WiFi.status() == WL_CONNECTED){
        drawSuccess();
        delay(1000);
        if (is_first_boot){
            ESP.restart();
        }
        Blinker.begin(auth,WiFi.SSID().c_str(),WiFi.psk().c_str());
        BLINKER_TAST_INIT();
        Blinker_callback();
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        weatherNow.config(UserKey,location_code);
        weatherNow.get();
        matrix.clear();
    }
}

void EEPROMInit(){
    Serial.println("Neon Zone EEPROM initialize start.");
    if (!IS_FIRST_BOOT.begin(2)){
        Serial.println("Failed to initialize IS_FIRST_BOOT");
        Serial.println("Board will reboot.");
        delay(1000);
        ESP.restart();
    }

    if (IS_FIRST_BOOT.readUChar(0) != 0xA5 || IS_FIRST_BOOT.readUChar(1) != 0x5A){
        Serial.println("Neon Zone first boot detected.");
        is_first_boot = true;
        IS_FIRST_BOOT.writeUChar(0,0xA5);
        IS_FIRST_BOOT.writeUChar(1,0x5A);
        IS_FIRST_BOOT.commit();
    }

    Serial.println("Neon Zone EEPROM initialize succeed.");
}
