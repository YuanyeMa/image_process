# Image_Process Demo

图像处理实例集合
## [bmp](./bmp/bmp.md)  
bmp和yuv420 plat格式的图片文件相互转换  
运行环境：linux，编译器：gcc  
文件说明：  
	bmp.h			----- 声明bmp头结构， bmp2yuv.c和yuv2bmp.c公用  
	yuv2bmp.c	----- yuv图片转换为bmp格式程序  
	bmp2yuv.c	----- bmp图片格式转为yuv格式程序		  

## opencv
此目录是学习opencv时写的一些demo程序

### [感兴趣区域选取（ROI）](./opencv/roi/opencv-ROI.md)
opencv ROI和图像混合

### [线性混合](./opencv/addWeight/README.md)
opencv addWeighted 函数进行线性混合

### [图像亮度和对比度调节](./opencv/bright/README.md)
对比度和亮度调节的示例程序，对比度和亮度的调节方法，滑动条的使用以及像素的访问方法；

### [highgui基本组件和基本绘图](./opencv/mouseAndDraw/README.md)
### [erode/dilate](./opencv/erode_dilate/README.md)
