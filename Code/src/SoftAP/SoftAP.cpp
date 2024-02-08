//
// Created by jonyl on 2023/11/4.
//

#include "SoftAP.h"

const byte DNS_PORT = 53;
const int webPort = 80;
const char* AP_SSID = "Neon-Zone";
const char* AP_PASS = "neonzone";
const char* HOST_NAME = "My_NeonZone";
String NetworkID = "";
IPAddress apModeIP(192,168,14,1);
DNSServer dnsServer;
WebServer webServer(webPort);

#define ROOT_HTML  "<!DOCTYPE html><html>" \
    "<head>" \
    "<title>WIFI</title>" \
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">" \
    "</head>" \
    "<style type=\"text/css\">" \
    ".input{display: block; margin-top: 10px;}" \
    ".input span{width: 100px; float: left; height: 36px; line-height: 36px;}" \
    ".input input{height: 30px;width: 200px;}" \
    ".btn{width: 120px; height: 35px; background-color: #000000; border:0px; color:#ffffff; margin-top:15px; margin-left:100px;}" \
    "</style>" \
    "<body>" \
    "<form method=\"POST\" action=\"configwifi\">" \
    "<label class=\"input\">" \
    "<span>WiFi SSID</span>" \
    "<input type=\"text\" name=\"ssid\">" \
    "</label>" \
    "<label class=\"input\">" \
    "<span>WiFi PASS</span>" \
    "<input type=\"text\" name=\"pass\">" \
    "</label>" \
    "<label class=\"input\">" \
    "<span>Countdown Year</span>" \
    "<input type=\"text\" name=\"countdown_year\">" \
    "</label>" \
    "<label class=\"input\">" \
    "<span>Countdown Month</span>" \
    "<input type=\"text\" name=\"countdown_month\">" \
    "</label>" \
    "<label class=\"input\">" \
    "<span>Countdown Day</span>" \
    "<input type=\"text\" name=\"countdown_day\">" \
    "</label>" \
    "<input class=\"btn\" type=\"submit\" name=\"submit\" value=\"Submit\">" \
    "<p><span> Nearby wifi:</span></p>" \
    "</form>" \
    "</body>" \
    "</html>"


void handleRoot()
{
    if (webServer.hasArg("selectSSID")) {
        webServer.send(200, "text/html", ROOT_HTML + NetworkID + "</body></html>");
    }
    else {
        webServer.send(200, "text/html", ROOT_HTML + NetworkID + "</body></html>");
    }
}

void handleConfigWifi()
{
    if (webServer.hasArg("ssid"))
    {
        wifi_ssid = webServer.arg("ssid");
    }
    else
    {
        Serial.println("error, not found ssid");
        webServer.send(200, "text/html", "<meta charset='UTF-8'>error, not found ssid"); //返回错误页面
        return;
    }
    //密码与账号同理
    if (webServer.hasArg("pass"))
    {
        wifi_pswd = webServer.arg("pass");
    }
    else
    {
        Serial.println("error, not found password");
        webServer.send(200, "text/html", "<meta charset='UTF-8'>error, not found password");
        return;
    }
    if (webServer.hasArg("countdown_year"))
    {
        countdown_year = webServer.arg("countdown_year").toInt();
        EEPROM.put(3000, countdown_year);
    }
    if (webServer.hasArg("countdown_month"))
    {
        countdown_month = webServer.arg("countdown_month").toInt();
        EEPROM.put(3000 + sizeof(int), countdown_month);
    }
    if (webServer.hasArg("countdown_day"))
    {
        countdown_day = webServer.arg("countdown_day").toInt();
        EEPROM.put(3000 + 2 * sizeof(int), countdown_day);
    }
    EEPROM.commit();
    webServer.send(200, "text/html", "<meta charset='UTF-8'>SSID：" + wifi_ssid + "<br />password:" + wifi_pswd + "<br />Countdown Year: " + String(countdown_year) + "<br />Countdown Month: " + String(countdown_month) + "<br />Countdown Day: " + String(countdown_day) + "<br />已取得WiFi信息和倒计时日期，正在尝试连接，请手动关闭此页面。");
    webServer.close();                  //关闭web服务
    WiFi.softAPdisconnect();         //在不输入参数的情况下调用该函数,将关闭接入点模式,并将当前配置的AP热点网络名和密码设置为空值.
    Serial.println("Got Wifi ssid: ");
    Serial.print(wifi_ssid);
    Serial.printf("\n");
    Serial.println("Got Wifi pswd: ");
    Serial.print(wifi_pswd);

    if (WiFi.status() != WL_CONNECTED)    //wifi没有连接成功
    {
        Serial.printf("\n");
        Serial.println("Connect to wifi now.");
        connectWifi(connectTimeOut);
    }
    else {
        Serial.println("Auto connect succeed.");
    }
}

