#include <ros/ros.h>
//#include "core/core.hpp" 
//#include "imgproc/imgproc.hpp"  
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <stdio.h>
#include "sensor_msgs/Image.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <string>

using namespace cv;
using namespace std;
 
#define iLowH        1
#define iHighH       30
#define iLowS        90
#define iHighS       255 
#define iLowV        189
#define iHighV       255 

#define g_nThresh    100   //137
// Original Parameters
// int iLowH = 1;
// int iHighH = 30;
// int iLowS = 30;
// int iHighS = 255;
// int iLowV = 100;
// int iHighV = 255;
#define img_compress_width  640
#define img_compress_height 480
#define img_num  14
#define beg  0
#define end  14

const string img_path = "/home/hyh/mc_ws/src/object_recognition/object_images/";

vector<Mat> GetOriginalImg(const string img_path)
{
	string img_name;
	cv::Mat imgOriginal;
	vector<Mat> imgOriginalVector;
	for(int index = 0; index < img_num; index++)
	{
		img_name = format("%d.jpg", index+1);
		imgOriginal = cv::imread(img_path + img_name, CV_LOAD_IMAGE_COLOR);
		resize(imgOriginal, imgOriginal, cv::Size(img_compress_width, img_compress_height));//resize the shape of image
		imgOriginalVector.push_back(imgOriginal);
	}
	return imgOriginalVector;
}

void showManyImages(vector<Mat>& src, Size imgSize)
{
	int nNumImages = src.size();
	Size nSizeWindows;
	if (nNumImages > 14)
	{
		cout << "Not more than 14 images!" << endl;
		return;
	}
	//根据图片数量确定分割小窗口的排布
	switch (nNumImages)
	{
	case 1:nSizeWindows = Size(1, 1); break;
	case 2:nSizeWindows = Size(1, 2); break;
	case 3:
	case 4:nSizeWindows = Size(2, 2); break;
	case 5:
	case 6:nSizeWindows = Size(3, 2); break;
	case 7:
	case 8:nSizeWindows = Size(4, 2); break;
	case 9:nSizeWindows = Size(3, 3); break;
	case 10:nSizeWindows = Size(4, 3); break;
	case 11:nSizeWindows = Size(4, 3); break;
	case 12:nSizeWindows = Size(4, 3); break;
	case 13:nSizeWindows = Size(5, 3); break;
	case 14:nSizeWindows = Size(5, 3); break;
	default:nSizeWindows = Size(5, 3); break;
	
	}
	//设置图像的大小，图像之间的间隔以及边界
	int nShowImageSize = 300;
	int nShowImageH = 225;
	int nSplitLineSize = 15;
	int nAroundLineSize = 50;
	//创建输出图像的大小
	int imageWidth = nShowImageSize*nSizeWindows.width + (nShowImageSize - 1)*nSplitLineSize + nAroundLineSize;
	int imageHeight = nShowImageH*nSizeWindows.height + (nShowImageH - 1)*nSplitLineSize + nAroundLineSize;
	Mat showWindowImages(imageHeight, imageWidth, CV_8UC3, Scalar::all(0));
	//提取小图像左上角坐标
	int posX = nAroundLineSize / 2;
	int posY = nAroundLineSize / 2;
	cout << "posX: " << posX << " posY: " << posY << endl;
	int tempPosX = posX;
	int tempPosY = posY;
	//将每张小图整合到大图中
	for (int i = 0; i < nNumImages; i++)
	{
		if ((i%nSizeWindows.width == 0) && (tempPosX != posX))
		{
			tempPosX = posX;
			tempPosY += (nSplitLineSize + nShowImageH);
		}
		//利用Rect区域将小图像置于大图像相应区域
		Mat tempImage = showWindowImages(Rect(tempPosX, tempPosY, nShowImageSize, nShowImageH));
		//利用resize实现图像缩放
		resize(src[i],tempImage,Size(nShowImageSize,nShowImageH));
		tempPosX += nSplitLineSize + nShowImageSize;
	}
	
	imshow("showWindowImages",showWindowImages);
}

