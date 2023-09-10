//
// Created by jonyl on 2023/8/18.
//

#ifndef CODE_DRAWANIMATION_H
#define CODE_DRAWANIMATION_H
#include <Arduino.h>
#include <Adafruit_NeoMatrix.h>
#include "Tools/config.h"
#include "Draw/ShowThings.h"
#include "ShowMenu.h"
#include <vector>
#include <tuple>

void rainbowLight();
uint32_t Wheel(byte WheelPos);
std::tuple<int, int, int, uint32_t> createRainDrop();
void codeRain();

#endif //CODE_DRAWANIMATION_H
