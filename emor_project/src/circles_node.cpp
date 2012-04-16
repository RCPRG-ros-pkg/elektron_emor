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
			vel.linear.x = 0.2;
			vel.angular.z = 0.0;
    }
    else if(counter < 40){
			vel.linear.x = 0.2;
			vel.angular.z = 0.5;
    }
    else if(counter < 60){
			vel.linear.x = 0.2;
			vel.angular.z = 0.0;
    }
    else if(counter < 80){
			vel.linear.x = 0.2;
			vel.angular.z = -0.5;
    }
    else{
			vel.linear.x = 0.0;
			vel.angular.z = 0.0;
	    vel_pub.publish(vel);
			return 0;
    }
    counter++;
 */   

    vel_pub.publish(vel);

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}

