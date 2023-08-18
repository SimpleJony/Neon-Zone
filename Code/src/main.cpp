#include <Arduino.h>
#include <Adafruit_NeoMatrix.h>
#include <time.h>
#include <WiFi.h>
#include "Draw/DrawThings.h"
#include "Draw/ShowThings.h"
#include "Draw/DrawAnimation.h"
#include "Game/Game.h"
#include "config.h"

// 函数声明
void connectWifi();
void onBoot();
void menu();

void setup(){
    Serial.begin(9600);
    onBoot();
}

void loop(){
    //showTime(124,77,255);
    //menu();
    //snakeGame();
    //codeRain();
    //showWeather();
    adjustBrightness();
    drawProgressBar();
    delay(200);
}

/*
    connectWifi函数实现,用来使ESP32连接上网络
    Date: 2023.6.23
    Author: Jony
*/
void connectWifi(){
    int i=0;
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid,pswd);
    drawWifi();
    while (WiFi.status()!=WL_CONNECTED){
        delay(1000);
        i++;
        if (i==15){
            Serial.println("Connect to Wifi failed,board will reboot.");
            delay(1000);
            ESP.restart();
        }
        else{
            Serial.println("Connecting to Wifi...");
        }
    }
    drawSuccess();
    delay(1000);
    Serial.println("Connected!");
    Serial.print("IP address:");
    Serial.print(WiFi.localIP());
    Serial.println("\n");
}

/*
    onBoot函数实现，在开机时执行相应命令
    Date: 2023.7.31
    Author: Jony
*/
void onBoot(){
    matrix.begin();
    matrix.setBrightness(Brightness);
    matrix.show();
    rainbowLight();
    delay(2000);
    matrix.clear();
    delay(1000);
    connectWifi();
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    weatherNow.config(UserKey,location_code);
    weatherNow.get();
    matrix.clear();
}

// TODO: Optimize code. (Code unfinished)
void menu(){
    int menu_index = 0;
    while (true){
        joystick_x = analogRead(adc0);
        joystick_y = analogRead(adc1);
        if (joystick_x == 0 && joystick_y != 0){
            if (menu_index == 0){
                menu_index = 3;
            }
            else {
                menu_index -= 1;
            }
        }
        if (joystick_x == 8191 && joystick_y != 0){
            if (menu_index == 3){
                menu_index = 0;
            }
            else {
                menu_index += 1;
            }
        }
        if (menu_index == 0){
            matrix.clear();
            drawTime();
            delay(500);
        }
        if (menu_index == 1){
            matrix.clear();
            drawTimer();
            delay(500);
        }
        if (menu_index == 2){
            matrix.clear();
            drawGIF();
            delay(500);
        }
        if (menu_index == 3){
            matrix.clear();
            drawGame();
            delay(500);
        }
    }
}



