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
#include <geometry_msgs/Point.h>
#include <ball_msgs/BallPositionStamp.h>

using namespace cv;
using namespace std;

Mat ImageThresholded;//二值化后的图像数组
Mat ImageProcessed;//处理后的图像，画出小球的轮廓
sensor_msgs::ImagePtr RosImgThresholded;
sensor_msgs::ImagePtr RosImageProcessed;
ball_msgs::BallPositionStamp BallPosition;//z is the radius of circle

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

void Table_Tennis_Pos(Mat img)
{
    Mat canny_output;
	Mat imgHSV;
	Mat bf;//对灰度图像进行双边滤波
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    vector<Mat> hsvSplit;
	ImageProcessed = img;
    cvtColor(img, imgHSV, COLOR_BGR2HSV); 
    split(imgHSV, hsvSplit);
    equalizeHist(hsvSplit[2], hsvSplit[2]);
    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), ImageThresholded); //Threshold the image


    blur(ImageThresholded, bf, Size(3, 3));//mean value fiter

    Canny(bf, canny_output, g_nThresh, g_nThresh * 2, 3);// canny_output is a binary img

    //myfindContours(canny_output);

    vector<Vec3f> circles; //
    // int dp = 1; int minDist = 70; int param1 = 250; int param2 = 15; int minRadius = 1; int maxRadius = 100;
	int dp = 1; int minDist = 8; int param1 = 250; int param2 = 20; int minRadius = 2; int maxRadius = 40;
    HoughCircles(canny_output, circles, CV_HOUGH_GRADIENT, dp, minDist, param1, param2, minRadius, maxRadius);


	//find all circles , Hough Circles
	geometry_msgs::Point tempPos;
	BallPosition.Position.clear();

    for (size_t i = 0; i < circles.size(); i++)
    {
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		tempPos.x = cvRound(circles[i][0]);
		tempPos.y = cvRound(circles[i][1]);
		tempPos.z = cvRound(circles[i][2]);
		circle(ImageProcessed, center, tempPos.z, Scalar(255, 255, 255), 2, 8, 0);
		BallPosition.Position.push_back(tempPos);
    }
}


void imageCallback(const sensor_msgs::Image::ConstPtr& msg)
{
	ImageStamped = msg->header.stamp;

	cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	Mat image_raw = cv_ptr->image;

	Table_Tennis_Pos(image_raw);

	/* publish  RosImageProcessed*/
	RosImageProcessed = cv_bridge::CvImage(std_msgs::Header(), "bgr8", ImageProcessed).toImageMsg(); 
	RosImageProcessed->header.stamp = ImageStamped;
	RosImageProcessed->header.frame_id = "image_processed_Frame";

	/* publish  RosImageProcessed*/
	RosImgThresholded = cv_bridge::CvImage(std_msgs::Header(), "mono8", ImageThresholded).toImageMsg(); 
	RosImgThresholded->header.stamp = ImageStamped;
	RosImgThresholded->header.frame_id = "image_thresholded_Frame";
	
	/* publish  position of ball*/
	BallPosition.header.stamp = ImageStamped;
	BallPosition.header.frame_id = "Ball_Frame";
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_process");
    ros::NodeHandle nh;

    ros::Publisher BallPos_pub = nh.advertise<ball_msgs::BallPositionStamp>("/Ball/Position", 10);
    image_transport::ImageTransport it(nh); 
    image_transport::Publisher ImageProcessed_pub = it.advertise("camera/rgb/image_processed", 1);
	image_transport::Publisher ImageThresholded_pub = it.advertise("camera/rgb/image_thresholded", 1);
	image_transport::Subscriber image_raw_sub = it.subscribe("/usb_cam/image_raw", 1, imageCallback);

    sensor_msgs::ImagePtr msg1;

    ros::Rate loop_rate(30); //定义发布频率

    while (nh.ok())
    {
		ImageProcessed_pub.publish(RosImageProcessed);
		ImageThresholded_pub.publish(RosImgThresholded);
		BallPos_pub.publish(BallPosition);

        ros::spinOnce();
        loop_rate.sleep();
    }
}