//
// Created by jonyl on 2023/11/2.
//

#include "SoftAP.h"

const byte DNS_PORT = 53;
const int webPort = 80;
const char* AP_SSID = "Neon-Zone";
String NetworksID = "";
IPAddress apIP(192,168,11,1);
DNSServer dnsServer;
WebServer webServer(webPort);
#define ROOT_HTML  "<!DOCTYPE html><html><head><title>WIFI</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head><style type=\"text/css\">.input{display: block; margin-top: 10px;}.input span{width: 100px; float: left; float: left; height: 36px; line-height: 36px;}.input input{height: 30px;width: 200px;}.btn{width: 120px; height: 35px; background-color: #000000; border:0px; color:#ffffff; margin-top:15px; margin-left:100px;}</style><body><form method=\"POST\" action=\"configwifi\"><label class=\"input\"><span>WiFi SSID</span><input type=\"text\" name=\"ssid\" value=\"\"></label><label class=\"input\"><span>WiFi PASS</span> <input type=\"text\"  name=\"pass\"></label><input class=\"btn\" type=\"submit\" name=\"submit\" value=\"Submit\"> <p><span> Nearby wifi:</P></form>"
String wifi_ssid = "";
String wifi_pswd = "";
int connectTimeOut = 15;

void handleRoot() {
    if (webServer.hasArg("selectSSID")) {
        webServer.send(200, "text/html", ROOT_HTML + NetworksID + "</body></html>");
    } else {
        webServer.send(200, "text/html", ROOT_HTML + NetworksID + "</body></html>");
    }
}

void handleConfigWifi()               //返回http状态
{
    if (webServer.hasArg("ssid"))          //判断是否有账号参数
    {
        Serial.print("got ssid:");
        wifi_ssid = webServer.arg("ssid");   //获取html表单输入框name名为"ssid"的内容

        Serial.println(wifi_ssid);
    }
    else                                //没有参数
    {
        Serial.println("error, not found ssid");
        webServer.send(200, "text/html", "<meta charset='UTF-8'>error, not found ssid"); //返回错误页面
        return;
    }
    //密码与账号同理
    if (webServer.hasArg("pass"))
    {
        Serial.print("got password:");
        wifi_pswd = webServer.arg("pass");  //获取html表单输入框name名为"pwd"的内容
        Serial.println(wifi_pswd);
    }
    else
    {
        Serial.println("error, not found password");
        webServer.send(200, "text/html", "<meta charset='UTF-8'>error, not found password");
        return;
    }
    webServer.send(200, "text/html", "<meta charset='UTF-8'>SSID：" + wifi_ssid + "<br />password:" + wifi_pswd + "<br />已取得WiFi信息,正在尝试连接,请手动关闭此页面。"); //返回保存成功页面
    delay(2000);
    WiFi.softAPdisconnect(true);     //参数设置为true，设备将直接关闭接入点模式，即关闭设备所建立的WiFi网络。
    webServer.close();                  //关闭web服务
    WiFi.softAPdisconnect();         //在不输入参数的情况下调用该函数,将关闭接入点模式,并将当前配置的AP热点网络名和密码设置为空值.
    Serial.println("WiFi Connect SSID:" + wifi_ssid + "  PASS:" + wifi_pswd);

    if (WiFi.status() != WL_CONNECTED)    //wifi没有连接成功
    {
        Serial.println("开始调用连接函数connectToWiFi()..");
        connectWifi(connectTimeOut);
    }
    else {
        Serial.println("提交的配置信息自动连接成功..");
    }
}

void handleNotFound(){
    handleRoot();
}

void initSoftAP(){
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP,apIP,IPAddress(255,255,255,0));
    if (WiFi.softAP(AP_SSID)){

        Serial.println("Neon-Zone SoftAP Mode init");
        Serial.print("SoftAP IP address = ");
        Serial.println(WiFi.softAPIP());
        Serial.println(String("MAC address = ")  + WiFi.softAPmacAddress().c_str());
    }
    else {
        Serial.println("SoftAP mode init failed,board will reboot");
        delay(1000);
        ESP.restart();
    }
}

void initDNSServer(){
    if (dnsServer.start(DNS_PORT, "*", apIP)){
        Serial.println("start dnsserver success.");
    }
    else {
        Serial.println("start dnsserver failed.");
    }
}

void initWebServer(){
    if (MDNS.begin("Neon-Zone")){
        Serial.println("MDNS responder started");
    }
    webServer.on("/",HTTP_GET,handleRoot);
    webServer.on("/configWifi",HTTP_POST,handleConfigWifi);

    webServer.onNotFound(handleNotFound);
    webServer.begin();
    Serial.println("WebServer start!");
}

bool scanWifi(){
    Serial.println("Wifi scan start!");
    int num_wifi = WiFi.scanNetworks();
    if (num_wifi == 0){
        Serial.println("No wifi found");
        return false;
    }
    else {
        Serial.print(num_wifi);
        Serial.print("wifi found");
        for (int i=0;i<num_wifi;i++){
            Serial.print(i+1);
            Serial.print(": ");
            Serial.print(WiFi.SSID());
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
            NetworksID += "<P>" + WiFi.SSID(i) + "</P>";
            delay(10);
        }
        return true;
    }
}

void connectWifi(int timeout){
    WiFi.hostname(HOST_NAME);
    Serial.println("Now connect to wifi");
    WiFi.mode(WIFI_STA);
    WiFi.setAutoConnect(true);

    if (wifi_ssid != ""){
        Serial.println("Connect wifi web config");
        WiFi.begin(wifi_ssid.c_str(),wifi_pswd.c_str());
        wifi_ssid = "";
        wifi_pswd = "";
    }
    else {
        Serial.println("Connect wift latest config");
        WiFi.begin();
    }

    int connectTime = 0;
    while (WiFi.status() != WL_CONNECTED){
        Serial.println(".");
        delay(1000);
        connectTime++;
        if (connectTime > connectTimeOut){
            Serial.println("Wifi connect time out,let do config");
            wifiConfig();
            return;
        }
    }

    if (WiFi.status() == WL_CONNECTED){
        Serial.println("WIFI connect Success");
        Serial.printf("SSID:%s", WiFi.SSID().c_str());
        Serial.printf(", PSW:%s\r\n", WiFi.psk().c_str());
        Serial.print("LocalIP:");
        Serial.print(WiFi.localIP());
        Serial.print(" ,GateIP:");
        Serial.println(WiFi.gatewayIP());
        Serial.print("WIFI status is:");
        Serial.print(WiFi.status());
        webServer.stop();
    }
}

void wifiConfig(){
    initSoftAP();
    initDNSServer();
    initWebServer();
    scanWifi();
}


void restoreWiFi() {
    delay(500);
    esp_wifi_restore();  //删除保存的wifi信息
    Serial.println("连接信息已清空");
}

void checkDNS_HTTP()
{
    dnsServer.processNextRequest();
    webServer.handleClient();
}
