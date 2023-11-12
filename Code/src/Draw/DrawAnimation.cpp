//
// Created by jonyl on 2023/9/10.
//
#include "DrawAnimation.h"

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
            delay(5);
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

std::tuple<int, int, int, uint32_t> createRainDrop() {
    int x = random(0, SCREEN_WIDTH - 1);
    int speed = random(1, 3);

    int r = random(0, 255);
    int g = random(0, 255);
    int b = random(0, 255);
    uint32_t color = matrix.Color(r, g, b);
    return std::make_tuple(x, 0, speed, color);
}

void codeRain() {
    matrix.fillScreen(0);
    matrix.show();

    std::vector<std::tuple<int, int, int, uint32_t>> raindrops;

    while (now_state == "gif") {
        int buttonState_e = digitalRead(16);
        if (BlinkerButtonState_exit == "tap" || buttonState_e == 0){
            BlinkerButtonState_exit = "null";
            matrix.clear();
            now_state = "menu";
            ShowMenu();
        }
        matrix.fillScreen(0);
        if (raindrops.size() < 10) {
            raindrops.push_back(createRainDrop());
        }

        for (int i = 0; i < raindrops.size(); i++) {
            int x, y, speed;
            uint32_t color;
            std::tie(x, y, speed, color) = raindrops[i];
            matrix.drawPixel(x, y, color);
            y += 1;
            // 边界处理
            if (y >= SCREEN_HEIGHT) {
                raindrops[i] = createRainDrop();
            } else {
                raindrops[i] = std::make_tuple(x, y, speed, color);
            }

            delay(5);
        }
        matrix.show();
    }
}