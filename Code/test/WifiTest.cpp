#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "Simplicity";
const char* pswd = "18722722085";

//函数声明
void connectWifi();

void setup(){
    Serial.begin(115200);
    connectWifi();
}

void loop(){
    
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
    Serial.println("Connected!");
    Serial.print("IP address:");
    Serial.print(WiFi.localIP());
}


