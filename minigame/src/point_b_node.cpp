#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>


ros::Publisher pub_position;

/** Main node entry point. */
int main(int argc, char **argv)
{

  //node initialisieren
  ros::init(argc, argv, "point_b_node");
  ros::NodeHandle nh;

  //publisher definieren 
  pub_position = nh.advertise<geometry_msgs::PointStamped>("/positionB", 1);

  //PunktB erstellen
  geometry_msgs::PointStamped pointStampedB;
  pointStampedB.header.frame_id = "/map";

  //fängt in punkt 0,0 an
  pointStampedB.point.x = 0;
  pointStampedB.point.y = 0; 

  ros::Rate rate(2); // 2 hz
  while (ros::ok()) {

    //set new random position
    pointStampedB.point.x += ( (rand() % 100) / 50.0 ) - 1.0;
    pointStampedB.point.y += ( (rand() % 100) / 50.0 ) - 1.0;  
      
    //publish point  
    pointStampedB.header.stamp = ros::Time::now();
    pub_position.publish(pointStampedB); 
    rate.sleep(); 
    ros::spinOnce();
	  
  }
  return 0;
}
