# kuka_ipk
Repository based on [kuka_experimental](https://github.com/ros-industrial/kuka_experimental). Holds support files, moveit configurations and network configurations specific to the MTP laboratory.

## Prerequisite
* A working ROS Environment. ROS can be installed using [this guide](http://wiki.ros.org/lunar/Installation/Ubuntu)
* ros_control `sudo apt-get install ros-<distro>-ros-control ros-<distro>-ros-controllers`
* MoveIt! `sudo apt-get install ros-<distro>-moveit-full`

## Instructions
* Create and initialize a workspace, explained in [this ROS Tutorial](http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment)
* Navigate to `/your/workspace/src/`
* Run the following commands to install the packages:
```
git clone git@git.ipk.ivt.ntnu.no:adamleon/ironhide-robots.git
wstool init
wstool merge ironhide-robots/ironhide-robots.rosinstall
wstool update
cd ..
catkin_make
```