void handleNotFound(){
    handleRoot();
}

void initSoftAP() {
    WiFi.mode(WIFI_AP);                                           //配置为AP模式
    WiFi.softAPConfig(apModeIP, apModeIP, IPAddress(255, 255, 255, 0));   //设置AP热点IP和子网掩码
    if (WiFi.softAP(AP_SSID,AP_PASS))                                     //开启AP热点,如需要密码则添加第二个参数
    {
        //打印相关信息
        Serial.println("Neon Zone SoftAP mode init success.");
        Serial.println("SoftAP Mode IP address: ");
        Serial.println(WiFi.softAPIP());                                                //接入点ip
        Serial.println(String("MAC address: ")  + WiFi.softAPmacAddress().c_str());    //接入点mac
    }
    else                                                  //开启AP热点失败
    {
        Serial.println("Neon Zone SoftAP mode init failed");
        delay(1000);
        Serial.println("restart now...");
        ESP.restart();                                      //重启复位esp32
    }
}

void initDNS()
{
    if (dnsServer.start(DNS_PORT, "*", apModeIP))   //判断将所有地址映射到esp32的ip上是否成功
    {
        Serial.println("Start DNSServer success.");
    } else {
        Serial.println("Start DNSServer failed.");
    }
}

void initWebServer(){
    if (MDNS.begin("Neon-Zone")){
        Serial.println("MDNS responder started.");
    }
    webServer.on("/",HTTP_GET,handleRoot);
    webServer.on("/configwifi",HTTP_POST,handleConfigWifi);
    webServer.onNotFound(handleNotFound);
    webServer.begin();
    Serial.println("WebServer started.");
}

bool scanWifi(){
    Serial.println("Start to scan wifi");
    int num_wifi = WiFi.scanNetworks();
    Serial.println("Scan wifi done.");
    if (num_wifi==0){
        Serial.println("No wifi found");
        return false;
    }
    else {
        Serial.println(num_wifi);
        Serial.print(" wifi found");
        for (int i=1;i<=num_wifi;i++){
            Serial.print(i);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
            NetworkID += "<P>" + WiFi.SSID(i) + "</P>";
            delay(10);
        }
        return true;
    }
}

void connectWifi(int timeout) {
    WiFi.hostname(HOST_NAME);
    Serial.println("In connectWifi() now.");
    WiFi.mode(WIFI_STA);
    WiFi.setAutoConnect(true);

    if (wifi_ssid != "") {
        Serial.println("Connect wifi web config");
        Serial.printf("\n");
        WiFi.begin(wifi_ssid.c_str(), wifi_pswd.c_str());
        wifi_ssid = "";
        wifi_pswd = "";
    } else {
        Serial.println("Connect with latest config");
        Serial.printf("\n");
        WiFi.begin();
    }
    uint8_t connectTime = 0;
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
        connectTime++;
        if (connectTime == connectTimeOut) {
            Serial.printf("\n");
            Serial.println("Connect to wifi failed,will do web config now");
            matrix.clear();
            drawWifi();
            drawX();
            delay(2000);
            matrix.clear();
            is_APmode = true;
            drawAP();
            drawArrow();
            configWifi();
            return;
        }
    }
    if (WiFi.status() == WL_CONNECTED)          //如果连接成功
    {
        Serial.println("WIFI connect Success");
        Serial.printf("SSID:%s\n", WiFi.SSID().c_str());
        Serial.printf(", PSWD:%s\r\n", WiFi.psk().c_str());
        Serial.print("LocalIP:");
        Serial.print(WiFi.localIP());
        Serial.print(" ,GateIP:");
        Serial.println(WiFi.gatewayIP());
        Serial.print("WIFI status is:");
        Serial.print(WiFi.status());
    }
}

void configWifi(){
    initSoftAP();
    initDNS();
    initWebServer();
    scanWifi();
}

void checkDNS(){
    dnsServer.processNextRequest();
    webServer.handleClient();
}

void restoreWifi(){
    esp_wifi_restore();
    delay(500);
    Serial.println("Clear the wifi data now.");
    Serial.println("Will restart now");
    ESP.restart();
}