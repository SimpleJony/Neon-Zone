//
// Created by jonyl on 2023/8/18.
//

#ifndef CODE_DRAWTHINGS_H
#define CODE_DRAWTHINGS_H
#include <Arduino.h>
#include <Adafruit_NeoMatrix.h>
#include "Tools/config.h"

void drawNumber(int x, int y, int num, int red, int green, int blue, int brightness);
void drawWifi();
void drawSuccess();
void drawGIF();
void drawTime();
void drawTimer();
void drawGame();
void drawScore();
void drawSunny();
void drawCloud();
void drawRain();
void drawSnow();
void drawUnknown();
void drawProgressBar();
void adjustBrightness();

#endif //CODE_DRAWTHINGS_H