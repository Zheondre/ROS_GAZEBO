#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "DriveTarget.h"
#include "ball_chaser/DriveToTarget.h"

// TODO: Create a handle_drive_request callback function that executes whenever a drive_bot service is requested
// This function should publish the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities

bool DriveTarget::handle_drive_request_cb(ball_chaser::DriveToTarget::Request& req, 
	ball_chaser::DriveToTarget::Response& res){

 
   ROS_INFO("DriveTarget received - j1:%1.2f, a1:%1.2f", (float)req.linear_x, (float)req.angular_z);


        geometry_msgs::Twist motor_command;
        // Set wheel velocities, forward [0.5, 0.0]
        motor_command.linear.x =  req.linear_x;
        motor_command.angular.z = req.angular_z;

	motor_command_publisher.publish(motor_command);


  res.msg_feedback = "Joint vel set - j1: " + std::to_string(req.linear_x) + "angle, a1; " + std::to_string(req.angular_z);
    ROS_INFO_STREAM(res.msg_feedback);

ros::Duration(1).sleep();

return true; 
}

int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;
	DriveTarget tar(n);

    // TODO: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function
    ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot", &tar.handle_drive_request_cb);
    ROS_INFO("Ready to send joint commands");


    // TODO: Handle ROS communication events
    ros::spin();

    return 0;
}
