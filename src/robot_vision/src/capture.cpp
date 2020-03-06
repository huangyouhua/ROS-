#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include <stdio.h>
#include"sensor_msgs/Image.h"
 
using namespace cv;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);//用之前声明的节点句柄初始化it，其实这里的it和nh的功能基本一样，可以像之前一样使用it来发布和订阅相消息。
  image_transport::Publisher pub = it.advertise("camera/rgb/image_raw", 1);
 
  //cv::Mat image = cv::imread("/home/hyh/桌面/12.png", CV_LOAD_IMAGE_COLOR);

  VideoCapture capture;
  capture.open(1);//打开相机 (1)选择相机设备号

  if(!capture.isOpened())
  {
    printf("摄像头没有正常打开，重新插拔工控机上当摄像头\n");
    return 0;
  }

  waitKey(1000);
  Mat frame;//当前帧图片
  int nFrames=0;//图片帧数
  int frameWidth=capture.get(CV_CAP_PROP_FRAME_WIDTH);//图片宽
  int frameHeight=capture.get(CV_CAP_PROP_FRAME_HEIGHT);//图片高
  sensor_msgs::ImagePtr msg;

  while (nh.ok()) 
  {
    capture.read(frame);
    if(frame.empty())
    {
        break;
        printf("cannot capture the image");
    }
    Mat frIn=frame;

    msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frIn).toImageMsg();//图像格式转换
 
    ros::Rate loop_rate(5);//每秒5帧

    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
  
}