#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @author: rechie
# 用OpenCV的直方图计算函数cv2.calcHist

import cv2
import numpy as np

img = cv2.imread("/home/rechie/Pictures/6.jpg")
# 创建用于绘制直方图的全0图像
h = np.zeros((256, 256, 3))
# 直方图中各bin的顶点位置
bins = np.arange(256).reshape(256, 1)
# BGR三种颜色
color = [(255, 0, 0), (0, 255, 0), (0, 0, 255)]
for ch, col in enumerate(color):
    originHist = cv2.calcHist([img], [ch], None, [256], [0, 256])
    cv2.normalize(originHist, originHist, 0, 255*0.9, cv2.NORM_MINMAX)
    hist = np.int32(np.around(originHist))
    pts = np.column_stack((bins, hist))
    cv2.polylines(h, [pts], False, col)

h = np.flipud(h)

cv2.imshow("img", img)
cv2.imshow("hist", h)
cv2.waitKey(0)
