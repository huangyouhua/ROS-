#include <ros/ros.h>
#include <string>
#include <vector>
#include <algorithm>
#include <pick_ball_mbot_msgs/BallPositionStamp.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Twist.h>
#include <pick_ball_mbot_msgs/void_obstacle.h>
#include <list>

#define LeftBoundary    200
#define RightBoundary   400
#define FilterFactor    0.2
#define Duaration       40

using namespace std;

geometry_msgs::Twist vel_msg;
uint duaration = 0; 
bool obstacle = false;

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

/*
* Set positions of most balls
*/
geometry_msgs::Point SetPositonGoal(const pick_ball_mbot_msgs::BallPositionStamp::ConstPtr &BallPositionStampMsg)
{
    vector<geometry_msgs::Point> BallPosition(BallPositionStampMsg->Position);
    vector<geometry_msgs::Point> LeftBalls;
    vector<geometry_msgs::Point> MidBalls;
    vector<geometry_msgs::Point> RightBalls;

    geometry_msgs::Point GoalPosition;

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
    return GoalPosition;
}

/*
* Find the nearest ball
*/
geometry_msgs::Point FindNearestPosition(const pick_ball_mbot_msgs::BallPositionStamp::ConstPtr &BallPositionStampMsg)
{
    vector<geometry_msgs::Point> BallPosition(BallPositionStampMsg->Position);

    geometry_msgs::Point GoalPosition;
    uint MaxCircleRadius = 0;
    size_t MaxCircleIndex = 0;

    /*find the nearest ball*/
    vector<geometry_msgs::Point>::iterator first = BallPosition.begin();
    for(vector<geometry_msgs::Point>::iterator it = BallPosition.begin(); it < BallPosition.end(); it++)
    {
        if(it->z > MaxCircleRadius)
        {
            MaxCircleRadius = it->z;
            MaxCircleIndex = distance(BallPosition.begin(),first);
        }
    }

    GoalPosition.x = BallPosition[MaxCircleIndex].x;
    GoalPosition.y = BallPosition[MaxCircleIndex].y;
    GoalPosition.z = BallPosition[MaxCircleIndex].z;

    return GoalPosition;
}

/* 
According to the position of balls or 
if there is obstacle to publish velocity 
*/
void PosCallback(const pick_ball_mbot_msgs::BallPositionStamp::ConstPtr &BallPositionStampMsg)
{
    static geometry_msgs::Point GoalPosition; 

    if(BallPositionStampMsg->Position.empty())
    {
        duaration++;
        duaration = duaration >= Duaration ? Duaration : duaration;
    }
    else
    {
        duaration = 0;
        
        //GoalPosition = SetPositonGoal(BallPositionStampMsg);
        GoalPosition = FindNearestPosition(BallPositionStampMsg);

        GoalPosition = PostionFilter(GoalPosition);
    }
    
    if(duaration==Duaration || obstacle)
    {
        vel_msg.linear.x = 0.0;
        vel_msg.angular.z = 0.8;
        return;
    }
    else
    {
        vel_msg.angular.z = 0.005 * (GoalPosition.x - 320);
        vel_msg.linear.x = 0.4;
    }

}

// obstacle 请求处理函数
bool handle_function(pick_ball_mbot_msgs::void_obstacle::Request &req,
					 pick_ball_mbot_msgs::void_obstacle::Response &res)
{

    if(req.obstacle)
        obstacle = true;
    else
        obstacle = false;

	res.result = true;

	return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "motion_planning");
    ros::NodeHandle nh;

    ros::Publisher VelMsg_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    ros::Subscriber BallPos_sub = nh.subscribe("/Ball/Position", 10, &PosCallback);
	ros::ServiceServer void_obstacle_service = nh.advertiseService("void_obstacle", handle_function);

    ros::Rate loop_rate(100); 

    while (nh.ok())
    {
        VelMsg_pub.publish(vel_msg);

        ros::spinOnce();
        loop_rate.sleep();
    }
}