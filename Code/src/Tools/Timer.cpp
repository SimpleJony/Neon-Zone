//
// Created by jonyl on 2023/9/16.
//
#include "Timer.h"

void Timer(){
    int timer_hour = 0;
    int timer_minute = 0;
    int timer_second = 0;
    int r = 124;
    int g = 77;
    int b = 255;
    int timer_index = 1;

    while (now_state == "timer"){
        int buttonState_c = digitalRead(14);
        int buttonState_e = digitalRead(16);
        joystick_x = analogRead(adc0);
        joystick_y = analogRead(adc1);
        if (BlinkerButtonState_exit == "tap" || buttonState_e == 0){
            BlinkerButtonState_exit = "null";
            matrix.clear();
            now_state = "info";
            ShowInfo();
        }
        //显示小时
        drawNumber(2,1,timer_hour / 10,r,g,b,Brightness);
        drawNumber(6,1,timer_hour % 10,r,g,b,Brightness);
        matrix.drawPixel(10,2,matrix.Color(r,g,b));
        matrix.drawPixel(10,5,matrix.Color(r,g,b));
        //显示分钟
        drawNumber(12,1,(timer_minute / 10),r,g,b,Brightness);
        drawNumber(16,1,(timer_minute % 10),r,g,b,Brightness);
        matrix.drawPixel(20,2,matrix.Color(r,g,b));
        matrix.drawPixel(20,5,matrix.Color(r,g,b));
        //显示秒数
        drawNumber(22,1,(timer_second / 10),r,g,b,Brightness);
        drawNumber(26,1,(timer_second % 10),r,g,b,Brightness);
        matrix.show();

        if (BlinkerButtonState_confirm == "tap" || buttonState_c == 0){
            BlinkerButtonState_confirm = "null";
            timer_index++;
        }

        if ((joystick_x == 8191 && joystick_y != 0) || (BlinkerX >= 250 && BlinkerX <= 255)) {
            if (timer_index == 1) {
                timer_hour++;
                if (timer_hour > 99) {
                    timer_hour = 0;
                }
                delay(500);
                matrix.clear();
            } else if (timer_index == 2) {
                timer_minute++;
                if (timer_minute > 59) {
                    timer_minute = 0;
                }
                delay(500);
                matrix.clear();
            } else if (timer_index == 3) {
                timer_second++;
                if (timer_second > 59) {
                    timer_second = 0;
                }
                delay(500);
                matrix.clear();
            }
        } else if ((joystick_x == 0 && joystick_y != 0) || (BlinkerX >= 0 && BlinkerX <= 5)) {
            if (timer_index == 1) {
                timer_hour--;
                if (timer_hour < 0) {
                    timer_hour = 99;
                }
                delay(500);
                matrix.clear();
            } else if (timer_index == 2) {
                timer_minute--;
                if (timer_minute < 0) {
                    timer_minute = 59;
                }
                delay(500);
                matrix.clear();
            } else if (timer_index == 3) {
                timer_second--;
                if (timer_second < 0) {
                    timer_second = 59;
                }
                delay(500);
                matrix.clear();
            }
        }

        if (timer_index == 4){
            break;
        }
    }
    auto start_time = millis();

    while (now_state == "timer"){
        int buttonState_c = digitalRead(14);
        int buttonState_e = digitalRead(16);
        if (BlinkerButtonState_exit == "tap" || buttonState_e == 0){
            BlinkerButtonState_exit = "null";
            matrix.clear();
            now_state = "menu";
            ShowMenu();
        }
        if (millis() - start_time > 1000){
            start_time = millis();
            timer_second--;
            if (timer_second < 0 && (timer_minute > 0 || timer_hour > 0)){
                timer_second = 59;
                timer_minute--;
                if (timer_minute < 0){
                    timer_minute = 59;
                    timer_hour--;
                }
            }
        }
        matrix.clear();
        //显示小时
        drawNumber(2,1,timer_hour / 10,255,255,255,Brightness);
        drawNumber(6,1,timer_hour % 10,255,255,255,Brightness);
        matrix.drawPixel(10,2,matrix.Color(255,255,255));
        matrix.drawPixel(10,5,matrix.Color(255,255,255));
        //显示分钟
        drawNumber(12,1,(timer_minute / 10),255,255,255,Brightness);
        drawNumber(16,1,(timer_minute % 10),255,255,255,Brightness);
        matrix.drawPixel(20,2,matrix.Color(255,255,255));
        matrix.drawPixel(20,5,matrix.Color(255,255,255));
        //显示秒数
        drawNumber(22,1,(timer_second / 10),255,255,255,Brightness);
        drawNumber(26,1,(timer_second % 10),255,255,255,Brightness);
        matrix.show();
        delay(1000);

        if (timer_second == 0 && timer_minute == 0 && timer_hour == 0){
            matrix.clear();
            while (now_state == "timer"){
                int buttonState_c = digitalRead(14);
                int buttonState_e = digitalRead(16);
                if (BlinkerButtonState_exit == "tap" || buttonState_e == 0){
                    BlinkerButtonState_exit = "null";
                    matrix.clear();
                    now_state = "menu";
                    ShowMenu();
                }
                matrix.clear();
                //显示小时
                drawNumber(2,1,0,255,0,0,Brightness);
                drawNumber(6,1,0,255,0,0,Brightness);
                matrix.drawPixel(10,2,matrix.Color(255,0,0));
                matrix.drawPixel(10,5,matrix.Color(255,0,0));
                //显示分钟
                drawNumber(12,1,0,255,0,0,Brightness);
                drawNumber(16,1,0,255,0,0,Brightness);
                matrix.drawPixel(20,2,matrix.Color(255,0,0));
                matrix.drawPixel(20,5,matrix.Color(255,0,0));
                //显示秒数
                drawNumber(22,1,0,255,0,0,Brightness);
                drawNumber(26,1,0,255,0,0,Brightness);
                matrix.show();
                delay(1500);
            }
        }
    }
}