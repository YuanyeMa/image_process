#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @author: rechie
# 使用Numpy的直方图计算函数np.histogram实现

import cv2
import numpy as np

img = cv2.imread("/home/rechie/Pictures/6.jpg")
# 创建用于绘制直方图的全0图像
h = np.zeros((300, 256, 3))
# 直方图中各bin的顶点位置
bins = np.arange(257)
bin = bins[0: -1]
# BGR三种颜色
color = [(255, 0, 0), (0, 255, 0), (0, 0, 255)]

for ch, col in enumerate(color):
    item = img[:, :, ch]
    N, bins = np.histogram(item, bins)
    v = N.max()
    N = np.int32(np.around((N*255)/v))
    N = N.reshape(256, 1)
    pts = np.column_stack((bin, N))
    cv2.polylines(h, [pts], False, col)

h = np.flipud(h)

cv2.imshow("img", img)
cv2.imshow("his", h)
cv2.waitKey(0)
