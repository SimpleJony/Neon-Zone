//
// Created by jonyl on 2023/8/18.
//

#ifndef CODE_DRAWTHINGS_H
#define CODE_DRAWTHINGS_H
#include <Arduino.h>
#include <Adafruit_NeoMatrix.h>
#include "config.h"

void drawNumber(int x, int y, int num, int red, int green, int blue, int brightness);
void drawWifi();
void drawSuccess();
void drawGIF();
void drawTime();
void drawTimer();
void drawGame();
void drawScore();
void drawSunny();
void drawCloud();
void drawRain();
void drawSnow();
void drawUnknown();
void drawProgressBar();
void adjustBrightness();

/*
    DrawNumber函数实现，用来在屏幕上显示数字
    Date: 2023.6.22
    Author: Jony
*/
void drawNumber(int x, int y, int num, int red, int green, int blue, int brightness) {
    if (num == 0) {
        for (int h = 0; h <= 5; h++) {
            matrix.drawPixel(x, y + h, matrix.Color(red, green, blue));
            matrix.drawPixel(x + 2, y + h, matrix.Color(red, green, blue));
        }
        matrix.drawPixel(x + 1, y, matrix.Color(red, green, blue));
        matrix.drawPixel(x + 1, y + 5, matrix.Color(red, green, blue));
    }
    else if (num == 1) {
        for (int h = 0; h <= 5; h++) {
            matrix.drawPixel(x + 1, y + h, matrix.Color(red, green, blue));
        }
        matrix.drawPixel(x, y + 1, matrix.Color(red, green, blue));
        matrix.drawPixel(x, y + 5, matrix.Color(red, green, blue));
        matrix.drawPixel(x + 2, y + 5, matrix.Color(red, green, blue));
    }
    else if (num==2){
        for (int h=0;h<=2;h++){
            matrix.drawPixel(x+h, y,matrix.Color(red, green, blue));
            matrix.drawPixel(x+h, y+2,matrix.Color(red, green, blue));
            matrix.drawPixel(x+h, y+5,matrix.Color(red, green, blue));
        }
        matrix.drawPixel(x+2, y+1,matrix.Color(red, green, blue));
        matrix.drawPixel(x, y+3,matrix.Color(red, green, blue));
        matrix.drawPixel(x, y+4,matrix.Color(red, green, blue));
    }
    else if (num == 3){
        for (int h=0;h<=2;h++){
            matrix.drawPixel(x+h, y,matrix.Color(red, green, blue));
            matrix.drawPixel(x+h, y+2,matrix.Color(red, green, blue));
            matrix.drawPixel(x+h, y+5,matrix.Color(red, green, blue));
        }
        matrix.drawPixel(x+2, y+1,matrix.Color(red, green, blue));
        matrix.drawPixel(x+2, y+3,matrix.Color(red, green, blue));
        matrix.drawPixel(x+2, y+4,matrix.Color(red, green, blue));
    }
    else if (num == 4){
        for (int h=0;h<=3;h++){
            matrix.drawPixel(x, y+h,matrix.Color(red, green, blue));
        }
        for (int i=0;i<=5;i++){
            matrix.drawPixel(x+2, y+i,matrix.Color(red, green, blue));
        }
        matrix.drawPixel(x+1, y+3,matrix.Color(red, green, blue));
    }
    else if (num == 5) {
        for (int w = 0; w <= 2; w++) {
            matrix.drawPixel(x + w, y, matrix.Color(red, green, blue));
            matrix.drawPixel(x + w, y + 3, matrix.Color(red, green, blue));
            matrix.drawPixel(x + w, y + 5, matrix.Color(red, green, blue));
        }
        matrix.drawPixel(x, y + 1, matrix.Color(red, green, blue));
        matrix.drawPixel(x, y + 2, matrix.Color(red, green, blue));
        matrix.drawPixel(x + 2, y + 4, matrix.Color(red, green, blue));
    }
    else if (num == 6) {
        for (int w = 0; w <= 2; w++) {
            matrix.drawPixel(x + w, y, matrix.Color(red, green, blue));
            matrix.drawPixel(x + w, y + 3, matrix.Color(red, green, blue));
            matrix.drawPixel(x + w, y + 5, matrix.Color(red, green, blue));
        }
        matrix.drawPixel(x, y + 1, matrix.Color(red, green, blue));
        matrix.drawPixel(x, y + 2, matrix.Color(red, green, blue));
        matrix.drawPixel(x, y + 4, matrix.Color(red, green, blue));
        matrix.drawPixel(x + 2, y + 4, matrix.Color(red, green, blue));
    }
    else if (num == 7){
        for (int h=0;h<=2;h++){
            matrix.drawPixel(x + h, y, matrix.Color(red, green, blue));
        }
        for (int i=0;i<=5;i++){
            matrix.drawPixel(x + 2, y + i, matrix.Color(red, green, blue));
        }
    }
    else if (num == 8){
        for (int h = 0; h <= 5; h++) {
            matrix.drawPixel(x, y + h, matrix.Color(red, green, blue));
            matrix.drawPixel(x + 2, y + h, matrix.Color(red, green, blue));
        }
        matrix.drawPixel(x + 1, y, matrix.Color(red, green, blue));
        matrix.drawPixel(x + 1, y + 5, matrix.Color(red, green, blue));
        matrix.drawPixel(x + 1, y + 3, matrix.Color(red, green, blue));
    }
    else if (num == 9) {
        for (int w = 0; w <= 2; w++) {
            matrix.drawPixel(x + w, y, matrix.Color(red, green, blue));
            matrix.drawPixel(x + w, y + 3, matrix.Color(red, green, blue));
            matrix.drawPixel(x + w, y + 5, matrix.Color(red, green, blue));
        }
        matrix.drawPixel(x, y + 1, matrix.Color(red, green, blue));
        matrix.drawPixel(x, y + 2, matrix.Color(red, green, blue));
        matrix.drawPixel(x + 2, y + 1, matrix.Color(red, green, blue));
        matrix.drawPixel(x + 2, y + 2, matrix.Color(red, green, blue));
        matrix.drawPixel(x + 2, y + 4, matrix.Color(red, green, blue));

    }
    matrix.setBrightness(brightness);
    matrix.show();
}

