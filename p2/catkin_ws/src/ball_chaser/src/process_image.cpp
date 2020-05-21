
//#include <sensor_msgs/Image.h>
//#include "ros/ros.h"
//#include "ball_chaser/DriveToTarget.h"
#include "process_image.h"

#define ROBOERR
// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void process_image::drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
	ball_chaser::DriveToTarget srv;
#ifdef ROBOERR 
	//when I appply the force to linear, the robot drives turns instead of going straight doing this for now until i figure out why.
	srv.request.linear_x = ang_z; 
	srv.request.angular_z = lin_x; 
#else 
	srv.request.linear_x = lin_x; 
	srv.request.angular_z = ang_z; 
#endif 

	if (!client.call(srv))
		ROS_ERROR("Failed to call service safe_move");
}

// This callback function continuously executes and reads the image data
void process_image::process_image_callback(const sensor_msgs::Image img)
{

	 this->dirc = NOBALL; 
	bool imgFnd = false; 
    int white_pixel = 255;
    int i;
    
    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    
    for (i = 0; i < img.height * img.step; i++) {
		if (img.data[i] == white_pixel) {
		    imgFnd = true;
		    break;
		}
    }
    
    int L, R; 
    L = (float)img.step *(1.0/3.0); 
    R = (float)img.step *(2.0/3.0); 
    
    if(i < L) 
    	this->dirc = LEFT; 
    else if (i > R) 
    	this->dirc = RIGHT; 
    else 
    	this->dirc = MIDDLE;
    
	switch(this->dirc){

	case LEFT: 
		drive_robot(-0.5,0.5); 
	break; 
	case MIDDLE:
		drive_robot(0,0.5); 
	break;  
	case RIGHT:
		drive_robot(0.5,0.5); 
	break ; 
	default: 
		drive_robot(0,0); 
	}
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;
	process_image pi(n); 
  
    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, &process_image::process_image_callback, &pi);

    // Handle ROS communication events
    ros::spin();

    return 0;
}

