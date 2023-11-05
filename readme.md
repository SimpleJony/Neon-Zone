<div align="center">

[![Header Picture](https://z1.ax1x.com/2023/11/05/piQY8Ld.png)](https://imgse.com/i/piQY8Ld)
# Neon Zone
### A DIY pixel light based on ESP32

---
#### `Neon Zone`is a pixel light made based on ESP32. The display is driven by the light board of WS2812b, and the Arduino program is written and run. It is a pixel light integrating design and practicality

---
</div>

[中文](https://github.com/SimpleJony/Neon-Zone/readme_cn.md) | [English](https://github.com/SimpleJony/Neon-Zone/readme_en.md)

## 👐Get Started
### Material

* See "Material" folder for details.

### Program Compile
#### Tips:
* Program is written by Clion(~~vscode is good for it too~~) + platformio plugin, about how to configure PlatformIO,please refer to [this document](https://docs.platformio.org/en/latest/integration/ide/pioide.html)

* If it is difficult to configure the project in Clion, you can use vscode to configure the project and then write code in Clion

* The git submodule was used to write the program. After you clone the project, you need to execute the following Code in the code folder：
```
git submodule init
git submodule update
```

### 1. Clone the project with git command
```
git clone https://github.com/SimpleJony/Neon-Zone
```
### 2. Import project into Clion,wait for its initialization
Choose `Open` in Clion，select the `Code` folder，click `Open`
[![project-init](https://z1.ax1x.com/2023/10/01/pPLKoIU.png)](https://imgse.com/i/pPLKoIU)

## 📱Function
* **Control the light by XiaoAi**
* ESP32 SoftAP network configure mode
* Connect to the network, automatically get time, weather information
* Show time, weather
* Timer
* Snake
* Code rain animation

## Credits
* [SimpleJony](https://github.com/SimpleJony): Program the project
* [Kila](https://space.bilibili.com/278299486/?spm_id_from=333.999.0.0): Exterior Design & Model making
* [Blinker](https://github.com/blinker-iot): IoT Solution provider
* [QWeather](https://www.qweather.com/): Weather data provider
* [Arduino](https://github.com/arduino): Language used to write this project
* [Adafruit](https://github.com/adafruit): Libs used to control the light
* [JLC](https://www.jlc.com/): 3D print service provider
