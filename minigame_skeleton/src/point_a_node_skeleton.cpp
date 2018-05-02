#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>
#include <dynamic_reconfigure/server.h>
#include <minigame_skeleton/point_a_nodeConfig.h>

ros::Publisher pub_position;
float current_pos_x;
float current_pos_y;

void callback(minigame_skeleton::point_a_nodeConfig &config, uint32_t level) {
  ROS_INFO("Reconfigure Request: x: %f y: %f", 
            config.current_pos_x, config.current_pos_y);

  current_pos_x = config.current_pos_x;
  current_pos_y = config.current_pos_y;  
  
}

/** Main node entry point. */
int main(int argc, char **argv)
{
    ros::init(argc, argv, "point_a_node");
    ros::NodeHandle nh;

    pub_position = nh.advertise<geometry_msgs::PointStamped>("/positionA", 1);
    dynamic_reconfigure::Server<minigame_skeleton::point_a_nodeConfig> server;
    dynamic_reconfigure::Server<minigame_skeleton::point_a_nodeConfig>::CallbackType f;

    f = boost::bind(&callback, _1, _2);
    server.setCallback(f);

    float start_x, start_y;
    nh.param("start_x", start_x);
    nh.param("start_y", start_y);
    current_pos_x = start_x;
    current_pos_y = start_y;    

    geometry_msgs::PointStamped pointStampedA;
    pointStampedA.header.frame_id = "/map";
    pointStampedA.point.x = start_x;
    pointStampedA.point.y = start_y;    

  	ros::Rate rate(100); // 10 hz    
    while (ros::ok()) {
      pointStampedA.header.stamp = ros::Time::now();
      pointStampedA.point.x = current_pos_x;
      pointStampedA.point.y = current_pos_y;    
      
      pub_position.publish(pointStampedA);
      rate.sleep();
      ros::spinOnce();
	  }
    return 0;
}