Mat myfindContours(Mat image)    
{  
    vector<vector<Point> > contours;  
    vector<Vec4i> hierarchy;  
    findContours(image,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point());  
    Mat imageContours=Mat::zeros(image.size(),CV_8UC1);  
    Mat Contours=Mat::zeros(image.size(),CV_8UC1);  //绘制  

    for(int i=0;i<contours.size();i++)  
    {  
        //contours[i]代表的是第i个轮廓，contours[i].size()代表的是第i个轮廓上所有的像素点数  
        for(int j=0;j<contours[i].size();j++)   
        {  
            //绘制出contours向量内所有的像素点  
            Point P=Point(contours[i][j].x,contours[i][j].y);  
            Contours.at<uchar>(P)=255;  
        }  
        //绘制轮廓  
        drawContours(imageContours,contours,i,Scalar(255),1,8,hierarchy);  
    }  
    imshow("Contours Image",imageContours); //轮廓  
    imshow("Point of Contours",Contours);   //向量contours内保存的所有轮廓点集  
    waitKey(0);  
    return imageContours;  
}  

int main(int argc, char** argv)
{
	Mat canny_output;
	Mat imgHSV;
	Mat imgThresholded;//二值化后的图像数组
	Mat bf;//对灰度图像进行双边滤波
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));

	ros::init(argc, argv, "object_rgb_pos_publisher");
	ros::NodeHandle nh;
	// image_transport::ImageTransport it(nh);//用之前声明的节点句柄初始化it，其实这里的it和nh的功能基本一样，可以像之前一样使用it来发布和订阅相消息。
	// image_transport::Publisher pub = it.advertise("object/rgb/pos", 1);

	ros::Rate loop_rate(5);//每秒5帧

	while (nh.ok()) 
	{
		vector<Mat> imgOriginalVector = GetOriginalImg(img_path);
		string img_name;
		//showManyImages(imgOriginalVector, Size(img_compress_height, img_compress_height));

		for(int index = 0; index < img_num; index++)
		{
			img_name = format("%d.jpg", index+1);
			vector<Mat> hsvSplit;
			cvtColor(imgOriginalVector[index], imgHSV, COLOR_BGR2HSV); 
			split(imgHSV, hsvSplit);
			equalizeHist(hsvSplit[2], hsvSplit[2]);
			inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
			//morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);//dialate and erode
			//imshow("imgThresholded_morph" + img_name, imgThresholded);

			blur(imgThresholded, bf, Size(3, 3));//mean value fiter
			//用Canny算子检测边缘
			Canny(bf, canny_output, g_nThresh, g_nThresh * 2, 3);// canny_output is a binary img

			//myfindContours(canny_output);
			//开操作 (去除一些噪点)
			//morphologyEx(canny_output, canny_output, MORPH_OPEN, element);

			//闭操作 (连接一些连通域)
			//morphologyEx(canny_output, canny_output, MORPH_CLOSE, element);
			//imshow("canny_output_morph" + img_name, canny_output);
			vector<Vec3f> circles;
			int dp = 1; int minDist = 70; int param1 = 250; int param2 = 15; int minRadius = 1; int maxRadius = 100;

			HoughCircles(canny_output, circles, CV_HOUGH_GRADIENT, dp, minDist, param1, param2, minRadius, maxRadius);


			cout << "\n" << img_name << ":\n";
			for (size_t i = 0; i < circles.size(); i++)//把霍夫变换检测出的圆画出来
			{
				Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
				int radius = cvRound(circles[i][2]);

				circle(imgOriginalVector[index], center, radius, Scalar(255, 255, 255), 2, 8, 0);

				cout << "x= " << cvRound(circles[i][0]) << "\t" << "y= " << cvRound(circles[i][1]) << "\t"
					<< "r=" << cvRound(circles[i][2]) << endl;			
			}

			imshow("imgThresholded" + img_name, imgThresholded);
			imshow("canny_output" + img_name, canny_output);
			imshow("HoughCircles" + img_name, imgOriginalVector[index]);

			waitKey();
		}
		ros::spinOnce();
		loop_rate.sleep();
	}
}