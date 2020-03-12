#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <string>

using namespace std;
geometry_msgs::Twist vel_msg;

void PosCallback(const geometry_msgs::PointStamped::ConstPtr &msg)
{
    /*根据识别到的小球位置发布速度信息 */
    vel_msg.angular.z = 0.01 * (msg->point.x - 320);
    vel_msg.linear.x = 0.1;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "table_tennis");
    ros::NodeHandle nh;

    ros::Publisher mbot_vel = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    ros::Subscriber sub = nh.subscribe("/Ball/Pos", 10, &PosCallback);

    ros::Rate loop_rate(30); //定义发布频率

    while (nh.ok())
    {
        mbot_vel.publish(vel_msg);

        ros::spinOnce();
        loop_rate.sleep();
    }
}