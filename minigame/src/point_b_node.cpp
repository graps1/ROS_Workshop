#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>

ros::Subscriber sub_position;
ros::Publisher pub_position;

void callback(const geometry_msgs::PointStamped::ConstPtr &msg) {
  geometry_msgs::PointStamped pointStampedB;
  pointStampedB.point.x = msg->point.x + 5;
  pointStampedB.point.y = msg->point.y + 5;  
  pointStampedB.header.frame_id = "/map";
  pointStampedB.header.stamp = ros::Time::now();
  pub_position.publish(pointStampedB);  
}

/** Main node entry point. */
int main(int argc, char **argv)
{
  ros::init(argc, argv, "point_b_node");
  ros::NodeHandle nh;

  sub_position = nh.subscribe<geometry_msgs::PointStamped>("/positionA", 1, callback);
  pub_position = nh.advertise<geometry_msgs::PointStamped>("/positionB", 1);

  ros::spin();
  return 0;
}
