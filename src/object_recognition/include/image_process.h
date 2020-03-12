#ifndef _IMAGE_PROCESS_H_
#define  _IMAGE_PROCESS_H_

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <stdio.h>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <string>
#include <utility>

using namespace cv;
using namespace std;

#define img_compress_width  640
#define img_compress_height 480
#define img_num  14
#define beg  0
#define end  14

#define iLowH        1
#define iHighH       30
#define iLowS        90
#define iHighS       255 
#define iLowV        189
#define iHighV       255 

#define g_nThresh    100   //137

vector<Mat> GetOriginalImg(const string img_path);
void showManyImages(vector<Mat>& src, Size imgSize);
Mat myfindContours(Mat image);
pair<Point3f, Mat> Table_Tennis_Pos(Mat img);

#endif 