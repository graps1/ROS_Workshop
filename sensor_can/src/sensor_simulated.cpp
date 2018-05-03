#include "ros/ros.h"
#include "std_msgs/Int32.h"

std_msgs::Int32 createRandomData() {
    std_msgs::Int32 msg;
    msg.data = rand() % 30000;
    ROS_INFO("%i", msg.data);
    return msg;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "sensor_simulated_node");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::Int32> ("/sensor_input", 1);

    ros::Rate rate(10); // publish with a frequency of 10 Hz --> 1 message each 100 ms
    while (ros::ok()) {
        pub.publish(createRandomData());
        rate.sleep();
        ros::spinOnce();
    }

    return 0;
}