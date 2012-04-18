#include <ros/ros.h>

#include <geometry_msgs/Twist.h>


geometry_msgs::Twist vel;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "emor_wall");
  ros::NodeHandle nh;
  ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  ros::Rate loop_rate(10);

  vel.linear.x = 0.2;
  vel.angular.z = -0.3;

  while(ros::ok())
  {
    if (ros::isShuttingDown()) {
      vel.linear.x = 0.0;
      vel.angular.z = 0.0;
    }
    
 /*   if(counter < 20){
			vel.linear.x = ...
			vel.angular.z = ...
    }
    else if(counter < 40){
			...
    }
    else ...
    
    counter++;
 */   

    vel_pub.publish(vel);

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}

