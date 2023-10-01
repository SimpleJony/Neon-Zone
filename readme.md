<div align="center">

# Neon Zone
### 一个基于ESP32制作的DIY像素灯

---
#### `Neon Zone`是一款基于ESP32制作的像素灯，通过WS2812b的灯板来驱动显示，Arduino编写程序运行，是一款集设计与实用性为一体的像素灯
---
</div>

## 👐良好的开始
### 材料准备
* 详细材料见“相关资料”

### 程序编译
#### Tips:
* 程序通过Clion(~~也可以使用vscode~~) + platformio插件编写实现，关于如何配置PlatformIo,请参考[此文档](https://docs.platformio.org/en/latest/integration/ide/pioide.html)

* 程序编写时用到的git的submodule，在将项目clone下来之后，你需要在Code文件夹下执行以下代码：
```
git submodule init
```

### 1. 使用git指令将改项目clone下来
```
git clone https://github.com/SimpleJony/Neon-Zone
```
### 2. 将项目导入Clion，等待项目的初始化
在Clion中选择`打开`，选中项目中的`Code`文件夹，点击打开
[![project-init](https://z1.ax1x.com/2023/10/01/pPLKoIU.png)](https://imgse.com/i/pPLKoIU)

## 📱功能实现
* **小爱同学控制灯的运行**
* 连接网络，自动获取时间，天气信息
* 显示时间，天气
* 计时器功能
* 贪吃蛇小游戏
* 代码雨动画

## Credits
* [SimpleJony](https://github.com/SimpleJony): 编写整个项目的程序
* Kila: 外观设计&模型制作
* [Blinker](https://github.com/blinker-iot): IoT方案的提供
* [QWeather](https://www.qweather.com/): 天气数据的提供
* [Arduino](https://github.com/arduino): 程序编写所使用的语言
* [Adafruit](https://github.com/adafruit): 灯板控制所用到的库
* [嘉立创](https://www.jlc.com/): 3D打印服务提供