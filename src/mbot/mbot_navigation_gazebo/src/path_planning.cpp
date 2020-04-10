#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "std_msgs/String.h"
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/Point.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <gazebo_msgs/ModelStates.h>
#include <ros/ros.h>
#include <vector>

using namespace std;

bool GoalSucceeded = true;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

typedef struct _POSE
{
    double X;
    double Y;
    double Z;
    double or_x;
    double or_y;
    double or_z;
    double or_w;
} POSE;

typedef struct _POSITION
{
    double X;
    double Y;
    double Z;
} POSITION;

// vector<POSITION> base_link_pose({-4, 2, 0}, {-3, 2, 0}, {-2, 2, 0}, {-1, 2, 0}, {0, 2, 0}, {1, 2, 0}, {2, 2, 0}, {3, 2, 0}, {4, 2, 0}, {5, 2, 0}, {6, 2, 0}, {6, 1, 0}, {6, 0, 0}, {6, -1, 0}, {6, -2, 0}, {5, -2, 0}, {4, -2, 0}, {3, -2, 0}, {2, -2, 0}, {1, -2, 0}, {0, -2, 0}, {-1, -2, 0}, {-2, -2, 0}, {-3, -2, 0}, {-4, -2, 0}, {-4, -1, 0}, {-4, 0, 0}, {-4, 1, 0});
// base_link_pose.push_back()
POSITION position0 = {-4.0, 2.0, 0.0};
POSITION position1 = {-3.0, 2.0, 0.0};
POSITION position2 = {-2, 2, 0};
POSITION position3 = {-1, 2, 0};
POSITION position4 = {0, 2, 0};
POSITION position5 = {1, 2, 0};
POSITION position6 = {2, 2, 0};
POSITION position7 = {3, 2, 0};
POSITION position8 = {4, 2, 0};
POSITION position9 = {5, 2, 0};
POSITION position10 = {6, 2, 0};
// vector<POSITION> base_link_pose(position0, position1, position2, position3, position4, position5, position6, position7, position8, position9, position10);
vector<POSITION> base_link_pose;


void setGoal()
{
    //tell the action client that we want to spin a thread by default
    MoveBaseClient ac("move_base", true);

    //wait for the action server to come up
    while (!ac.waitForServer(ros::Duration(5.0)))
    {
        ROS_WARN("Waiting for the move_base action server to come up");
    }

    move_base_msgs::MoveBaseGoal goal;

    //we'll send a goal to the robot to move 1 meter forward

    ROS_INFO("Sending goal");

    for(size_t i = 0; i < 10; i++)
    {
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();

        goal.target_pose.pose.position.x = base_link_pose[i].X;
        goal.target_pose.pose.position.y = base_link_pose[i].Y;
        goal.target_pose.pose.position.z = base_link_pose[i].Z;
        goal.target_pose.pose.orientation.x = 0;
        goal.target_pose.pose.orientation.y = 0;
        goal.target_pose.pose.orientation.z = 0;
        goal.target_pose.pose.orientation.w = 1;

        if(GoalSucceeded)
        {
            GoalSucceeded = false;
            ac.sendGoal(goal);
        }
        else 
            continue;
    
        ac.waitForResult();

        if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        {
            GoalSucceeded = true;
            ROS_INFO("it is successful");
        }
        else
            ROS_ERROR("The base failed  move to goal!!!");

        }
}

void poseCallback(const gazebo_msgs::ModelStates::ConstPtr &msg)
{
    ROS_INFO_STREAM("Topic is Subscriber");
    //setGoal(pose1);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "path_planning");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/base_link/pose_topic", 10, poseCallback);

    ros::Rate rate_loop(10);

    base_link_pose.push_back(position0);
    base_link_pose.push_back(position1);
    base_link_pose.push_back(position2);
    base_link_pose.push_back(position3);
    base_link_pose.push_back(position4);
    base_link_pose.push_back(position5);
    base_link_pose.push_back(position6);
    base_link_pose.push_back(position7);
    base_link_pose.push_back(position8);
    base_link_pose.push_back(position9);
    base_link_pose.push_back(position10);

    while (ros::ok())
    {
        setGoal();
        ros::spinOnce();
    }

    return 0;
}