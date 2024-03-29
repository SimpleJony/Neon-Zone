//
// Created by jonyl on 2023/9/10.
//
#include "Snake.h"

void resetGame(Snake* snake, Food &food, int &snake_length, int &snake_speed, int &snake_x, int &snake_y, int &snake_r, int &snake_g, int &snake_b, String &direction) {
    joystick_x = 0;
    joystick_y = 0;

    snake_length = 3;
    snake_speed = 100;
    snake_x = 0;
    snake_y = 0;
    snake_r = 255;
    snake_g = 0;
    snake_b = 0;
    direction = "right";

    matrix.begin();
    matrix.setTextWrap(false);
    matrix.fillScreen(matrix.Color(0, 0, 0));
    matrix.show();

    randomSeed(analogRead(0));
    food.x = random(SCREEN_WIDTH);
    food.y = random(SCREEN_HEIGHT);
    food.r = 255;
    food.g = 255;
    food.b = 255;

    for (int i = 0; i < snake_length; i++) {
        snake[i].x = snake_x - i;
        snake[i].y = snake_y;
        snake[i].r = snake_r;
        snake[i].g = snake_g;
        snake[i].b = snake_b;
    }
}


void snakeGame() {
    joystick_x = 0;
    joystick_y = 0;

    Snake* snake = new Snake[SCREEN_WIDTH * SCREEN_HEIGHT];
    Food food;

    int snake_length = 3;
    int snake_speed = 100;
    int snake_x = 0;
    int snake_y = 0;
    int snake_r = 255;
    int snake_g = 0;
    int snake_b = 0;
    String direction = "right";

    matrix.begin();
    matrix.setTextWrap(false);
    matrix.fillScreen(matrix.Color(0, 0, 0));
    matrix.show();

    randomSeed(analogRead(0));
    food.x = random(SCREEN_WIDTH);
    food.y = random(SCREEN_HEIGHT);
    food.r = 255;
    food.g = 255;
    food.b = 255;

    for (int i = 0; i < snake_length; i++) {
        snake[i].x = snake_x - i;
        snake[i].y = snake_y;
        snake[i].r = snake_r;
        snake[i].g = snake_g;
        snake[i].b = snake_b;
    }
    while (now_state == "snake") {
        buttonState_c = digitalRead(14);
        buttonState_e = digitalRead(34);
        if (BlinkerButtonState_exit == "tap" || buttonState_e == 0){
            BlinkerButtonState_exit = "null";
            matrix.clear();
            delete[] snake;
            now_state = "menu";
            ShowMenu();
        }

        joystick_x = analogRead(adc0);
        joystick_y = analogRead(adc1);

        if ((joystick_x != 0 && joystick_y == 0 && direction != "down") || ((BlinkerY >= 0 && BlinkerY <=5) && direction != "down")) direction = "up";
        else if ((joystick_x != 0 && joystick_y == 8191 && direction != "up") || ((BlinkerY >= 250 && BlinkerY <=255) && direction != "up")) direction = "down";
        else if ((joystick_x == 0 && joystick_y != 0 && direction != "right") || ((BlinkerX >= 250 && BlinkerX <=255) && direction != "right")) direction = "left";
        else if ((joystick_x == 8191 && joystick_y != 0 && direction != "left") || ((BlinkerX >= 0 && BlinkerX <=5) && direction != "left")) direction = "right";

        if (direction == "right") snake_x++;
        else if (direction == "left") snake_x--;
        else if (direction == "up") snake_y--;
        else if (direction == "down") snake_y++;

        if (snake_x < 0 || snake_x >= SCREEN_WIDTH || snake_y < 0 || snake_y >= SCREEN_HEIGHT) {
            matrix.clear();
            matrix.fillScreen(matrix.Color(255,0,0));
            matrix.show();
            delay(1000);
            matrix.clear();
            drawScore();
            delay(1000);
            if (snake_length-3 > 9){
                drawNumber(23,1,(snake_length-3)/10,255,163,177,Brightness);
                drawNumber(28,1,(snake_length-3)%10,255,163,177,Brightness);
            }
            else {
                drawNumber(23,1,snake_length-3,255,163,177,Brightness);
            }
            delay(3000);
            resetGame(snake, food, snake_length, snake_speed, snake_x, snake_y, snake_r, snake_g, snake_b, direction);
        }

        for (int i = 1; i < snake_length; i++) {
            if (snake[i].x == snake_x && snake[i].y == snake_y) {
                matrix.clear();
                matrix.fillScreen(matrix.Color(255,0,0));
                matrix.show();
                delay(1000);
                matrix.clear();
                drawScore();
                delay(1000);
                if (snake_length-3 > 9){
                    drawNumber(23,1,(snake_length-3)/10,255,163,177,Brightness);
                    drawNumber(28,1,(snake_length-3)%10,255,163,177,Brightness);
                }
                else {
                    drawNumber(23,1,snake_length-3,255,163,177,Brightness);
                }
                delay(3000);
                resetGame(snake, food, snake_length, snake_speed, snake_x, snake_y, snake_r, snake_g, snake_b, direction);
            }
        }

        if (snake_x == food.x && snake_y == food.y) {
            snake_length++;
            food.x = random(SCREEN_WIDTH);
            food.y = random(SCREEN_HEIGHT);
        }

        for (int i = snake_length - 1; i > 0; i--) {
            snake[i].x = snake[i - 1].x;
            snake[i].y = snake[i - 1].y;
        }
        snake[0].x = snake_x;
        snake[0].y = snake_y;
        matrix.fillScreen(matrix.Color(0, 0, 0));
        for (int i = 0; i < snake_length; i++) {
            matrix.drawPixel(snake[i].x, snake[i].y, matrix.Color(snake[i].r, snake[i].g, snake[i].b));
        }

        matrix.drawPixel(food.x, food.y, matrix.Color(food.r, food.g, food.b));
        matrix.show();
        delay(snake_speed);
    }
}