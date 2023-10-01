//
// Created by jonyl on 2023/9/10.
//
#include "ShowMenu.h"

void ShowMenu(){
    while (now_state == "menu"){
        joystick_x = analogRead(adc0);
        joystick_y = analogRead(adc1);
        if ((joystick_x == 0 && joystick_y != 0) || (BlinkerX >= 0 && BlinkerX <=5)){
            if (menu_index == 1){
                menu_index = 5;
            }
            else {
                menu_index -= 1;
            }
        }

        if ((joystick_x == 8191 && joystick_y != 0) || (BlinkerX >= 250 && BlinkerX <=255)){
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
            }
            else if (menu_index == 2) {
                matrix.clear();
                now_state = "timer";
            }
            else if (menu_index == 3) {
                matrix.clear();
                now_state = "weather";
            }
            else if (menu_index == 4){
                matrix.clear();
                now_state = "snakegame";
            }
            else if (menu_index == 5) {
                matrix.clear();
                now_state = "gif";
            }
        }

        if (now_state == "time"){
            matrix.clear();
            showTime(124,77,255);
        }
        else if (now_state == "timer"){
            matrix.clear();
            Timer();
        }
        else if (now_state == "weather"){
            matrix.clear();
            showWeather();
        }
        else if (now_state == "snakegame"){
            matrix.clear();
            snakeGame();
        }
        else if (now_state == "gif"){
            matrix.clear();
            codeRain();
        }
    }
}