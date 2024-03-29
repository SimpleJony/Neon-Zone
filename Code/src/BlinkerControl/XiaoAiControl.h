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
BlinkerText TextMode("tex-mode");

//函数创建
void joystickController_callback(uint8_t xAxis, uint8_t yAxis);
void miotBright(const String & bright);
void heartbeat();
void Blinker_callback();
void checkNetwork();
void miotMode(uint8_t setMode);

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
    Blinker.attachHeartbeat(heartbeat);
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
        now_state = "snake";
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

void heartbeat(){
    BrightnessControl.print(Brightness);

    if (now_state == "menu") TextMode.print("当前模式: 主页");
    else if (now_state == "info") TextMode.print("当前模式: 信息");
    else if (now_state == "time") TextMode.print("当前模式: 时间");
    else if (now_state == "timer") TextMode.print("当前模式: 计时");
    else if (now_state == "countdown") TextMode.print("当前模式: 倒计时");
    else if (now_state == "weather") TextMode.print("当前模式: 天气");
    else if (now_state == "game") TextMode.print("当前模式: 游戏页面");
    else if (now_state == "snake") TextMode.print("当前模式: 贪吃蛇");
    else if (now_state == "guessnum") TextMode.print("当前模式: 猜数字");
    else if (now_state == "gif") TextMode.print("当前模式: GIF");
    else if (now_state == "set") TextMode.print("当前模式: 设置");
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
