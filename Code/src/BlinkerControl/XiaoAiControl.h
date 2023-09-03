//
// Created by jonyl on 2023/9/3.
//

#ifndef CODE_XIAOAICONTROL_H
#define CODE_XIAOAICONTROL_H
#include <Blinker.h>

bool result;
//Blinker对象创建
BlinkerJoystick Controller("Controller");

//函数创建
void joystick1_callback(uint8_t xAxis, uint8_t yAxis);
void Blinker_callback();
void checkNetwork();

//数据回调函数
void joystick1_callback(uint8_t xAxis, uint8_t yAxis)
{
    checkNetwork();
    if (result){
        BlinkerX = xAxis;
        BlinkerY = yAxis;
    }
    BLINKER_LOG("Joystick1 X axis: ", xAxis);
    BLINKER_LOG("Joystick1 Y axis: ", yAxis);
}

void Blinker_callback(){
    Controller.attach(joystick1_callback);
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
