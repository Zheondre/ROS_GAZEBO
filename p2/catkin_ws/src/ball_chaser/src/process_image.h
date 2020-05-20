#ifndef PROCESS_IMAGE_H 
#define PROCESS_IMAGE_H

#include "ros/rosh"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>


class process_image(){ 

public: 
process_image(ros::NodeHandle n){
client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
}


ros::ServiceClient client; 

void drive_robot(float lin_x, float ang_z);
void process_image_callback(const sensor_msgs::Image img);

};


#endif 
