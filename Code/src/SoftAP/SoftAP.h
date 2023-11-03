//
// Created by jonyl on 2023/11/2.
//

#ifndef CODE_SOFTAP_H
#define CODE_SOFTAP_H
#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <esp_wifi.h>
#include "Tools/config.h"

extern const char* HOST_NAME;
void restoreWiFi();
//void checkDNS_HTTP();
void connectWifi(int timeout);
void handleRoot();
void handleConfigWifi();
void handleNotFound();
void initSoftAP();
void initDNSServer();
void initWebServer();
bool scanWifi();
void wifiConfig();
void checkConnection(bool isReconnect);

#endif //CODE_SOFTAP_H