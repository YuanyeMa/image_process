#!/usr/bin/env python
# @author: rechie
# python --version 2.7
# opencv --version 2.4.13

from cv2 import *

def process():
    srcImg1 = imread("./01.jpg")
    srcImg2 = imread("./02.jpg")

    if srcImg1 == None and srcImg2 == None :
        print "read image file failed!"
	return false
    
    x = srcImg1.shape[1]/5
    y = srcImg1.shape[0]/5

    ImgROI = srcImg1[150:150+y, 1000:1000+x]
    res = srcImg1.copy()
    Img2 = resize(srcImg2, (x,y))
    
    a = 0.5
    b = 1 - a

    ImgROI = addWeighted(ImgROI, a, Img2, b, 0)
    res[150:150+y, 1000:1000+x] = ImgROI
	
    imwrite("addWeighted-part.jpg", res)
    imshow("res", res)
    waitKey(0)

if __name__ == '__main__':
    process()	
