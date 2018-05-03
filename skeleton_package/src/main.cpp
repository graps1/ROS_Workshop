#include "ros/ros.h"


void Callback (...){
    
}

int main (int argc, char **argv) {
    
    ros::init(argc, argv, "skeleton_node");
    ros::NodeHandle nh;

    // ros::Publisher pub = nh.advertise<data::type>("/topic_name", 1);
    // ros::Subscriber sub = handle.subscribe("/topic_Name", 100, Callback);
    

    while (ros::ok()) {
        //code ...

        ros::spinOnce();
    }

    return 0;
}

