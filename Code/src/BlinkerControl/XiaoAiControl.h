//
// Created by jonyl on 2023/9/3.
//

#ifndef CODE_XIAOAICONTROL_H
#define CODE_XIAOAICONTROL_H
#include <Blinker.h>
#include "Draw/ShowThings.h"

bool result;
//Blinker对象创建
BlinkerJoystick Controller("Controller");
BlinkerButton ButtonConfirm("btn-confirm");
BlinkerButton ButtonExit("btn-exit");

//函数创建
void joystickController_callback(uint8_t xAxis, uint8_t yAxis);
void miotBright(const String & bright);
void Blinker_callback();
void checkNetwork();

//数据回调函数
void joystickController_callback(uint8_t xAxis, uint8_t yAxis)
{
    checkNetwork();
    if (result){
        BlinkerX = xAxis;
        BlinkerY = yAxis;
    }
    BLINKER_LOG("Joystick1 X axis: ", xAxis);
    BLINKER_LOG("Joystick1 Y axis: ", yAxis);
}

void buttonConfirm_callback(const String &state)
{
    BlinkerButtonState_confirm = state;
    BLINKER_LOG("Confirm button state: ", BlinkerButtonState_confirm);
    delay(100);
    BLINKER_LOG("Now state: ", now_state);
}
void buttonExit_callback(const String &state)
{
    BlinkerButtonState_exit = state;
    BLINKER_LOG("Exit button state: ", BlinkerButtonState_exit);
    delay(100);
    BLINKER_LOG("Now state: ", now_state);
}


void Blinker_callback(){
    Controller.attach(joystickController_callback);
    ButtonConfirm.attach(buttonConfirm_callback);
    ButtonExit.attach(buttonExit_callback);
    BlinkerMIOT.attachBrightness(miotBright);
}

void miotBright(const String & bright)
{
    BLINKER_LOG("need set brightness: ", bright);
    uint8_t colorW = bright.toInt();
    Brightness = colorW*15/10+105;
    BLINKER_LOG("now set brightness: ", colorW);
    matrix.setBrightness(Brightness);
    BlinkerMIOT.brightness(colorW);
    BlinkerMIOT.print();
}

void checkNetwork(){
    int count = 15;
    while (count--) {
        result = Blinker.connected();
        if (result) {
            break;
        }
        delay(1000);
    }
}

#endif //CODE_XIAOAICONTROL_H
