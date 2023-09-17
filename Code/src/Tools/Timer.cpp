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

    while (true){
        if (BlinkerButtonState_exit == "tap"){
            BlinkerButtonState_exit = "null";
            matrix.clear();
            now_state = "menu";
            ShowMenu();
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

        if (BlinkerButtonState_confirm == "tap"){
            BlinkerButtonState_confirm = "null";
            timer_index++;
        }

        if ((joystick_x == 0 && joystick_y != 0) || (BlinkerX >= 250 && BlinkerX <=255)){
            if (timer_index == 1){
                if (timer_hour+1 > 99){
                    timer_hour = 0;
                    matrix.clear();
                }
                else{
                    timer_hour++;
                    delay(500);
                    matrix.clear();
                }
            }
            else if (timer_index == 2){
                if (timer_minute+1 == 60){
                    timer_minute = 0;
                    matrix.clear();
                }
                else{
                    timer_minute++;
                    delay(500);
                    matrix.clear();
                }
            }
            else if (timer_index == 3){
                if (timer_second+1 == 60){
                    timer_second = 0;
                    matrix.clear();
                }
                else{
                    timer_second++;
                    delay(500);
                    matrix.clear();
                }
            }
        }
        else if ((joystick_x == 8191 && joystick_y != 0) || (BlinkerX >= 0 && BlinkerX <=5)){
            if (timer_index == 1){
                if (timer_hour-1 < 0){
                    timer_hour = 99;
                    matrix.clear();
                }
                else{
                    timer_hour--;
                    delay(500);
                    matrix.clear();
                }
            }
            else if (timer_index == 2){
                if (timer_minute-1 < 0){
                    timer_minute = 59;
                    matrix.clear();
                }
                else{
                    timer_minute++;
                    delay(500);
                    matrix.clear();
                }
            }
            else if (timer_index == 3){
                if (timer_second-1 < 0){
                    timer_second = 59;
                    matrix.clear();
                }
                else{
                    timer_second++;
                    delay(500);
                    matrix.clear();
                }
            }
        }

        if (timer_index == 4){
            break;
        }
    }
    auto start_time = millis();

    while (true){
        if (BlinkerButtonState_exit == "tap"){
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
        delay(1000);

        if (timer_second == 0 && timer_minute == 0 && timer_hour == 0){
            matrix.clear();
            while (true){
                if (BlinkerButtonState_exit == "tap"){
                    BlinkerButtonState_exit = "null";
                    matrix.clear();
                    now_state = "menu";
                    ShowMenu();
                }
                matrix.clear();
                //显示小时
                drawNumber(2,1,0,r,g,b,Brightness);
                drawNumber(6,1,0,r,g,b,Brightness);
                matrix.drawPixel(10,2,matrix.Color(r,g,b));
                matrix.drawPixel(10,5,matrix.Color(r,g,b));
                //显示分钟
                drawNumber(12,1,0,r,g,b,Brightness);
                drawNumber(16,1,0,r,g,b,Brightness);
                matrix.drawPixel(20,2,matrix.Color(r,g,b));
                matrix.drawPixel(20,5,matrix.Color(r,g,b));
                //显示秒数
                drawNumber(22,1,0,r,g,b,Brightness);
                drawNumber(26,1,0,r,g,b,Brightness);
                matrix.show();
                delay(1500);
            }
        }
    }
}