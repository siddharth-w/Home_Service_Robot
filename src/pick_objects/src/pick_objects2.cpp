#include <std_msgs/String.h>
#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
int main(int argc, char** argv){

  ros::init(argc, argv, "pick_objects2");

  ros::NodeHandle n;
  ros::Publisher robot_loc_pub = n.advertise<std_msgs::String>("/pick_objects/robot_location", 1);
  std_msgs::String robot_loc_msg;


  MoveBaseClient ac("move_base", true);


  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;


  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();


  goal.target_pose.pose.position.x = 3.0;
  goal.target_pose.pose.position.y = -2.0;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("Reached pickup zone");
    robot_loc_msg.data = "pick_up";
    robot_loc_pub.publish(robot_loc_msg);    
  }
  else {
    ROS_INFO("Failed to reach the pickup zone");
  }


  ros::Duration(3.0).sleep();


  move_base_msgs::MoveBaseGoal goal2;


  goal2.target_pose.header.frame_id = "map";
  goal2.target_pose.header.stamp = ros::Time::now();


  goal2.target_pose.pose.position.x = -5.0;
  goal2.target_pose.pose.position.y = 0.0;
  goal2.target_pose.pose.orientation.w = 1.0;


  ac.sendGoal(goal2);


  ac.waitForResult();


  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("Reached the drop off zone");
    robot_loc_msg.data = "drop_off";
    robot_loc_pub.publish(robot_loc_msg);    
  }
  else {
    ROS_INFO("Failed to reach the drop off zone");
  }

  return 0;
}