/*
  drawWifi函数实现，用来在屏幕上显示"WIFI"字样
  Date: 2023.6.24
  Author: Jony
*/
void drawWifi(){
    // draw "W"
    for (int i=1;i<=6;i++){
        matrix.drawPixel(3,i,matrix.Color(0,183,239));
        matrix.drawPixel(7,i,matrix.Color(0,183,239));
    }
    for (int k=2;k<=5;k++){
        matrix.drawPixel(5,k,matrix.Color(0,183,239));
    }
    for (int j=4;j<=6;j++){
        matrix.drawPixel(j,6,matrix.Color(0,183,239));
    }
    // draw "I"
    for (int i1=9;i1<=11;i1++){
        matrix.drawPixel(i1,1,matrix.Color(0,183,239));
        matrix.drawPixel(i1,6,matrix.Color(0,183,239));
    }
    for (int j1=2;j1<=5;j1++){
        matrix.drawPixel(10,j1,matrix.Color(0,183,239));
    }
    // draw "F"
    for (int j2=1;j2<=6;j2++){
        matrix.drawPixel(13,j2,matrix.Color(0,183,239));
    }
    for (int i2=14;i2<=15;i2++){
        matrix.drawPixel(i2,1,matrix.Color(0,183,239));
        matrix.drawPixel(i2,4,matrix.Color(0,183,239));
    }
    // draw "I"
    for (int i3=17;i3<=19;i3++){
        matrix.drawPixel(i3,1,matrix.Color(0,183,239));
        matrix.drawPixel(i3,6,matrix.Color(0,183,239));
    }
    for (int j3=2;j3<=5;j3++){
        matrix.drawPixel(18,j3,matrix.Color(0,183,239));
    }
    matrix.show();
}

/*
  drawSuccess函数实现，用来在屏幕上显示勾
  Date: 2023.6.24
  Author: Jony
*/
void drawSuccess(){
    matrix.drawPixel(22,3,matrix.Color(102,255,0));
    matrix.drawPixel(23,4,matrix.Color(102,255,0));
    matrix.drawPixel(24,5,matrix.Color(102,255,0));
    matrix.drawPixel(25,6,matrix.Color(102,255,0));
    matrix.drawPixel(26,5,matrix.Color(102,255,0));
    matrix.drawPixel(27,4,matrix.Color(102,255,0));
    matrix.drawPixel(28,3,matrix.Color(102,255,0));
    matrix.drawPixel(29,2,matrix.Color(102,255,0));
    matrix.drawPixel(30,1,matrix.Color(102,255,0));
    matrix.show();
}

