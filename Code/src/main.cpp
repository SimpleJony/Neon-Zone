#include <Arduino.h>
#include <Adafruit_NeoMatrix.h>
#include <time.h>
#include <WiFi.h>
#define NUM_LED 256 //定义led数量
#define PIN_LIGHT 5 //定义WS2812模块 GPIO

const int SCREEN_WIDTH = 32; //屏幕宽
const int SCREEN_HEIGHT = 8; //屏幕高
const int Brightness = 200; //亮度设置
const char *ntpServer = "ntp.aliyun.com";
const long gmtOffset_sec = 8 * 3600;
const int daylightOffset_sec = 0;
const char* ssid = "Jony's K30";
const char* pswd = "jony123456";

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(SCREEN_WIDTH,SCREEN_HEIGHT,PIN_LIGHT,NEO_MATRIX_TOP + NEO_MATRIX_LEFT+NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,NEO_GRB + NEO_KHZ800); //灯矩阵定义

// 函数声明
void showTime(int r,int g,int b);
void connectWifi();
void drawNumber(int x, int y, int num, int red, int green, int blue, int brightness);
void drawWifi();
void drawSuccess();
void rainbowLight();
void drawGIF();
void drawTimer();
uint32_t Wheel(byte WheelPos);


void setup(){
    Serial.begin(9600);
    matrix.begin();
    matrix.setBrightness(Brightness);
    matrix.show();
    rainbowLight();
    delay(1000);
    connectWifi();
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop(){
    showTime(124,77,255);
}

/*
    showTime函数实现，用来在屏幕上显示当前时间
    Date: 2023.6.23
    Author: Jony
*/
void showTime(int r,int g,int b){
    matrix.clear();
    delay(500);
    while (true) {
        //获取时间
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        time_t now = time(nullptr); // 获取当前时间的UNIX时间戳
        struct tm* nowtime = localtime(&now); // 将UNIX时间戳转换为本地时间结构体
        //显示小时
        drawNumber(2,2,(nowtime->tm_hour / 10),r,g,b,Brightness);
        drawNumber(6,2,(nowtime->tm_hour % 10),r,g,b,Brightness);
        matrix.drawPixel(10,3,matrix.Color(r,g,b));
        matrix.drawPixel(10,5,matrix.Color(r,g,b));
        //显示分钟
        drawNumber(13,2,(nowtime->tm_min / 10),r,g,b,Brightness);
        drawNumber(17,2,(nowtime->tm_min % 10),r,g,b,Brightness);
        matrix.drawPixel(21,3,matrix.Color(r,g,b));
        matrix.drawPixel(21,5,matrix.Color(r,g,b));
        //显示秒数
        drawNumber(24,2,(nowtime->tm_sec / 10),r,g,b,Brightness);
        drawNumber(28,2,(nowtime->tm_sec % 10),r,g,b,Brightness);
        matrix.show();
        delay(500);
    } 
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
    Serial.println("Connected!");
    Serial.print("IP address:");
    Serial.print(WiFi.localIP());
    Serial.println("\n");
}

/*
    DrawNumber函数实现，用来在屏幕上显示数字
    Date: 2023.6.22
    Author: Jony
*/
void drawNumber(int x, int y, int num, int red, int green, int blue, int brightness) {
  if (num == 0) {
    for (int h = 0; h < 5; h++) {
      matrix.drawPixel(x, y + h, matrix.Color(red, green, blue));
      matrix.drawPixel(x + 2, y + h, matrix.Color(red, green, blue));
    }
    matrix.drawPixel(x + 1, y, matrix.Color(red, green, blue));
    matrix.drawPixel(x + 1, y + 4, matrix.Color(red, green, blue));
  }
  else if (num == 1) {
    for (int h = 0; h < 5; h++) {
      matrix.drawPixel(x + 1, y + h, matrix.Color(red, green, blue));
    }
    matrix.drawPixel(x, y + 1, matrix.Color(red, green, blue));
    matrix.drawPixel(x, y + 4, matrix.Color(red, green, blue));
    matrix.drawPixel(x + 2, y + 4, matrix.Color(red, green, blue));
  }
  else if (num == 2) {
    for (int w = 0; w < 3; w++) {
      matrix.drawPixel(x + 2, y + w, matrix.Color(red, green, blue));
    }
    for (int h = 0; h < 3; h++) {
      matrix.drawPixel(x, y + h, matrix.Color(red, green, blue));
    }
    matrix.drawPixel(x + 1, y + 2, matrix.Color(red, green, blue));
  }
  else if (num == 5) {
    for (int w = 0; w < 3; w++) {
      matrix.drawPixel(x + w, y, matrix.Color(red, green, blue));
      matrix.drawPixel(x + w, y + 2, matrix.Color(red, green, blue));
      matrix.drawPixel(x + w, y + 4, matrix.Color(red, green, blue));
    }
    matrix.drawPixel(x, y + 1, matrix.Color(red, green, blue));
    matrix.drawPixel(x + 2, y + 3, matrix.Color(red, green, blue));
  }
  else if (num == 6) {
    for (int w = 0; w < 3; w++) {
      matrix.drawPixel(x + w, y, matrix.Color(red, green, blue));
      matrix.drawPixel(x + w, y + 2, matrix.Color(red, green, blue));
    }
    matrix.drawPixel(x + 1, y + 4, matrix.Color(red, green, blue));
  }
  else if (num == 9) {
    for (int w = 0; w < 3; w++) {
      matrix.drawPixel(x + w, y, matrix.Color(red, green, blue));
      matrix.drawPixel(x + w, y + 2, matrix.Color(red, green, blue));
      matrix.drawPixel(x + w, y + 4, matrix.Color(red, green, blue));
    }
    matrix.drawPixel(x, y + 1, matrix.Color(red, green, blue));
    matrix.drawPixel(x + 2, y + 1, matrix.Color(red, green, blue));
    matrix.drawPixel(x + 2, y + 3, matrix.Color(red, green, blue));
  }
  matrix.setBrightness(brightness);
  matrix.show();
}

/*
  drawWifi函数实现，用来在屏幕上显示"WIFI"字样
  Date: 2023.6.24
  Author: Jony
*/
void drawWifi(){
    // draw "W"
    for (int i=1;i<=6;i++){
      matrix.drawPixel(3,i,matrix.Color(0,183,239));
    }
    for (int j=4;j<=7;j++){
      matrix.drawPixel(j,6,matrix.Color(0,183,239));
    }
    for (int k=2;k<=5;k++){
      matrix.drawPixel(5,k,matrix.Color(0,183,239));
    }
    for (int l=1;l<=5;l++){
      matrix.drawPixel(7,l,matrix.Color(0,183,239));
    }
    // draw "I"
    for (int i1=9;i1<=11;i1++){
      matrix.drawPixel(i1,1,matrix.Color(0,183,239));
    }
    for (int j1=2;j1<=5;j1++){
      matrix.drawPixel(10,j1,matrix.Color(0,183,239));
    }
    for (int k1=9;k1<=11;k1++){
      matrix.drawPixel(k1,6,matrix.Color(0,183,239));
    }
    // draw "F"
    for (int i2=13;i2<=15;i2++){
      matrix.drawPixel(i2,1,matrix.Color(0,183,239));
    }
    for (int j2=2;j2<=6;j2++){
      matrix.drawPixel(13,j2,matrix.Color(0,183,239));
    }
    for (int k2=14;k2<=15;k2++){
      matrix.drawPixel(k2,4,matrix.Color(0,183,239));
    }
    // draw "I"
    for (int i3=17;i3<=19;i3++){
      matrix.drawPixel(i3,1,matrix.Color(0,183,239));
    }
    for (int j3=2;j3<=5;j3++){
      matrix.drawPixel(18,j3,matrix.Color(0,183,239));
    }
    for (int k3=17;k3<=19;k3++){
      matrix.drawPixel(k3,6,matrix.Color(0,183,239));
    }
    matrix.show();
}

/*
  drawSuccess函数实现，用来在屏幕上显示勾
  Date: 2023.6.24
  Author: Jony
*/
void drawSuccess(){
    matrix.drawPixel(22,3,matrix.Color(102,255,0));
    matrix.drawPixel(23,4,matrix.Color(102,255,0));
    matrix.drawPixel(24,5,matrix.Color(102,255,0));
    matrix.drawPixel(25,6,matrix.Color(102,255,0));
    matrix.drawPixel(26,5,matrix.Color(102,255,0));
    matrix.drawPixel(27,4,matrix.Color(102,255,0));
    matrix.drawPixel(28,3,matrix.Color(102,255,0));
    matrix.drawPixel(29,2,matrix.Color(102,255,0));
    matrix.drawPixel(30,1,matrix.Color(102,255,0));
    matrix.show();
}

/*
  rainbowLight函数实现，用来实现彩虹色渐变
  Date: 2023.6.23
  Author: Jony
*/
void rainbowLight(){
  int k = 0;
    for (int i=0;i<32;i++){
      for (int j=0;j<8;j++){
        matrix.drawPixel(i,j,Wheel(k));
        matrix.show();
        k+=5;
        delay(100);
      }
    }
}

/*
  一个来自Adafruit NeoPixel的sample中的函数，为rainbowLight函数所用
  解释:
    Input a value 0 to 255 to get a color value.
    The colours are a transition r - g - b - back to r.
*/
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return matrix.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return matrix.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return matrix.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

/*
    drawGIF函数实现，用来在灯矩阵上画出"GIF"字样
    Date: 2023.6.25
    Author: Jony
*/
void drawGIF(){
    // draw "G"
    for (int i=8;i<13;i++){
        matrix.drawPixel(i,1,matrix.Color(255,163,177));
    }
    for (int j=2;j<7;j++){
        matrix.drawPixel(8,j,matrix.Color(255,163,177));
    }
    for (int k=9;k<13;k++){
        matrix.drawPixel(k,6,matrix.Color(255,163,177));
    }
    matrix.drawPixel(12,5,matrix.Color(255,163,177));
    matrix.drawPixel(12,4,matrix.Color(255,163,177));
    matrix.drawPixel(11,4,matrix.Color(255,163,177));
    // draw "I"
    for (int i1=14;i1<19;i1++){
        matrix.drawPixel(i1,1,matrix.Color(255,163,177));
    }
    for (int j1=2;j1<6;j1++){
        matrix.drawPixel(16,j1,matrix.Color(255,163,177));
    }
    for (int k1=14;k1<19;k1++){
        matrix.drawPixel(k1,6,matrix.Color(255,163,177));
    }
    // draw "F"
    for (int i2=20;i2<24;i2++){
        matrix.drawPixel(i2,1,matrix.Color(255,163,177));
    }
    for (int j2=2;j2<7;j2++){
        matrix.drawPixel(20,j2,matrix.Color(255,163,177));
    }
    for (int k2=21;k2<24;k2++){
        matrix.drawPixel(k2,4,matrix.Color(255,163,177));
    }
    matrix.show();
}

/*
    drawTimer函数实现，用来在灯矩阵上画出"TIMER"字样
    Date: 2023.6.25
    Author: Jony
*/
void drawTimer(){
    // Draw "T"
    for (int i=1;i<=5;i++){
        matrix.drawPixel(i,1,matrix.Color(255,163,177));
    }
    for (int j=2;j<=6;j++){
        matrix.drawPixel(3,j,matrix.Color(255,163,177));
    }
    // Draw "I"
    for (int i1=7;i1<=9;i1++){
        matrix.drawPixel(i1,1,matrix.Color(255,163,177));
    }
    for (int j1=2;j1<=6;j1++){
        matrix.drawPixel(8,j1,matrix.Color(255,163,177));
    }
    for (int k1=7;k1<=9;k1++){
        matrix.drawPixel(k1,6,matrix.Color(255,163,177));
    }
    // draw "M"
    for (int i2=11;i2<=12;i2++){
        matrix.drawPixel(i2,1,matrix.Color(255,163,177));
    }
    for (int j2=2;j2<=6;j2++){
        matrix.drawPixel(11,j2,matrix.Color(255,163,177));
    }
    matrix.drawPixel(13,2,matrix.Color(255,163,177));
    matrix.drawPixel(14,3,matrix.Color(255,163,177));
    matrix.drawPixel(15,2,matrix.Color(255,163,177));
    for (int k2=16;k2<=17;k2++){
        matrix.drawPixel(k2,1,matrix.Color(255,163,177));
    }
    for (int l2=2;l2<=6;l2++){
        matrix.drawPixel(17,l2,matrix.Color(255,163,177));
    }
    // draw "E"
    for (int i3=19;i3<=22;i3++){
        matrix.drawPixel(i3,1,matrix.Color(255,163,177));
    }
    for (int j3=2;j3<=6;j3++){
        matrix.drawPixel(19,j3,matrix.Color(255,163,177));
    }
    for (int k3=20;k3<=22;k3++){
        matrix.drawPixel(k3,4,matrix.Color(255,163,177));
    }
    for (int l3=20;l3<=22;l3++){
        matrix.drawPixel(l3,6,matrix.Color(255,163,177));
    }
    // Draw "R"
    for (int i4=24;i4<=27;i4++){
        matrix.drawPixel(i4,1,matrix.Color(255,163,177));
    }
    for (int j4=2;j4<=6;j4++) {
        matrix.drawPixel(24, j4, matrix.Color(255, 163, 177));
    }
    for (int k4=25;k4<=27;k4++){
        matrix.drawPixel(k4,4,matrix.Color(255,163,177));
    }
    matrix.drawPixel(26,5,matrix.Color(255,163,177));
    matrix.drawPixel(27,6,matrix.Color(255,163,177));
    matrix.drawPixel(27,2,matrix.Color(255,163,177));
    matrix.drawPixel(27,3,matrix.Color(255,163,177));
    matrix.show();
}
