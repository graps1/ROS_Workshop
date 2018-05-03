#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>
#include <dynamic_reconfigure/server.h>
#include <minigame/point_a_nodeConfig.h>

ros::Publisher pub_position;
float current_pos_x;
float current_pos_y;

//callback für dynamische rekonfiguration
void callback(minigame::point_a_nodeConfig &config, uint32_t level) {
  //kleine Info
  ROS_INFO("Reconfigure Request: x: %f y: %f", 
            config.current_pos_x, config.current_pos_y);

  //neue Parameter setzen
  current_pos_x = config.current_pos_x;
  current_pos_y = config.current_pos_y;  
  
}

/** Main node entry point. */
int main(int argc, char **argv)
{
    
    //initialisiere Node
    ros::init(argc, argv, "point_a_node");
    ros::NodeHandle nh;

    //create publisher
    pub_position = nh.advertise<geometry_msgs::PointStamped>("/positionA", 1);

    //initialisire dynamic_reconfigure server
    dynamic_reconfigure::Server<minigame::point_a_nodeConfig> server;
    dynamic_reconfigure::Server<minigame::point_a_nodeConfig>::CallbackType f;

    //callback binden
    f = boost::bind(&callback, _1, _2);
    server.setCallback(f);

    //veränderbare startpunkte
    float start_x, start_y;
    nh.param("start_x", start_x);
    nh.param("start_y", start_y);

    //dynamisch rekonfigurierbare Punkte
    current_pos_x = start_x;
    current_pos_y = start_y;    

    //PunktA erstellen
    geometry_msgs::PointStamped pointStampedA;
    pointStampedA.header.frame_id = "/map"; 

  	ros::Rate rate(100); // 10 hz    
    while (ros::ok()) {
      pointStampedA.header.stamp = ros::Time::now();
      
      //dynamisch rekonfigurierbare werte schreiben
      pointStampedA.point.x = current_pos_x;
      pointStampedA.point.y = current_pos_y;    
      
      //publishen
      pub_position.publish(pointStampedA);
      rate.sleep();
      ros::spinOnce();
	  }
    return 0;
}