/*
    drawGIF函数实现，用来在灯矩阵上画出"GIF"字样
    Date: 2023.6.25
    Author: Jony
*/
void drawGIF(){
    // draw "G"
    for (int i=8;i<=12;i++){
        matrix.drawPixel(i,1,matrix.Color(255,163,177));
        matrix.drawPixel(i,6,matrix.Color(255,163,177));
    }
    for (int j=2;j<=5;j++){
        matrix.drawPixel(8,j,matrix.Color(255,163,177));
    }
    matrix.drawPixel(12,5,matrix.Color(255,163,177));
    matrix.drawPixel(12,4,matrix.Color(255,163,177));
    matrix.drawPixel(11,4,matrix.Color(255,163,177));
    // draw "I"
    for (int i1=14;i1<=18;i1++){
        matrix.drawPixel(i1,1,matrix.Color(255,163,177));
        matrix.drawPixel(i1,6,matrix.Color(255,163,177));
    }
    for (int j1=2;j1<=5;j1++){
        matrix.drawPixel(16,j1,matrix.Color(255,163,177));
    }
    // draw "F"
    for (int j2=1;j2<=6;j2++){
        matrix.drawPixel(20,j2,matrix.Color(255,163,177));
    }
    for (int i2=21;i2<=23;i2++){
        matrix.drawPixel(i2,1,matrix.Color(255,163,177));
        matrix.drawPixel(i2,4,matrix.Color(255,163,177));
    }
    matrix.show();
}

/*
    drawTimer函数实现，用来在灯矩阵上画出"TIMER"字样
    Date: 2023.6.25
    Author: Jony
*/
// TODO: Need improve ,missing original file
void drawTimer(){
    // Draw "T"
    for (int i=1;i<=5;i++){
        matrix.drawPixel(i,1,matrix.Color(255,163,177));
    }
    for (int j=2;j<=6;j++){
        matrix.drawPixel(3,j,matrix.Color(255,163,177));
    }
    // Draw "I"
    for (int i1=7;i1<=9;i1++){
        matrix.drawPixel(i1,1,matrix.Color(255,163,177));
    }
    for (int j1=2;j1<=6;j1++){
        matrix.drawPixel(8,j1,matrix.Color(255,163,177));
    }
    for (int k1=7;k1<=9;k1++){
        matrix.drawPixel(k1,6,matrix.Color(255,163,177));
    }
    // draw "M"
    for (int i2=11;i2<=12;i2++){
        matrix.drawPixel(i2,1,matrix.Color(255,163,177));
    }
    for (int j2=2;j2<=6;j2++){
        matrix.drawPixel(11,j2,matrix.Color(255,163,177));
    }
    matrix.drawPixel(13,2,matrix.Color(255,163,177));
    matrix.drawPixel(14,3,matrix.Color(255,163,177));
    matrix.drawPixel(15,2,matrix.Color(255,163,177));
    for (int k2=16;k2<=17;k2++){
        matrix.drawPixel(k2,1,matrix.Color(255,163,177));
    }
    for (int l2=2;l2<=6;l2++){
        matrix.drawPixel(17,l2,matrix.Color(255,163,177));
    }
    // draw "E"
    for (int i3=19;i3<=22;i3++){
        matrix.drawPixel(i3,1,matrix.Color(255,163,177));
    }
    for (int j3=2;j3<=6;j3++){
        matrix.drawPixel(19,j3,matrix.Color(255,163,177));
    }
    for (int k3=20;k3<=22;k3++){
        matrix.drawPixel(k3,4,matrix.Color(255,163,177));
    }
    for (int l3=20;l3<=22;l3++){
        matrix.drawPixel(l3,6,matrix.Color(255,163,177));
    }
    // Draw "R"
    for (int i4=24;i4<=27;i4++){
        matrix.drawPixel(i4,1,matrix.Color(255,163,177));
    }
    for (int j4=2;j4<=6;j4++) {
        matrix.drawPixel(24, j4, matrix.Color(255, 163, 177));
    }
    for (int k4=25;k4<=27;k4++){
        matrix.drawPixel(k4,4,matrix.Color(255,163,177));
    }
    matrix.drawPixel(26,5,matrix.Color(255,163,177));
    matrix.drawPixel(27,6,matrix.Color(255,163,177));
    matrix.drawPixel(27,2,matrix.Color(255,163,177));
    matrix.drawPixel(27,3,matrix.Color(255,163,177));
    matrix.show();
}
// TODO: This function comes from drawTimer(),need improve
void drawTime() {
    // Draw "T"
    for (int i = 1; i <= 5; i++) {
        matrix.drawPixel(i, 1, matrix.Color(255, 163, 177));
    }
    for (int j = 2; j <= 6; j++) {
        matrix.drawPixel(3, j, matrix.Color(255, 163, 177));
    }
    // Draw "I"
    for (int i1 = 7; i1 <= 9; i1++) {
        matrix.drawPixel(i1, 1, matrix.Color(255, 163, 177));
    }
    for (int j1 = 2; j1 <= 6; j1++) {
        matrix.drawPixel(8, j1, matrix.Color(255, 163, 177));
    }
    for (int k1 = 7; k1 <= 9; k1++) {
        matrix.drawPixel(k1, 6, matrix.Color(255, 163, 177));
    }
    // draw "M"
    for (int i2 = 11; i2 <= 12; i2++) {
        matrix.drawPixel(i2, 1, matrix.Color(255, 163, 177));
    }
    for (int j2 = 2; j2 <= 6; j2++) {
        matrix.drawPixel(11, j2, matrix.Color(255, 163, 177));
    }
    matrix.drawPixel(13, 2, matrix.Color(255, 163, 177));
    matrix.drawPixel(14, 3, matrix.Color(255, 163, 177));
    matrix.drawPixel(15, 2, matrix.Color(255, 163, 177));
    for (int k2 = 16; k2 <= 17; k2++) {
        matrix.drawPixel(k2, 1, matrix.Color(255, 163, 177));
    }
    for (int l2 = 2; l2 <= 6; l2++) {
        matrix.drawPixel(17, l2, matrix.Color(255, 163, 177));
    }
    // draw "E"
    for (int i3 = 19; i3 <= 22; i3++) {
        matrix.drawPixel(i3, 1, matrix.Color(255, 163, 177));
    }
    for (int j3 = 2; j3 <= 6; j3++) {
        matrix.drawPixel(19, j3, matrix.Color(255, 163, 177));
    }
    for (int k3 = 20; k3 <= 22; k3++) {
        matrix.drawPixel(k3, 4, matrix.Color(255, 163, 177));
    }
    for (int l3 = 20; l3 <= 22; l3++) {
        matrix.drawPixel(l3, 6, matrix.Color(255, 163, 177));
    }
    matrix.show();
}

