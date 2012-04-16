#include <ros/ros.h>

#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>


geometry_msgs::Twist vel;

void laserCallback(const sensor_msgs::LaserScanConstPtr& msg)
{
  double min_range;
  int min_index;

  min_range = msg->range_max;
  min_index = 0;

  for(unsigned int i = 0; i<msg->ranges.size(); i++)
  {
    if((min_range > msg->ranges[i]) && (msg->ranges[i] > 0.0))
    {
      min_range = msg->ranges[i]; 
      min_index = i;
    }
  }

  printf("min distance: ranges[%d]=%lf\n", min_index, min_range);
  fflush(stdout);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "emor_wall");
  ros::NodeHandle nh;
  ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  ros::Subscriber laser_sub = nh.subscribe("base_scan", 1, &laserCallback);
  ros::Rate loop_rate(10);

  //vel.linear.x = 0.2;
  //vel.angular.z = -0.3;

  while(ros::ok())
  {
    if (ros::isShuttingDown()) {
      vel.linear.x = 0.0;
      vel.angular.z = 0.0;
    } 

    vel_pub.publish(vel);

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}

