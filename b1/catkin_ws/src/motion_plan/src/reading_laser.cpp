#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <vector>
#include <string>
#include <algorithm>

void laserCallBack(const sensor_msgs::LaserScan::ConstPtr& msg){ 
//cout << msg; 


std::vector<float> regions; 
  regions.push_back(*(std::min_element(&msg->ranges[0],&msg->ranges[143])) ); 
  regions.push_back(*(std::min_element(&msg->ranges[144],&msg->ranges[287])) );
  regions.push_back(*(std::min_element(&msg->ranges[288],&msg->ranges[431])) );
  regions.push_back(*(std::min_element(&msg->ranges[432],&msg->ranges[575])) );
  regions.push_back(*(std::min_element(&msg->ranges[576],&msg->ranges[713])) );


std::string s; 
s += "lr "; 
for( auto i : regions)
s += std::to_string(i)+ " ";
 ROS_INFO_STREAM(s);

} 

int main(int argc, char ** argv) { 

  ros::init(argc, argv, "reading_laser"); 
 // ros
ros::NodeHandle n;

  ros::Subscriber sub1 = n.subscribe("m2w/laser/scan", 1000, &laserCallBack);

  ros::spin();

  return 0;
} 
