//
// Created by jonyl on 2023/11/4.
//

#ifndef CODE_SOFTAP_H
#define CODE_SOFTAP_H

#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <esp_wifi.h>
#include "Tools/config.h"
#include "Draw/DrawThings.h"

extern const char* HOST_NAME;

void restoreWifi();
void checkDNS();
void connectWifi(int timeout);

void handleRoot();
void handleConfigWifi();
void handleNotFound();
void initSoftAP();
void initDNS();
void initWebServer();
bool scanWifi();
void configWifi();
#endif //CODE_SOFTAP_H