void drawGame(){
    // draw "G"
    for (int i=3;i<=7;i++){
        matrix.drawPixel(i,1,matrix.Color(255,163,177));
    }
    for (int j=2;j<=6;j++){
        matrix.drawPixel(3,j,matrix.Color(255,163,177));
    }
    for (int k=4;k<=7;k++){
        matrix.drawPixel(k,6,matrix.Color(255,163,177));
    }
    // draw "A"
    matrix.drawPixel(11,1,matrix.Color(255,163,177));
    matrix.drawPixel(10,2,matrix.Color(255,163,177));
    matrix.drawPixel(12,2,matrix.Color(255,163,177));
    for (int i1=3;i1<=6;i1++){
        matrix.drawPixel(9,i1,matrix.Color(255,163,177));
        matrix.drawPixel(13,i1,matrix.Color(255,163,177));
    }
    for (int j1=10;j1<=12;j1++){
        matrix.drawPixel(j1,5,matrix.Color(255,163,177));
    }
    // draw "M"
    for (int i2=1;i2<=6;i2++){
        matrix.drawPixel(15,i2,matrix.Color(255,163,177));
        matrix.drawPixel(21,i2,matrix.Color(255,163,177));
    }
    matrix.drawPixel(16,1,matrix.Color(255,163,177));
    matrix.drawPixel(20,1,matrix.Color(255,163,177));
    matrix.drawPixel(17,2,matrix.Color(255,163,177));
    matrix.drawPixel(19,2,matrix.Color(255,163,177));
    matrix.drawPixel(18,3,matrix.Color(255,163,177));
    // draw "E"
    for (int i3=1;i3<=6;i3++){
        matrix.drawPixel(23,i3,matrix.Color(255,163,177));
    }
    for (int j3=24;j3<=27;j3++){
        matrix.drawPixel(j3,1,matrix.Color(255,163,177));
        matrix.drawPixel(j3,4,matrix.Color(255,163,177));
        matrix.drawPixel(j3,6,matrix.Color(255,163,177));
    }
    matrix.show();
}

