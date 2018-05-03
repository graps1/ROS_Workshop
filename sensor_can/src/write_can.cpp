#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "can_msgs/Frame.h"

ros::Publisher pub;

void callback (const std_msgs::Int32::ConstPtr& msg) {
    can_msgs::Frame frame;
    frame.header.stamp = ros::Time::now();
    frame.id = 0x123;   //can id
    frame.dlc = 2;      //two bytes long*/
    frame.data[0] = (msg->data & 0xff00) >> 8;
    frame.data[1] =  msg->data & 0x00ff;
    pub.publish(frame);
}

int main (int argc, char **argv) {
    ros::init(argc, argv, "write_can_node");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<std_msgs::Int32>("/sensor_input", 1, callback);
    pub = nh.advertise<can_msgs::Frame>("/received_msgs", 1);
    ros::spin();
    return 0;
}