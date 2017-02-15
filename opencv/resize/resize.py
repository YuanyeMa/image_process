#!/usr/bin/env python
# -*- coding:utf-8 -*-
# @author: rechie
# python --version 2.7
# opencv --version 2.4.13

import cv2

def resize():
    # 读取图片
    img = cv2.imread("01.jpg")
    if img == None:
        print "read image file failed!"
        return false
    cv2.imshow("origin", img)
    # 改变图片大小
    res = cv2.resize(img, (img.shape[1]/2, img.shape[0]/2))
    # 保存并显示图片
    cv2.imwrite("resize.jpg", res)
    cv2.imshow("res", res)
    cv2.waitKey(0)

if __name__ == '__main__':
    resize()
