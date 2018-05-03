#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>


ros::Publisher pub_position;
float current_pos_x;
float current_pos_y;
float start_x, start_y;

/** Main node entry point. */
int main(int argc, char **argv)
{
    
    //initialisiere Node
    ros::init(argc, argv, "point_a_node");
    ros::NodeHandle nh;

    //create publisher for PointA
    pub_position = nh.advertise<geometry_msgs::PointStamped>("/positionA", 1);

    
    
    //das sollen die veränderbaren startpunkte werden
    start_x = 0;
    start_y = 0;
  

    //das sollen die dynamisch rekonfigurierbaren Punkte werden
    current_pos_y = 0;
    current_pos_x = 0;  

    //PunktA erstellen
    geometry_msgs::PointStamped pointStampedA;
    pointStampedA.header.frame_id = "/map"; 

  	ros::Rate rate(10); // 10 hz    
   
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
