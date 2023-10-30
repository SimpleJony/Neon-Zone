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
BlinkerSlider BrightnessControl("Brightness-Control");

//函数创建
void joystickController_callback(uint8_t xAxis, uint8_t yAxis);
void miotBright(const String & bright);
void Blinker_callback();
void checkNetwork();
void miotMode(uint8_t setMode);
void miotColor(int32_t color);
bool isPixelOn(int x,int y);

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

void BrightnessControl_callback(int32_t brightness_blinker)
{
    Brightness = brightness_blinker;
    matrix.setBrightness(Brightness);
    BLINKER_LOG("get brightness value: ", brightness_blinker);
}

void Blinker_callback(){
    Controller.attach(joystickController_callback);
    ButtonConfirm.attach(buttonConfirm_callback);
    ButtonExit.attach(buttonExit_callback);
    BrightnessControl.attach(BrightnessControl_callback);
    BlinkerMIOT.attachBrightness(miotBright);
    BlinkerMIOT.attachMode(miotMode);
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

void miotMode(uint8_t setMode)
{
    BLINKER_LOG("need set mode: ", setMode);

    if (setMode == BLINKER_CMD_MIOT_DAY) {
        now_state = "info";
        Blinker.delay(1000);
        now_state = "time";
    }
    else if (setMode == BLINKER_CMD_MIOT_NIGHT) {
        now_state = "info";
        Blinker.delay(1000);
        now_state = "timer";
    }
    else if (setMode == BLINKER_CMD_MIOT_COLOR) {
        now_state = "info";
        Blinker.delay(1000);
        now_state = "weather";
    }
    else if (setMode == BLINKER_CMD_MIOT_WARMTH) {
        now_state = "snakegame";
    }
    else if (setMode == BLINKER_CMD_MIOT_TV) {
        now_state = "gif";
    }
    else if (setMode == BLINKER_CMD_MIOT_READING) {
        now_state = "menu";
        return;
    }
    else if (setMode == BLINKER_CMD_MIOT_COMPUTER) {
        now_state = "setting";
    }

    BlinkerMIOT.mode(setMode);
    BlinkerMIOT.print();
}

void miotColor(int32_t color){
    uint8_t colorR = color >> 16 & 0xFF;
    uint8_t colorG = color >> 8 & 0xFF;
    uint8_t colorB = color & 0xFF;
    BLINKER_LOG("Set color to: r=", colorR, ",g= ", colorG, ", b=", colorB);
    for (int i=0;i<32;i++){
        for (int j=0;j<8;j++){
            if (isPixelOn(i,j)){
                matrix.setPixelColor(j*32+i,matrix.Color(colorR,colorG,colorB));
            }
        }
    }
    matrix.show();
    BlinkerMIOT.color(color);
    BlinkerMIOT.print();
}

bool isPixelOn(int x,int y){
    uint16_t color = matrix.getPixelColor(y*32+x);
    return color != 0;
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
