#ifndef DRIVE_TARGET_H
#define DRIVE_TARGET_H


#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"



class DriveTarget { 

public:	
	DriveTarget(ros::NodeHandle n){
    	// Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    		motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
	} 

	// ROS::Publisher motor commands;
	ros::Publisher motor_command_publisher;

	bool handle_drive_request_cb(ball_chaser::DriveToTarget::Request& req, 
	ball_chaser::DriveToTarget::Response& res);
} ;

#endif
