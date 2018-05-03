#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "visualization_msgs/Marker.h"

std::vector<geometry_msgs::Point> buffer;
ros::Publisher pub;

visualization_msgs::Marker createNewMarker() {
	visualization_msgs::Marker marker;
	marker.type = visualization_msgs::Marker::POINTS;
	marker.header.frame_id = "/map";
	marker.header.stamp = ros::Time::now();
	marker.points = buffer;
	marker.scale.x = 0.2;
  	marker.scale.y = 0.2;
	marker.color.g = 1.0f;
  	marker.color.a = 1.0f;
	return marker;
}

void callback (const geometry_msgs::Point::ConstPtr& msg) {
    if (buffer.size() < 10)
        buffer.push_back(*msg);
    
    if (buffer.size() == 10) {
        /* create and publish marker */
        pub.publish(createNewMarker());
        buffer.clear();
    }

}



int main(int argc, char **argv) {
    ros::init(argc, argv, "point_visualization_node");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<geometry_msgs::Point>("/points", 10, callback);
    pub = nh.advertise<visualization_msgs::Marker>("/points_vis", 1);
    ros::spin();
    return 0;
}