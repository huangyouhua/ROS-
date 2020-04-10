#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "std_msgs/String.h"
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Pose.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <gazebo_msgs/ModelStates.h>
#include <pick_ball_mbot_msgs/PathPlanning.h>
#include <ros/ros.h>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>

using namespace std;

geometry_msgs::Pose base_link_pose;
string robot_name = "mbot";
bool LastGoalSucceeded = false;
bool PathRequest = false; 
bool GetPose = false;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

vector<geometry_msgs::Point> PrePath;

double PointDistance(const geometry_msgs::Point p1, const geometry_msgs::Point p2)
{
    return sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2));
}

void PrePathPlannig()
{
    geometry_msgs::Point position;
    int num = -4;
    for(size_t i = 0; i < 11; i++)
    {
        position.x = -4 + i;
        position.y = 2;
        position.z = 0;
        PrePath.push_back(position);
    }
    for(size_t i = 0; i < 4; i++)
    {
        position.x = 6;
        position.y = 1 - i;
        position.z = 0;
        PrePath.push_back(position);
    }
    for(size_t i = 0; i < 10; i++)
    {
        position.x = 5 - i;
        position.y = -2;
        position.z = 0;
        PrePath.push_back(position);
    }
    for(size_t i = 0; i < 3; i++)
    {
        position.x = -4;
        position.y = -1 + i;
        position.z = 0;
        PrePath.push_back(position);
    }
}

//find the nearest pre plannig path point
pair<size_t, double> GetNearestPointIndex()
{
    static size_t LastNearestPointIndex = 0;
    double Distance = 0;
    size_t Index = 0;
    size_t NearestPointIndex = 0;
    pair<vector<size_t>, vector<double> > IndexDistance;//save index and distance
    vector<geometry_msgs::Point>::iterator first = PrePath.begin();
    for(vector<geometry_msgs::Point>::iterator it = PrePath.begin(); it < PrePath.end(); it++)
    {
        Distance = PointDistance(*it, base_link_pose.position);
        Index = distance(first, it);
        IndexDistance.first.push_back(Index);
        IndexDistance.second.push_back(Distance);
    }
        
    NearestPointIndex = min_element(IndexDistance.second.begin(),IndexDistance.second.end()) - IndexDistance.second.begin();
    ROS_INFO("NearestPointIndex =  %d size : %d", NearestPointIndex, IndexDistance.second.size());
    //ROS_INFO_STREAM("Position:" << std::endl << base_link_pose);
    if(LastGoalSucceeded)
    {
        IndexDistance.first.erase(IndexDistance.first.begin() + NearestPointIndex - 1);
        IndexDistance.second.erase(IndexDistance.second.begin() + NearestPointIndex - 1);
        NearestPointIndex = min_element(IndexDistance.second.begin(),IndexDistance.second.end()) - IndexDistance.second.begin();
        ROS_INFO("NearestPointIndex =  %d size : %d", NearestPointIndex, IndexDistance.second.size());
    }

    LastNearestPointIndex = NearestPointIndex;

    return {NearestPointIndex, IndexDistance.second[NearestPointIndex]};
}

void setGoal()
{
    //tell the action client that we want to spin a thread by default
    MoveBaseClient ac("move_base", true);

    //wait for the action server to come up
    while (!ac.waitForServer(ros::Duration(5.0)))
    {
        ROS_WARN("Waiting for the move_base action server to come up");
    }

    pair<size_t, double> IndexDistance = GetNearestPointIndex();
    size_t NearestPointIndex = IndexDistance.first;
    double Distance = IndexDistance.second;
    //size_t NearestPointIndex = GetNearestPointIndex();
    // set navigation goal
    move_base_msgs::MoveBaseGoal goal;
   
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = PrePath[NearestPointIndex].x;
    goal.target_pose.pose.position.y = PrePath[NearestPointIndex].y;
    goal.target_pose.pose.position.z = PrePath[NearestPointIndex].z;
    goal.target_pose.pose.orientation.x = base_link_pose.orientation.x;
    goal.target_pose.pose.orientation.y = base_link_pose.orientation.y;
    goal.target_pose.pose.orientation.z = base_link_pose.orientation.z;
    goal.target_pose.pose.orientation.w = base_link_pose.orientation.w;
    
    LastGoalSucceeded = false; //clear flag
    ac.sendGoal(goal);
    ROS_INFO("Sending %d th goal, distance is %f", NearestPointIndex, Distance);

    ac.waitForResult();

    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
        LastGoalSucceeded = true;
        ROS_INFO("it is successful");
    }
    else
    {
        LastGoalSucceeded = false;
        ROS_ERROR("The base failed  move to goal!!!");
    }   
}

void poseCallback(const gazebo_msgs::ModelStates::ConstPtr &ModelState)
{
    int box_index = -1;
    std::vector<std::string> model_names = ModelState->name;

    for(size_t i = 0; i < model_names.size(); i++)
    {
        if(model_names[i] == robot_name)
        {
             box_index = i;
             break;
        } 
    }
    base_link_pose = ModelState->pose[box_index];
    GetPose = true;
}

bool handle_function(pick_ball_mbot_msgs::PathPlanning::Request &req,
					 pick_ball_mbot_msgs::PathPlanning::Response &res)
{

    if(req.Request)
    {
        PathRequest = true;
        res.Result = true;
        
    } 
    else
        PathRequest = false;

	return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "path_planning");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/base_link/pose_topic", 10, poseCallback);
    ros::ServiceServer PathPlanning_service = nh.advertiseService("PathPlanning", handle_function);

    bool ifget = nh.getParam("/path_planning/robot_name",robot_name);
    if(ifget)
        ROS_INFO("Get robot_name = %s", robot_name.c_str());
    else
        ROS_WARN("Didn't retrieve robot_name");

    ros::Rate rate_loop(10);

    PrePathPlannig();

    while (ros::ok())
    {
        if(PathRequest && GetPose)
        {
            PathRequest = false;
            setGoal();
        }

        ros::spinOnce();
    }

    return 0;
}