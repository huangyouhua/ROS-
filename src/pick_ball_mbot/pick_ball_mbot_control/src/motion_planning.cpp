#include <ros/ros.h>
#include <string>
#include <vector>
#include <algorithm>
#include <ball_msgs/BallPositionStamp.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Twist.h>

#define LeftBoundary    200
#define RightBoundary   400
#define FilterFactor    0.2

using namespace std;
geometry_msgs::Twist vel_msg;
geometry_msgs::Point GoalPosition;

geometry_msgs::Point PostionFilter(geometry_msgs::Point BallPosition)
{   
    static geometry_msgs::Point LastPosition;
    geometry_msgs::Point Position;

    Position.x = (1 - FilterFactor)*BallPosition.x + FilterFactor * LastPosition.x;
    Position.y = (1 - FilterFactor)*BallPosition.y + FilterFactor * LastPosition.y;
    Position.z = (1 - FilterFactor)*BallPosition.z + FilterFactor * LastPosition.z;

    LastPosition = Position;

    return Position;
}

geometry_msgs::Point CalculatePostion(vector<geometry_msgs::Point> BallPosition)
{
    double XPosition = 0;
    double YPosition = 0;
    double ZPosition = 0;
    geometry_msgs::Point Position;

    for(vector<geometry_msgs::Point>::iterator it = BallPosition.begin(); it < BallPosition.end(); it++)
    {
        XPosition += it->x;
        YPosition += it->y;
        ZPosition += it->z;
    }

    Position.x = XPosition/BallPosition.size();
    Position.y = YPosition/BallPosition.size();
    Position.z = ZPosition/BallPosition.size();

    return Position;
}

void SetPositonGoal(const ball_msgs::BallPositionStamp::ConstPtr &BallPositionStampMsg)
{
     if(BallPositionStampMsg->Position.empty())
        return;

    vector<geometry_msgs::Point> BallPosition(BallPositionStampMsg->Position);
    vector<geometry_msgs::Point> LeftBalls;
    vector<geometry_msgs::Point> MidBalls;
    vector<geometry_msgs::Point> RightBalls;

    size_t maxsize = 0;

    /*Divide the balls into different areas*/
    for(vector<geometry_msgs::Point>::iterator it = BallPosition.begin(); it < BallPosition.end(); it++)
    {
        if(it->x < LeftBoundary)
            LeftBalls.push_back(*it);
        else if(it->x > RightBoundary)
            RightBalls.push_back(*it);
        else
            MidBalls.push_back(*it);
    }

    maxsize = max(LeftBalls.size(), RightBalls.size());
    maxsize = max(maxsize, MidBalls.size());

    if(maxsize == LeftBalls.size() && maxsize == MidBalls.size() && maxsize == RightBalls.size())
        GoalPosition = CalculatePostion(MidBalls);

    else if(maxsize == LeftBalls.size() && maxsize == MidBalls.size())
        GoalPosition = CalculatePostion(MidBalls);

    else if(maxsize == MidBalls.size() && maxsize == RightBalls.size())
        GoalPosition = CalculatePostion(MidBalls);

    else if(maxsize == LeftBalls.size() && maxsize == RightBalls.size())
        GoalPosition = CalculatePostion(LeftBalls);

    else
    {
        if(maxsize == LeftBalls.size())
            GoalPosition = CalculatePostion(LeftBalls);

        else if(maxsize == MidBalls.size())
            GoalPosition = CalculatePostion(MidBalls);

        else 
            GoalPosition = CalculatePostion(RightBalls);
    }
}

void PosCallback(const ball_msgs::BallPositionStamp::ConstPtr &BallPositionStampMsg)
{
    SetPositonGoal(BallPositionStampMsg);

    GoalPosition = PostionFilter(GoalPosition);

    /* According to the position of balls to publish velocity */
    vel_msg.angular.z = 0.1 * (GoalPosition.x - 320);
    vel_msg.linear.x = 0.3;

}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "motion_planning");
    ros::NodeHandle nh;

    ros::Publisher VelMsg_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    ros::Subscriber BallPos_sub = nh.subscribe("/Ball/Position", 10, &PosCallback);

    /* define the publish frequency */
    ros::Rate loop_rate(30); 

    while (nh.ok())
    {
        VelMsg_pub.publish(vel_msg);

        ros::spinOnce();
        loop_rate.sleep();
    }
}