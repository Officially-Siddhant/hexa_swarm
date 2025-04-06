#!/bin/bash
export ROS_MASTER_URI=http://localhost:11311  
echo ''
echo 'ROS MASTER SET'
echo ''
source /opt/ros/foxy/setup.bash
echo ''
echo '----FOXY----'
source /home/siddhant/ros_bridge_ws/install/setup.bash
echo ''
echo '----sourced bridge workspace----'
echo ''
ros2 run ros1_bridge dynamic_bridge
echo ''
echo '----Bridge is Alive------'