void drawScore(){
    for (int i=1;i<=4;i++){
        matrix.drawPixel(i,1,matrix.Color(255,163,177));
        matrix.drawPixel(i,3,matrix.Color(255,163,177));
        matrix.drawPixel(i,6,matrix.Color(255,163,177));
    }
    matrix.drawPixel(1,2,matrix.Color(255,163,177));
    matrix.drawPixel(4,4,matrix.Color(255,163,177));
    matrix.drawPixel(4,5,matrix.Color(255,163,177));

    for (int j=6;j<=9;j++){
        matrix.drawPixel(j,1,matrix.Color(255,163,177));
        matrix.drawPixel(j,6,matrix.Color(255,163,177));
    }
    for (int k=2;k<=5;k++){
        matrix.drawPixel(6,k,matrix.Color(255,163,177));
    }

    for (int a=1;a<=6;a++){
        matrix.drawPixel(11,a,matrix.Color(255,163,177));
        matrix.drawPixel(14,a,matrix.Color(255,163,177));
    }
    for (int b=12;b<=13;b++){
        matrix.drawPixel(b,1,matrix.Color(255,163,177));
        matrix.drawPixel(b,6,matrix.Color(255,163,177));
    }

    for (int c=16;c<=19;c++){
        matrix.drawPixel(c,1,matrix.Color(255,163,177));
        matrix.drawPixel(c,4,matrix.Color(255,163,177));
    }
    for (int d=2;d<=3;d++){
        matrix.drawPixel(16,d,matrix.Color(255,163,177));
        matrix.drawPixel(19,d,matrix.Color(255,163,177));
    }
    matrix.drawPixel(16,5,matrix.Color(255,163,177));
    matrix.drawPixel(16,6,matrix.Color(255,163,177));
    matrix.drawPixel(18,5,matrix.Color(255,163,177));
    matrix.drawPixel(19,6,matrix.Color(255,163,177));

    matrix.drawPixel(21,2,matrix.Color(255,163,177));
    matrix.drawPixel(21,5,matrix.Color(255,163,177));
    matrix.show();
}

void drawSunny(){
    for (int i=4;i<=6;i++){
        matrix.drawPixel(i,2,matrix.Color(255,242,0));
        matrix.drawPixel(i,4,matrix.Color(255,242,0));
    }
    matrix.drawPixel(4,3,matrix.Color(255,242,0));
    matrix.drawPixel(6,3,matrix.Color(255,242,0));
    matrix.drawPixel(5,0,matrix.Color(255,242,0));
    matrix.drawPixel(3,1,matrix.Color(255,242,0));
    matrix.drawPixel(7,1,matrix.Color(255,242,0));
    matrix.drawPixel(2,3,matrix.Color(255,242,0));
    matrix.drawPixel(8,3,matrix.Color(255,242,0));
    matrix.drawPixel(3,5,matrix.Color(255,242,0));
    matrix.drawPixel(7,5,matrix.Color(255,242,0));
    matrix.drawPixel(5,6,matrix.Color(255,242,0));
    matrix.show();
}

void drawCloud(){
    for (int i=1;i<=8;i++){
        matrix.drawPixel(i,5,matrix.Color(118,215,234));
    }
    matrix.drawPixel(1,4,matrix.Color(118,215,234));
    matrix.drawPixel(8,4,matrix.Color(118,215,234));
    matrix.drawPixel(2,3,matrix.Color(118,215,234));
    matrix.drawPixel(4,2,matrix.Color(118,215,234));
    matrix.drawPixel(3,2,matrix.Color(118,215,234));
    matrix.drawPixel(5,1,matrix.Color(118,215,234));
    matrix.drawPixel(6,1,matrix.Color(118,215,234));
    matrix.drawPixel(7,2,matrix.Color(118,215,234));
    matrix.drawPixel(7,3,matrix.Color(118,215,234));
    matrix.show();
}

void drawRain(){
    matrix.drawPixel(2,3,matrix.Color(127,127,127));
    matrix.drawPixel(3,3,matrix.Color(127,127,127));
    matrix.drawPixel(4,3,matrix.Color(127,127,127));
    matrix.drawPixel(8,3,matrix.Color(127,127,127));
    matrix.drawPixel(3,2,matrix.Color(127,127,127));
    matrix.drawPixel(6,2,matrix.Color(127,127,127));
    matrix.drawPixel(7,2,matrix.Color(127,127,127));
    matrix.drawPixel(4,1,matrix.Color(127,127,127));
    matrix.drawPixel(5,1,matrix.Color(127,127,127));
    matrix.drawPixel(6,1,matrix.Color(127,127,127));
    matrix.drawPixel(7,4,matrix.Color(127,127,127));
    matrix.drawPixel(7,5,matrix.Color(127,127,127));
    matrix.drawPixel(7,6,matrix.Color(127,127,127));
    matrix.drawPixel(5,4,matrix.Color(127,127,127));
    matrix.drawPixel(5,5,matrix.Color(127,127,127));
    matrix.drawPixel(3,5,matrix.Color(127,127,127));
    matrix.drawPixel(3,6,matrix.Color(127,127,127));
    matrix.show();
}

