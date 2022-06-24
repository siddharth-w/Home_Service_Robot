# Home_Service_Robot

**Packages Used:**

1) **turtlebot_teleop:**
Package to control your bot's movement using keyboard inputs.
2) **turtlebot_gazebo:**
Package to deploy the turtle bot in a gazebo environment after linking your world file saved in the /src/map/ directory. 
3) **turtlebot_rviz_launchers:**
Package to visualize your robot's movement in an environment using a pre-configured rviz workspace.
4) **gmapping:**
This package provides laser based Simultaneous Localization and Mapping (SLAM), with the help of its ros node slam_gmapping. It takes laser and odometry data from the robot and creates a 2D occupancy grid map. The slam_gmapping node takes in sensor_msgs/LaserScan and creates a map output being nav_msgs/OccupancyGrid. An alternative of gmapping is the gmapping_demo in the turtlebot_gazebo package. 
5) **add_markers:**
Custom package created to add virtual objects at pre-defined positions. The objects/markers will be published in the rviz workspace and will appear and disappear corresponding to the robot's position and the pick_objects node. The add_markers package has a subscriber node add_markers subscribing to the publisher node pick_objects2 in pick_objects. The node add_markers places a marker at the defined position corresponding to the position and movement of the robot. The add_markers3 node creates markers at two given positions in a specified interval irrespective of the robots position and the pick_objects node.
6) **pick_objects:**
This custom package is used to give goals to the robot.The pick_objects2 node publishes the robots pose to the add_markers2 node, as soon as the robot reaches the first goal the markers vanishes and the add_markers2 node creates a new marker at the second goal and the robot is given a new destination. After sending the goals, the robot will create a path to the marker's location combining both localization and navigation. 

**Working:**
1) Test SLAM using /src/scripts/test_slam.sh, this will deploy a turtlebot in your preferred world and visualize using rviz. Teleoperate your bot using the turtlebot_teleop package to create a map for your world using the gmapping_demo launch file in the turtlebot_gazebo package.
2) Test navigation and localization using /src/scripts/test_navigation.sh . It will deploy the turtlebot in the given environment and launch rviz for visualization. Use 2D NAV Goal to move the bot in your environment, it will implement AMCL and Dijkstra's algorithm for localization and path planning respectively.
3) Give your bot goals using /src/scripts/pick_objects.sh and test test localization and mapping. The pick_objects.sh will give two goals to the turtlebot namely the pic-up zone and drop-off zone.
4) Use /src/scripts/add_markers.sh to test your virtual objects in rviz, the object should disappear and re-appear corresponding to the add_markers3 node in the add_markers package.
5) Combine all the above into your /src/scripts/home_service.sh . A turtlebot will be deployed in your environment and will be visualized in rviz. A marker will appear in your given position and the bot will be given a corresponding goal, the using the amcl_demo launch file it will plan its path to the goal, afterreaching the goal the bot will wait for 5sec and the marker will vanish from the first goal, and the bot will move on to the next goal given as the drop-off zone where the marker will re-appear after the bot reaches there. 
