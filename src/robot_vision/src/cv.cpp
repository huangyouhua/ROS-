#include <ros/ros.h>
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
 
#define img_compress_width  640
#define img_compress_height 480

int main(int argc, char** argv)
{
  ros::init(argc, argv, "robot_vision/cv");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);//用之前声明的节点句柄初始化it，其实这里的it和nh的功能基本一样，可以像之前一样使用it来发布和订阅相消息。
 
  cv::Mat imgOriginal;
  cv::Mat imgHSV;
  string img_path;
  string img_name;

  ros::Rate loop_rate(5);//每秒5帧

  img_path = "/media/hyh/Study/Desktop/Post-Graduate/Course/Modern_Control/Project/object_images/";
  img_name = "4.jpg";

  while (nh.ok()) 
  {
	imgOriginal = cv::imread(img_path + img_name, CV_LOAD_IMAGE_COLOR);
	resize(imgOriginal, imgOriginal, cv::Size(img_compress_width, img_compress_height));//resize the shape of image

	imshow("imgOriginal", imgOriginal);//

	cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

	waitKey();

	ros::spinOnce();
	loop_rate.sleep();
  }
}