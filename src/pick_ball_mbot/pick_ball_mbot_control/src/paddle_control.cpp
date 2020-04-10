#include <ros/ros.h>
#include <string>
#include <std_msgs/Float64.h>

std_msgs::Float64 paddle_velocity;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "paddle_control");
    ros::NodeHandle nh;

    ros::Publisher paddle_velocity_pub = nh.advertise<std_msgs::Float64>("/paddle_velocity", 10);

    ros::Rate loop_rate(100); //定义发布频率

    paddle_velocity.data = 5.0;

    while (nh.ok())
    {
        paddle_velocity_pub.publish(paddle_velocity);

        ros::spinOnce();
        loop_rate.sleep();
    }
}