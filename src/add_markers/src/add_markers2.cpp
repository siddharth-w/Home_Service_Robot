#include <std_msgs/String.h>
#include <visualization_msgs/Marker.h>
#include <ros/ros.h>

ros::Publisher marker_pub;
visualization_msgs::Marker marker;

void modify_marker_callback(const std_msgs::String msg)
{
  if (msg.data == "pick_up") {
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    ROS_INFO("Object picked");
  } else if (msg.data == "drop_off") {
    marker.pose.position.x = -5.0;
    marker.pose.position.y = 0.0;
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    ROS_INFO("Object dropped");
  } else {
    ROS_ERROR("Message Invalid");
  }
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers2");
  ros::NodeHandle n;
  ros::Rate r(1);

  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1, true);

  uint32_t shape = visualization_msgs::Marker::CUBE;

  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  marker.ns = "pick_up_object";
  marker.id = 0;


  marker.type = shape;

  marker.action = visualization_msgs::Marker::ADD;


  marker.pose.position.x = 3.0;
  marker.pose.position.y = -2.0;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  marker.scale.x = 0.5;
  marker.scale.y = 0.5;
  marker.scale.z = 0.5;

  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();

  ROS_INFO("Object at the pickup zone");
  marker_pub.publish(marker);

  ros::Subscriber robot_loc_sub = n.subscribe("/pick_objects/robot_location", 1, modify_marker_callback);

  ros::spin();

  return 0;
}
