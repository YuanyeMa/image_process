# Image_Process Demo

图像处理实例集合

## 1、[bmp](./bmp/bmp.md)

bmp和yuv420 plat格式的图片文件相互转换

运行环境：linux，编译器：gcc

文件说明：

* bmp.h-----声明bmp头结构，bmp2yuv.c 和 yuv2bmp.c公用
* yuv2bmp.c----- yuv图片转换为bmp格式程序
* bmp2yuv.c----- bmp图片格式转为yuv格式程序

## 2、[OpenCV](./opencv)

此目录是学习OpenCV时写的一些demo程序。

### 如何安装OpenCV

#### 方法一

在最新的Ubuntu 19.04中可以使用此方法安装OpenCV 3.2：

```Bash
sudo apt update
sudo apt install libopencv-dev -y
```

#### 方法二

源码编译，参考[自动安装OpenCV的脚本](./opencv/install-opencv-2.4.13-in-ubuntu.sh)

### [感兴趣区域选取（ROI）](./opencv/roi)

OpenCV ROI和图像混合。

### [线性混合](./opencv/addWeight)

OpenCV addWeighted 函数进行线性混合。

### [图像亮度和对比度调节](./opencv/bright)

对比度和亮度调节的示例程序，对比度和亮度的调节方法，滑动条的使用以及像素的访问方法。

### [highgui基本组件和基本绘图](./opencv/mouseAndDraw)

OpenCV中各项GUI组件的应用。

### [形态学操作（腐蚀与膨胀）](./opencv/erode_dilate)

OpenCV中两种基本的形态学操作，腐蚀与膨胀的应用。

### [画目标轮廓](./opencv/findContours)

OpenCV中的轮廓提取函数的应用。

### [图像直方图计算](./opencv/calcHist)

对图像直方图的计算

### [人脸识别](./opencv/facedetect)

Opencv中人脸识别的示例（识别速度较慢）

### [基于帧差法的视频动态检测](./opencv/movedetect)

Opencv的关于帧差法检测视频中动态情况的示例

### [图片大小的修改](./opencv/resize)

如何使用OpenCV修改图片大小