void drawSnow(){
    matrix.drawPixel(2,3,matrix.Color(255,255,255));
    matrix.drawPixel(3,3,matrix.Color(255,255,255));
    matrix.drawPixel(4,3,matrix.Color(255,255,255));
    matrix.drawPixel(5,3,matrix.Color(255,255,255));
    matrix.drawPixel(8,3,matrix.Color(255,255,255));
    matrix.drawPixel(9,3,matrix.Color(255,255,255));
    matrix.drawPixel(3,2,matrix.Color(255,255,255));
    matrix.drawPixel(7,2,matrix.Color(255,255,255));
    matrix.drawPixel(8,2,matrix.Color(255,255,255));
    matrix.drawPixel(4,1,matrix.Color(255,255,255));
    matrix.drawPixel(5,1,matrix.Color(255,255,255));
    matrix.drawPixel(6,1,matrix.Color(255,255,255));
    matrix.drawPixel(7,1,matrix.Color(255,255,255));
    matrix.drawPixel(6,4,matrix.Color(255,255,255));
    matrix.drawPixel(3,5,matrix.Color(255,255,255));
    matrix.drawPixel(5,5,matrix.Color(255,255,255));
    matrix.drawPixel(7,5,matrix.Color(255,255,255));
    matrix.drawPixel(2,6,matrix.Color(255,255,255));
    matrix.drawPixel(4,6,matrix.Color(255,255,255));
    matrix.drawPixel(6,6,matrix.Color(255,255,255));
    matrix.drawPixel(8,6,matrix.Color(255,255,255));
    matrix.show();
}

void drawUnknown() {
    matrix.drawPixel(2, 2, matrix.Color(0, 0, 0));
    matrix.drawPixel(2, 1, matrix.Color(0, 0, 0));
    matrix.drawPixel(3, 1, matrix.Color(0, 0, 0));
    matrix.drawPixel(4, 1, matrix.Color(0, 0, 0));
    matrix.drawPixel(4, 2, matrix.Color(0, 0, 0));
    matrix.drawPixel(4, 3, matrix.Color(0, 0, 0));
    matrix.drawPixel(3, 3, matrix.Color(0, 0, 0));
    matrix.drawPixel(3, 4, matrix.Color(0, 0, 0));
    matrix.drawPixel(3, 6, matrix.Color(0, 0, 0));
    matrix.drawPixel(6, 2, matrix.Color(0, 0, 0));
    matrix.drawPixel(6, 1, matrix.Color(0, 0, 0));
    matrix.drawPixel(7, 1, matrix.Color(0, 0, 0));
    matrix.drawPixel(8, 1, matrix.Color(0, 0, 0));
    matrix.drawPixel(8, 2, matrix.Color(0, 0, 0));
    matrix.drawPixel(8, 3, matrix.Color(0, 0, 0));
    matrix.drawPixel(7, 3, matrix.Color(0, 0, 0));
    matrix.drawPixel(7, 4, matrix.Color(0, 0, 0));
    matrix.drawPixel(7, 6, matrix.Color(0, 0, 0));
    matrix.show();
}

void drawProgressBar(){
    matrix.clear();
    int progressBarLength = map(Brightness, 0, 255, 0, SCREEN_WIDTH);
    for (int i = 1; i < progressBarLength; i++) {
        matrix.drawLine(i, 3, i, 3, matrix.Color(255,255,255));
        matrix.drawLine(i, 4, i, 4, matrix.Color(255,255,255));
        matrix.drawLine(i, 5, i, 5, matrix.Color(255,255,255));
    }
    matrix.show();
    matrix.setBrightness(Brightness);
}

void adjustBrightness() {
    joystick_x = analogRead(adc0);
    joystick_y = analogRead(adc1);
    if (joystick_x == 8191 && joystick_y != 0) {
        Brightness += 10;
    } else if (joystick_x == 0 && joystick_y != 0) {
        Brightness -= 10;
    }

    if (Brightness < 0) {
        Brightness = 0;
    } else if (Brightness > 255) {
        Brightness = 255;
    }
}

#endif //CODE_DRAWTHINGS_H