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
                menu_index = 4;
            }
            else {
                menu_index -= 1;
            }
        }

        if ((joystick_x == 8191 && joystick_y != 0) || (BlinkerX >= 250 && BlinkerX <=255)){
            if (menu_index == 4){
                menu_index = 1;
            }
            else {
                menu_index += 1;
            }
        }

        if (menu_index == 1){
            matrix.clear();
            drawInfo();
            delay(500);
        }
        if (menu_index == 2){
            matrix.clear();
            drawGame();
            delay(500);
        }
        if (menu_index == 3){
            matrix.clear();
            drawGIF();
            delay(500);
        }
        if (menu_index == 4){
            matrix.clear();
            drawSet();
            delay(500);
        }

        if (BlinkerButtonState_confirm=="tap"){
            BlinkerButtonState_confirm = "null";
            if (menu_index == 1){
                matrix.clear();
                now_state = "info";
            }
            else if (menu_index == 2){
                matrix.clear();
                now_state = "snakegame";
            }
            else if (menu_index == 3) {
                matrix.clear();
                now_state = "gif";
            }
            else if (menu_index == 4){
                matrix.clear();
                now_state = "setting";
            }
        }

        if (now_state == "info"){
            matrix.clear();
            ShowInfo();
        }
        else if (now_state == "snakegame"){
            matrix.clear();
            snakeGame();
        }
        else if (now_state == "gif"){
            matrix.clear();
            codeRain();
        }
        else if (now_state == "setting"){
            matrix.clear();
            ShowSet();
        }
    }
}

void ShowInfo(){
    while (now_state == "info"){
        joystick_x = analogRead(adc0);
        joystick_y = analogRead(adc1);
        if (BlinkerButtonState_exit == "tap"){
            BlinkerButtonState_exit = "null";
            matrix.clear();
            now_state = "menu";
            ShowMenu();
        }
        if ((joystick_x == 0 && joystick_y != 0) || (BlinkerX >= 0 && BlinkerX <=5)){
            if (info_index == 1){
                info_index = 3;
            }
            else {
                info_index -= 1;
            }
        }

        if ((joystick_x == 8191 && joystick_y != 0) || (BlinkerX >= 250 && BlinkerX <=255)){
            if (info_index == 3){
                info_index = 1;
            }
            else {
                info_index += 1;
            }
        }

        if (info_index == 1){
            matrix.clear();
            drawTime();
            delay(500);
        }
        if (info_index == 2){
            matrix.clear();
            drawTimer();
            delay(500);
        }
        if (info_index == 3){
            matrix.clear();
            drawWeather();
            delay(500);
        }

        if (BlinkerButtonState_confirm=="tap"){
            BlinkerButtonState_confirm = "null";
            if (info_index == 1){
                matrix.clear();
                now_state = "time";
            }
            else if (info_index == 2){
                matrix.clear();
                now_state = "timer";
            }
            else if (info_index == 3) {
                matrix.clear();
                now_state = "weather";
            }
        }

        if (now_state == "time"){
            matrix.clear();
            showTime(0,183,239);
        }
        else if (now_state == "timer"){
            matrix.clear();
            Timer();
        }
        else if (now_state == "weather"){
            matrix.clear();
            showWeather();
        }
    }
}

void ShowSet(){
    while (now_state == "setting"){
        joystick_x = analogRead(adc0);
        joystick_y = analogRead(adc1);
        if (BlinkerButtonState_exit == "tap"){
            BlinkerButtonState_exit = "null";
            matrix.clear();
            now_state = "menu";
            ShowMenu();
        }
        drawProgressBar();
        adjustBrightness();
    }
}