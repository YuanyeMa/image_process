# 图像尺寸缩放
opencv关于图像缩放有两种方式：
- resize函数：对图像进行任意尺寸的缩放；
- 图像金字塔：成倍的放大或缩小；

## resize
函数原型：`void resize(InputArray src,OutputArray dst, Size dsize, double fx=0, double fy=0, int interpolation=INTER_LINEAR ) `  
第一个参数：src, 源图像;  
第二个参数：dst, 输出图像；
第三个参数：dsize, 输出图像的尺寸，当为零时，则由公式`dsize = Size(round(fx*src.cols), round(fy*src.rows))`指定；  
第四个参数：fx, 沿水平轴的缩放系数，有默认值0，且当其等于0时，由`(double)dsize.width/src.cols`指定；  
第五个参数：fy, 沿垂直方向的缩放系数，有默认值0，且当其等于0时，由`(double)dsize.height/src.rows`指定;  
第六个参数：interpolation， 用于指定插值方式，默认为INTER_LINEAR(线性插值)；  
>可选的插值方式如下  
>- INTER_LINEAR 线性插值
- INTER_NEAREST 最近邻插值  
- INTER_AREA 区域插值 （利用像素区域关系的重采样插值）
- INTER_CUBIC –三次样条插值（超过4×4像素邻域内的双三次插值）
- INTER_LANCZOS4 -Lanczos插值（超过8×8像素邻域的Lanczos插值）


## 图像金字塔
