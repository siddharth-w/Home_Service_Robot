#!/bin/sh
xterm  -e  " source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find pick_objects)/../map/world.world" &
sleep 5
xterm  -e  " source devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 5
xterm  -e  " source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm  -e  " source devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch"
