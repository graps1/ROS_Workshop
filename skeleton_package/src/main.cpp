#include "ros/ros.h"

int main (int argc, char **argv) {
    ros::init(argc, argv, "skeleton_node");
    ros::NodeHandle nh;

    while (ros::ok()) {
        //code ...

        ros::spinOnce();
    }

    return 0;
}