#include <ros/ros.h>
#include <nav_msgs/Odometry.h>


nav_msgs::Odometry realpos;
ros::Publisher pose_pub;


void poseCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
	double temp;
//	temp = msg->pose.pose.position.x;
	realpos.pose.pose.position.x = - msg->pose.pose.position.y;
	realpos.pose.pose.position.y = msg->pose.pose.position.x;
	pose_pub.publish(realpos);
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "realpos");
  ros::NodeHandle nh;
  //ros::Publisher
  pose_pub = nh.advertise<nav_msgs::Odometry>("real_position", 1);
  ros::Subscriber pose_sub = nh.subscribe("base_pose_ground_truth", 1, &poseCallback);
  ros::Rate loop_rate(10);
  
  while (ros::ok())
  {
    ros::spinOnce();
    

    loop_rate.sleep();
  }


  return 0;
}

