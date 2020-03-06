#coding=utf-8
import cv2
from matplotlib import pyplot as plt
import numpy as np

img_path = "/media/hyh/Study/Desktop/Post-Graduate/Course/Modern_Control/Project/object_images/"
Img_beg = 1
Img_end = 14
img_compress_width = 640
img_compress_height = 480

def nothing():
    pass

def GetHSV(img_path):
    hsv_img = []
    plt.figure(1)
    for index in range(Img_beg - 1, Img_end):
        img_name = str(index+1) + ".jpg" 
        original_img = cv2.imread(img_path + img_name)
        original_img = cv2.resize(original_img, (img_compress_width, img_compress_height))#resize the shape of image
        hsv_img.append(cv2.cvtColor(original_img, cv2.COLOR_BGR2HSV))
        b,g,r = cv2.split(original_img) 
        original_img = cv2.merge([r,g,b])
        plt.subplot(3, 5, index+1)
        plt.imshow(original_img)
        # cv2.imshow(img_name,original_img)
        plt.title(img_name,fontsize=8)     

    plt.show()
    return hsv_img

# cv2.waitKey(0)

# hist_H = cv2.calcHist([hsv_img],[0],None,[181],[0,180])    
# hist_S = cv2.calcHist([hsv_img],[1],None,[256],[0,255])
# hist_V = cv2.calcHist([hsv_img],[2],None,[256],[0,255])    #获得不同通道的颜色直方图



def AdjustHSV(hsv_img):

    cv2.namedWindow('value')
    cv2.createTrackbar('h', 'value', 30, 180, nothing)
    cv2.createTrackbar('_h', 'value', 12, 50, nothing)
    cv2.createTrackbar('s', 'value', 255, 255, nothing)
    cv2.createTrackbar('_s', 'value', 90, 255, nothing)
    cv2.createTrackbar('v', 'value', 255, 255, nothing)
    cv2.createTrackbar('_v', 'value', 189, 255, nothing)
    while(1):
        k = cv2.waitKey(10)

        if k == ord('e'):#exit
            cv2.destroyAllWindows()
            break

        elif k == ord('o'): #change the value
            
            print("h value:", cv2.getTrackbarPos('h', 'value'), "s value:", cv2.getTrackbarPos('s', 'value'), "v value:", cv2.getTrackbarPos('v', 'value'))
            lb = np.array([1,100,170])
            lb = np.array([cv2.getTrackbarPos('_h','value'), cv2.getTrackbarPos('_s','value'), cv2.getTrackbarPos('_v','value')])
                
            hb = np.array([30,255,255])
            hb = np.array([cv2.getTrackbarPos('h', 'value'), cv2.getTrackbarPos('s', 'value'), cv2.getTrackbarPos('v', 'value')])
            
            for index in range(0,14):
                img_name = str(index+1) + ".jpg" 
                mask = cv2.inRange(hsv_img[index], lb, hb) 
                # b,g,r = cv2.split(mask) 
                # mask = cv2.merge([r,g,b])
                # cv2.imshow("imgimgThresholded", mask)
                plt.subplot(3, 5, index+1)
                plt.imshow(mask, cmap="gray")
                plt.title(img_name,fontsize=8)  
            plt.show()

        elif k == ord('n'):# next image
            img_index = img_index + 1
            break

hsv_img = GetHSV(img_path)
AdjustHSV(hsv_img)