import  cv2

def drawRotatedRect(rect, image):
    box = cv2.boxPoints(rect)
    x0, y0 = box[0]
    for i in range(3):
        x, y = box[i]
        x1, y1 = box[i + 1]
        cv2.line(image, (x, y), (x1, y1), (0, 0, 255), 2)
        if i is 2:
            cv2.line(image, (x1, y1), (x0, y0), (0, 0, 255), 2)


img = cv2.imread("./6.jpg")

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
af_f = cv2.medianBlur(gray, 3) #中值滤波
ret, thresh = cv2.threshold(af_f, 240 , 255, cv2.THRESH_BINARY_INV)

contours = cv2.findContours(thresh.copy(), cv2.MORPH_RECT, cv2.CHAIN_APPROX_SIMPLE) #不知道为什么使用CV_RETR_EXTERNAL会报错
#contours[0] 为原图
#contours[1] 为轮廓list
#contours[2] 为轮廓属性

# print(len(contours))
# print(type(contours))

# print(len(contours[0]))
# print(type(contours[0]))
# print(type(contours[0][0]))
# print(len(contours[0][0]))

# print(len(contours[1]))
# print(type(contours[1]))
#
#
# print(len(contours[2]))
# print(type(contours[2]))

for _ in range(len(contours[1])):
    cv2.drawContours(img, contours[1], _, (0, 200, 0), 1)
    #rect = cv2.boundingRect(contours[1][_])
    #img = cv2.rectangle(img, (rect[0],rect[1]), (rect[0]+rect[2], rect[1]+rect[3]), (255, 0,0), 2)
    rect = cv2.minAreaRect(contours[1][_])
    drawRotatedRect(rect, img)



cv2.namedWindow("img", cv2.WINDOW_NORMAL)
cv2.imshow("img", img)

cv2.waitKey(0)