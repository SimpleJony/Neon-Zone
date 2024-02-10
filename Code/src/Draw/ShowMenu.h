//
// Created by jonyl on 2023/9/10.
//

#ifndef CODE_SHOWMENU_H
#define CODE_SHOWMENU_H
#include <Arduino.h>
#include <WiFi.h>
#include "Draw/DrawThings.h"
#include "Draw/ShowThings.h"
#include "Draw/DrawAnimation.h"
#include "Game/Snake.h"
#include "Game/GuessNumber.h"
#include "Tools/config.h"
#include "Tools/Timer.h"
#include "SoftAP/SoftAP.h"

void ShowMenu();
void ShowInfo();
void ShowSet();
void ShowGame();

#endif //CODE_SHOWMENU_H
