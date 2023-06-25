#include <Arduino.h>
#include <Adafruit_NeoMatrix.h>
#define NUM_LED 256 //定义led数量
#define PIN_LIGHT 1 //定义WS2812模块 GPIO

const int SCREEN_WIDTH = 32; //屏幕宽
const int SCREEN_HEIGHT = 8; //屏幕高
const int Brightness = 200;
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32,8,PIN_LIGHT,NEO_MATRIX_TOP + NEO_MATRIX_LEFT+NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,NEO_GRB + NEO_KHZ800);

//函数定义
void drawNumber(int x, int y, int num, int red, int green, int blue, int brightness);
void rainbowLight();

void setup(){
    //初始化串口波特率
    Serial.begin(115200);
    //初始化灯条
    matrix.begin();
    matrix.setBrightness(Brightness);
    matrix.show();
}

void loop(){
    for (int i=0;i<10;i++){
      drawNumber(i*4,1,i,random(20,200),random(20,200),random(20,200),Brightness);
      matrix.show();
      delay(500);
    }
}

/*
    DrawNumber函数实现，用来测试在屏幕上显示数字
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
  rainbowLight函数实现，用来实现彩虹色渐变
  Date: 2023.6.23
  Author: Jony
*/
void rainbowLight(){
  int k = 0;
    for (int i=0;i<32;i++){
      matrix.setPixelColor(i,Wheel(k));
      k+=5;
      delay(100);
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