#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/Header.h"


geometry_msgs::Point createPoint(double x, double y, double z) {
	geometry_msgs::Point point;
	point.x = x;
	point.y = y;
	point.z = z;
	return point;
}

std::vector<geometry_msgs::Point> createPointList() {
	std::vector<geometry_msgs::Point> list;
	for (int i=0; i<10; i++) {
		double secs = ros::Time::now().toSec();
		double x = sin(secs + (i / 5.0) * 3.1415);
		double y = cos(secs + (i / 5.0) * 3.1415);
		list.push_back(createPoint(x, y, 0));
	}
	return list;
}

visualization_msgs::Marker createNewMarker() {
	visualization_msgs::Marker marker;
	marker.type = visualization_msgs::Marker::POINTS;
	marker.header.frame_id = "/map";
	marker.header.stamp = ros::Time::now();
	marker.points = createPointList();
	marker.scale.x = 0.2;
  	marker.scale.y = 0.2;
	marker.color.g = 1.0f;
  	marker.color.a = 1.0f;
	return marker;
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "point_publisher_node");

	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<visualization_msgs::Marker>("/bouncing_point", 1);
	
	ros::Rate rate(100); // 10 hz

	while (ros::ok()) {
		pub.publish(createNewMarker());
		ROS_INFO("Published points.");
		rate.sleep();
		ros::spinOnce();
	}
	
	return 0;
}
