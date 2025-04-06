#!/bin/bash

source /opt/ros/noetic/setup.bash
echo '\nSourced ROS1, time to run roscore\n'
roscore &
echo '\n roscore is combusting...\n'
gnome-terminal -- bash -c "bash Bridge.sh; exec bash"
