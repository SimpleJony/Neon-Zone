//
// Created by jonyl on 2023/9/10.
//
#include "ShowMenu.h"

void ShowMenu(){
    while (true){
        joystick_x = analogRead(adc0);
        joystick_y = analogRead(adc1);
        if ((joystick_x == 0 && joystick_y != 0) || BlinkerX == 0){
            if (menu_index == 1){
                menu_index = 5;
            }
            else {
                menu_index -= 1;
            }
        }
        if ((joystick_x == 8191 && joystick_y != 0) || BlinkerX == 255){
            if (menu_index == 5){
                menu_index = 1;
            }
            else {
                menu_index += 1;
            }
        }
        if (menu_index == 1){
            matrix.clear();
            drawTime();
            delay(500);
        }
        if (menu_index == 2){
            matrix.clear();
            drawTimer();
            delay(500);
        }
        if (menu_index == 3){
            matrix.clear();
            drawWeather();
            delay(500);
        }
        if (menu_index == 4){
            matrix.clear();
            drawGame();
            delay(500);
        }
        if (menu_index == 5){
            matrix.clear();
            drawGIF();
            delay(500);
        }

        if (BlinkerButtonState_confirm=="tap"){
            BlinkerButtonState_confirm = "null";
            if (menu_index == 1){
                matrix.clear();
                now_state = "time";
                delay(300);
                showTime(124,77,255);
            }
            else if (menu_index == 2) {
                matrix.clear();
                now_state = "timer";
                delay(300);
                Timer();
            }
            else if (menu_index == 3) {
                matrix.clear();
                now_state = "weather";
                delay(300);
                showWeather();
            }
            else if (menu_index == 4){
                matrix.clear();
                now_state = "snakegame";
                delay(300);
                snakeGame();
            }
            else if (menu_index == 5) {
                matrix.clear();
                now_state = "gif";
                delay(300);
                codeRain();
            }
        }
    }
}