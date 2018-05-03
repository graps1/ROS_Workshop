#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/Header.h"

ros::Publisher pub;

geometry_msgs::Point createPoint(double x, double y, double z) {
	geometry_msgs::Point point;
	point.x = x;
	point.y = y;
	point.z = z;
	return point;
}

void publishPointList() {
	for (int i=0; i<10; i++) {
		double secs = ros::Time::now().toSec();
		double x = sin(secs + (i / 5.0) * 3.1415);
		double y = cos(secs + (i / 5.0) * 3.1415);
		pub.publish(createPoint(x,y,0));	
	}
}


int main(int argc, char **argv) {
	ros::init(argc, argv, "point_publisher_node");

	ros::NodeHandle nh;
	pub = nh.advertise<geometry_msgs::Point>("/points", 10);
	
	ros::Rate rate(100); // 100 hz

	while (ros::ok()) {
		publishPointList();
		ROS_INFO("Published points.");
		rate.sleep();
		ros::spinOnce();
	}
	
	return 0;
}
