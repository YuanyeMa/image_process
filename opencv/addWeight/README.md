# addWeighted 图像混合(线性混合)
## 原图
![01](./01.jpg)  
![02](./02.jpg)
## 效果
![线性混合](./addWeighted.jpg)

## 函数原型
```
void addWeighted(InputArray src1, double alpha, InputArray src2,
                              double beta, double gamma, OutputArray dst, int dtype = -1);
```
混合公式：dst[I] = src1[I]\*alpha + src2[I]\*beta + gamma;
最后一个参数dtype表示输出阵列的可选深度，默认为-1，即等于src1.depth()

## 注意
src1的大小要和src2相等，如果不相等需要通过resize等进行变换。

例如，addWeighted-part.cpp中
```
Size sz(srcImg1.cols/5, srcImg1.rows/5);
Mat srcImg2z;
resize(srcImg2, srcImg2z, sz);

Mat imageROI = srcImg1(Rect(1000, 150, srcImg2z.cols, srcImg2z.rows));
addWeighted(imageROI, a, srcImg2z, b, 0, imageROI);
```
效果如下
![addWeighted-part](./addWeighted-part.jpg)  

## python版addWeighted-part
[addWeighted-part.py](./addWeighted-part.py)

## PIL Image 模块的blend函数实现相同效果
```
PIL.Image.blend(image1, image2, alpha)
out= image1 * (1-alpha) + image2 * alpha
```
[addWeight-by-blend.py](./addWeight-by-blend.py)
