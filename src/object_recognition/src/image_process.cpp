#include <ros/ros.h>
#include "../include/image_process.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "sensor_msgs/Image.h"
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PointStamped.h>

using namespace cv;
using namespace std;

pair<Point, Mat> ImageProcessed;
sensor_msgs::ImagePtr RosImageProcessed;
geometry_msgs::PointStamped BallPos;
ros::Time ImageStamped;

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

pair<Point, Mat> Table_Tennis_Pos(Mat img)
{
    Mat canny_output;
	Mat imgHSV;
	Mat imgThresholded;//二值化后的图像数组
	Mat bf;//对灰度图像进行双边滤波
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    vector<Mat> hsvSplit;
    cvtColor(img, imgHSV, COLOR_BGR2HSV); 
    split(imgHSV, hsvSplit);
    equalizeHist(hsvSplit[2], hsvSplit[2]);
    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image


    blur(imgThresholded, bf, Size(3, 3));//mean value fiter

    Canny(bf, canny_output, g_nThresh, g_nThresh * 2, 3);// canny_output is a binary img

    //myfindContours(canny_output);

    vector<Vec3f> circles;
    int dp = 1; int minDist = 70; int param1 = 250; int param2 = 15; int minRadius = 1; int maxRadius = 100;

    HoughCircles(canny_output, circles, CV_HOUGH_GRADIENT, dp, minDist, param1, param2, minRadius, maxRadius);

    int MaxCircleRadius = 0;
    size_t MaxCircleIndex = 0;
    for (size_t i = 0; i < circles.size(); i++)//find the biggest circles
    {
        if(cvRound(circles[i][2]) > MaxCircleRadius)
        {
            MaxCircleRadius =  cvRound(circles[i][2]);
            MaxCircleIndex = i;
        }
    }

	Point center(img_compress_width/2, img_compress_height/2);
	if(circles.size() != 0)
	{
		//Point center(cvRound(circles[MaxCircleIndex][0]), cvRound(circles[MaxCircleIndex][1]));
		center.x = cvRound(circles[MaxCircleIndex][0]);
		center.y = cvRound(circles[MaxCircleIndex][1]);
		int radius = cvRound(circles[MaxCircleIndex][2]);
		circle(img, center, radius, Scalar(255, 255, 255), 2, 8, 0);// Hough Circles

	}
	return {center, img};
}


void imageCallback(const sensor_msgs::Image::ConstPtr& msg)
{
	ImageStamped = msg->header.stamp;

	cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	Mat image_raw = cv_ptr -> image;

	ImageProcessed = Table_Tennis_Pos(image_raw);

	RosImageProcessed = cv_bridge::CvImage(std_msgs::Header(), "bgr8", ImageProcessed.second).toImageMsg(); 
	RosImageProcessed->header.stamp = ImageStamped;
	RosImageProcessed->header.frame_id = "image_processed_Frame";
	
	BallPos.point.x = ImageProcessed.first.x;
	BallPos.point.y = ImageProcessed.first.y;
	BallPos.point.z = 0;
	BallPos.header.stamp = ImageStamped;
	BallPos.header.frame_id = "Ball_Frame";
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_process");
    ros::NodeHandle nh;

    ros::Publisher BallPosPub = nh.advertise<geometry_msgs::PointStamped>("/Ball/Pos", 10);
    image_transport::ImageTransport it(nh); //用之前声明的节点句柄初始化it，其实这里的it和nh的功能基本一样，可以像之前一样使用it来发布和订阅相消息。
    image_transport::Publisher ImagePub = it.advertise("camera/rgb/image_processed", 1);
	image_transport::Subscriber sub = it.subscribe("/usb_cam/image_raw", 1, imageCallback);

    sensor_msgs::ImagePtr msg1;

    ros::Rate loop_rate(30); //定义发布频率

    while (nh.ok())
    {
		ImagePub.publish(RosImageProcessed);
		BallPosPub.publish(BallPos);

        ros::spinOnce();
        loop_rate.sleep();
    }
}