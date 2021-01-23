#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

#include <vector>
#include <string>
#include <algorithm>

//put this in a clas
ros::Publisher pub1;

enum {
  RIGHT,
  FRIGHT,
  FRONT,
  FLEFT,
  LEFT
};
  float mymin( float a, float b) { 

    if(a < b) 
      return a; 
    else 
      return b;

  }

void takeAction( std::vector<float> regions) { 
	geometry_msgs::Twist msg; 

float  linear_x = 0;
  float  angular_z = 0;

   std::string state_description;


if( (regions[FRONT] > 1) && (regions[FLEFT] > 1) && (regions[FRIGHT] > 1)){
        state_description = "case 1 - nothing";
        linear_x = 0.6;
        angular_z = 0;
}
    else if (regions[FRONT] < 1 && regions[FLEFT] > 1 && regions[FRIGHT] > 1){
        state_description = "case 2 - front";
        linear_x = 0;
        angular_z = -0.3;
}
    else if (regions[FRONT] > 1 && regions[FLEFT] > 1 && regions[FRIGHT] < 1){
        state_description = "case 3 - fright";
        linear_x = 0;
        angular_z = -0.3;
    }else if (regions[FRONT] > 1 && regions[FLEFT] < 1 && regions[FRIGHT] > 1){
        state_description = "case 4 - fleft";
        linear_x = 0;
        angular_z = 0.3;
    }else if (regions[FRONT] < 1 && regions[FLEFT] > 1 && regions[FRIGHT] < 1){
        state_description = "case 5 - front and fright";
        linear_x = 0;
        angular_z = -0.3;
    }else if (regions[FRONT] < 1 && regions[FLEFT] < 1 && regions[FRIGHT] > 1){
        state_description = "case 6 - front and fleft";
        linear_x = 0;
        angular_z = 0.3;
    }else if( regions[FRONT] < 1 && regions[FLEFT] < 1 && regions[FRIGHT] < 1){
        state_description = "case 7 - front and fleft and fright";
        linear_x = 0;
        angular_z = -0.3;
   } else if ( regions[FRONT] > 1 && regions[FLEFT] < 1 && regions[FRIGHT] < 1){
        state_description = "case 8 - fleft and fright";
        linear_x = 0;
        angular_z = -0.3;
   } else{
        state_description = "unknown case";
       // rospy.loginfo(regions);
}
    ROS_INFO_STREAM(state_description);
    msg.linear.x = linear_x;
    msg.angular.z = angular_z;
    pub1.publish(msg);
  
}

void laserCallBack(const sensor_msgs::LaserScan::ConstPtr& msg){ 
  //cout << msg; 
  
  std::vector<float> regions; 
  regions.push_back( mymin( *(std::min_element(&msg->ranges[0],&msg->ranges[143]))  , 10.0) ); 
  regions.push_back( mymin( *(std::min_element(&msg->ranges[144],&msg->ranges[287])), 10.0) );
  regions.push_back( mymin( *(std::min_element(&msg->ranges[288],&msg->ranges[431])), 10.0) );
  regions.push_back( mymin( *(std::min_element(&msg->ranges[432],&msg->ranges[575])), 10.0) );
  regions.push_back( mymin( *(std::min_element(&msg->ranges[576],&msg->ranges[713])), 10.0) );

/*
  std::string s; 
  s += "lr "; 
  for( auto i : regions)
    s += std::to_string(i)+ " ";
  ROS_INFO_STREAM(s);
*/


  takeAction(regions);
}

int main(int argc, char ** argv) { 

  ros::init(argc, argv, "obstacle_avoidance");
  geometry_msgs::Twist msg; 
  // ros
  ros::NodeHandle n;

  pub1 = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10); 
  ros::Subscriber sub1 = n.subscribe("m2w/laser/scan", 1000, &laserCallBack);

  ros::spin();

  return 0;
} 

