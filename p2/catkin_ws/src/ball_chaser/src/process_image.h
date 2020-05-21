#ifndef PROCESS_IMAGE_H 
#define PROCESS_IMAGE_H

#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>


class process_image{ 

public: 
process_image(ros::NodeHandle n){

 // Define a client service capable of requesting services from command_robot
client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
}


enum Move{ 

NOBALL, 
LEFT, 
MIDDLE, 
RIGHT

};

Move dirc; 
ros::ServiceClient client; 
void drive_robot(float lin_x, float ang_z);
void process_image_callback(const sensor_msgs::Image img);

};


#endif 
