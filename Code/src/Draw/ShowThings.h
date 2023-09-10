//
// Created by jonyl on 2023/8/18.
//

#ifndef CODE_SHOWTHINGS_H
#define CODE_SHOWTHINGS_H

#include <Arduino.h>
#include <Adafruit_NeoMatrix.h>
#include "Weather/WeatherNow.h"
#include "Weather/HttpsGetUtils.h"
#include "DrawThings.h"
#include "Tools/config.h"
#include "DrawAnimation.h"
#include "Game/Game.h"
#include "ShowMenu.h"

extern WeatherNow weatherNow; //天气定义

void showTime(int r,int g,int b);
void showWeather();

#endif //CODE_SHOWTHINGS_H
