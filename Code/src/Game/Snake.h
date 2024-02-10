//
// Created by jonyl on 2023/8/18.
//

#ifndef CODE_SNAKE_H
#define CODE_SNAKE_H
#include <Arduino.h>
#include <Adafruit_NeoMatrix.h>
#include "Tools/config.h"
#include "Draw/DrawThings.h"
#include "Draw/ShowThings.h"
#include "Draw/DrawAnimation.h"
#include "Draw/ShowMenu.h"

struct Snake {
    int x;
    int y;
    int r;
    int g;
    int b;
};

struct Food {
    int x;
    int y;
    int r;
    int g;
    int b;
};

void resetGame(Snake snake[], Food &food, int &snake_length, int &snake_speed, int &snake_x, int &snake_y, int &snake_r, int &snake_g, int &snake_b, String &direction);
void snakeGame();
#endif //CODE_SNAKE_H
