//
// Created by adamleon on 06.06.17.
//

#include "ros/ros.h"
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include "ironhide_robot_control/setTrajectoryAgili.h"

bool set_trajectory(ironhide_robot_control::setTrajectoryAgili::Request  &req,
         ironhide_robot_control::setTrajectoryAgili::Response &res)
{

    res.progress = 0.5f;
    ROS_INFO("request: execute=%s, absolute=%s", req.execute ? "true" : "false", req.absolute ? "true" : "false");
    return true;
}

double calculate_waypoints(std::vector<geometry_msgs::Pose> agilus_1_poses, std::vector<geometry_msgs::Pose> agilus_2_poses) {
    moveit::planning_interface::MoveGroupInterface group("both_agili");
    double eef_step, jump_threshold;
    ros::param::get("trajectory_parameters/eef_step", eef_step);
    ros::param::get("trajectory_parameters/jump_threshold", jump_threshold);
    moveit_msgs::RobotTrajectory trajectory;
    ROS_INFO("Waypoint Received");
    double fraction = group.computeCartesianPath(agilus_1_poses, eef_step, jump_threshold, trajectory);
    if(fraction < 1) {
        ROS_WARN("Trajectory not fully feasible; only the first %f%% is feasible.", 100*fraction);
    }
    else {
        ROS_INFO("Trajectory successfully planned");
    }
    return fraction;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "ironhide_robot_control");
    ros::NodeHandle n;
    double eef_step = 0.01, jump_threshold = 0.0;
    ros::param::get("trajectory_parameters/eef_step", eef_step);
    ros::param::get("trajectory_parameters/jump_threshold", jump_threshold);

    ros::ServiceServer service = n.advertiseService("ironhide_robot_control/agili/set_trajectory", set_trajectory);
    ROS_INFO("Ready to receive waypoints.");
    ros::spin();

    return 0;
}