#!/bin/sh
xterm  -e  " source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find pick_objects)/../map/world.world" &
sleep 5
xterm  -e  " source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find pick_objects)/../map/map.yaml" &
sleep 5
xterm  -e  " source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation_with_markers.launch" &
sleep 5
xterm  -e  " source devel/setup.bash; rosrun add_markers add_markers" &
sleep 5
xterm  -e  " source devel/setup.bash; roslaunch pick_objects pick_objects2.launch"
