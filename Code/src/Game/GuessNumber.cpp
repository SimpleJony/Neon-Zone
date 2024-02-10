//
// Created by jonyl on 2024/2/9.
//

#include "GuessNumber.h"

void GuessNumber(){
    matrix.clear();
    randomSeed((unsigned)time(nullptr));
    int num_index = 1;
    int randomNum = random(1,1000);
    int retryTime = 0;
    // debug
    Serial.println(randomNum);
    while (now_state == "guessnum") {
        buttonState_c = digitalRead(14);
        buttonState_e = digitalRead(34);
        joystick_x = analogRead(adc0);
        joystick_y = analogRead(adc1);
        if (BlinkerButtonState_exit == "tap" || buttonState_e == 0) {
            BlinkerButtonState_exit = "null";
            matrix.clear();
            now_state = "menu";
            ShowMenu();
        }
        drawNumber(9,2,inputNum_b,255,255,255,Brightness);
        drawNumber(14,2,inputNum_s,255,255,255,Brightness);
        drawNumber(19,2,inputNum_g,255,255,255,Brightness);
        matrix.show();
        if (BlinkerButtonState_confirm == "tap" || buttonState_c == 0){
            BlinkerButtonState_confirm = "null";
            num_index++;
            delay(1000);
        }
        if ((joystick_x == 8191 && joystick_y != 0) || (BlinkerX >= 250 && BlinkerX <= 255)) {
            if (num_index == 1) {
                inputNum_b++;
                if (inputNum_b > 9) {
                    inputNum_b = 0;
                }
                delay(500);
                matrix.clear();
            } else if (num_index == 2) {
                inputNum_s++;
                if (inputNum_s > 9) {
                    inputNum_s = 0;
                }
                delay(500);
                matrix.clear();
            } else if (num_index == 3) {
                inputNum_g++;
                if (inputNum_g > 9) {
                    inputNum_g = 0;
                }
                delay(500);
                matrix.clear();
            }
        } else if ((joystick_x == 0 && joystick_y != 0) || (BlinkerX >= 0 && BlinkerX <= 5)) {
            if (num_index == 1) {
                inputNum_b--;
                if (inputNum_b < 0) {
                    inputNum_b = 9;
                }
                delay(500);
                matrix.clear();
            } else if (num_index == 2) {
                inputNum_s--;
                if (inputNum_s < 0) {
                    inputNum_s = 9;
                }
                delay(500);
                matrix.clear();
            }
            else if (num_index == 3){
                inputNum_g--;
                if (inputNum_g < 0){
                    inputNum_g = 9;
                }
                delay(500);
                matrix.clear();
            }
        }
        if (retryTime == 5){
            matrix.clear();
            drawX();
            delay(1000);
            matrix.clear();
            resetNum(num_index,retryTime,randomNum,inputNum_b,inputNum_s,inputNum_g);
        }
        if (num_index == 4) {
            int finalNum = inputNum_b * 100 + inputNum_s * 10 + inputNum_g;
            if (finalNum < randomNum) {
                matrix.clear();
                matrix.fillScreen(matrix.Color(255, 0, 0));
                matrix.show();
                delay(1000);
                matrix.clear();
                retryTime++;
                num_index = 1;
            } else if (finalNum > randomNum) {
                matrix.clear();
                matrix.fillScreen(matrix.Color(0, 0, 255));
                matrix.show();
                delay(1000);
                matrix.clear();
                retryTime++;
                num_index = 1;
            } else {
                matrix.clear();
                matrix.fillScreen(matrix.Color(0, 255, 0));
                matrix.show();
                delay(1000);
                matrix.clear();
                resetNum(num_index,retryTime,randomNum,inputNum_b,inputNum_s,inputNum_g);
            }
        }
    }
}

void resetNum(int &num_index, int &retryTime, int &randomNum, int &inputNum_b, int &inputNum_s, int &inputNum_g){
    num_index = 1;
    retryTime = 0;
    randomNum = random(1,1000);
    inputNum_b = 0;
    inputNum_s = 0;
    inputNum_g = 0;
}