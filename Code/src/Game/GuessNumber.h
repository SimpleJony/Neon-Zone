//
// Created by jonyl on 2024/2/9.
//

#ifndef CODE_GUESSNUMBER_H
#define CODE_GUESSNUMBER_H
#include <Arduino.h>
#include <Adafruit_NeoMatrix.h>
#include "Tools/config.h"
#include "Draw/DrawThings.h"
#include "Draw/ShowThings.h"
#include "Draw/DrawAnimation.h"
#include "Draw/ShowMenu.h"

void GuessNumber();
void resetNum(int &num_index, int &retryTime, int &randomNum, int &inputNum_b, int &inputNum_s, int &inputNum_g);

#endif //CODE_GUESSNUMBER_H
