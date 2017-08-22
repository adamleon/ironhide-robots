//
// Created by adamleon on 07.06.17.
//

#include "ros/ros.h"
#include "ironhide_robot_control/setTrajectoryAgili.h"
#include <cstdlib>
#include <sstream>

bool arg2bool(char* arg) {
    std::stringstream ss(arg);
    bool b;

    if(!(ss >> std::boolalpha >> b)) {
        ROS_INFO("Error in parsing argument");
        return false;
    }

    return b;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "ironhide_robot_control_test_client");
    if (argc != 3)
    {
        ROS_INFO("usage: ironhide_robot_control_test_client <bool> <bool>");
        return 1;
    }

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<ironhide_robot_control::setTrajectoryAgili>("ironhide_robot_control/agili/set_trajectory");
    ironhide_robot_control::setTrajectoryAgili srv;
    srv.request.execute = arg2bool(argv[1]);
    srv.request.absolute = arg2bool(argv[2]);
    if (client.call(srv))
    {
        ROS_INFO("Progress: %f", srv.response.progress);
    }
    else
    {
        ROS_ERROR("Failed to call service");
        return 1;
    }

    return 0;
}