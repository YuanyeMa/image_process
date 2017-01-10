#!/usr/bin/env python
# -*- coding=utf-8 -*-
# @author: rechie

from cv2 import *

def erode_dilate():
    img = imread("01.jpg", 0)
    
    # opencv定义的结构元素
    kernel = getStructuringElement(MORPH_RECT,(3,3))
    
    # 腐蚀图像
    eroded = erode(img, kernel)
    # 保存并显示腐蚀后的图像
    imwrite("eroded.jpg", eroded)
    imshow("Eroded Image", eroded)
    
    # 膨胀图像
    dilated = dilate(img, kernel)
    # 保存并显示膨胀后的图像
    imwrite("dilated.jpg", dilated)
    imshow("Dilated Image", dilated)
    
    # 原图像
    imshow("Origin", img)
    
    waitKey(0)
    destroyAllWindows()

if __name__ == '__main__':
    erode_dilate()
