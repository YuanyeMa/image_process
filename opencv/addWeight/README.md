# addWeighted 图像混合(线性混合)
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
