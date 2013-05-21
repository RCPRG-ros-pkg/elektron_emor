#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>


nav_msgs::Odometry realpos;
ros::Publisher pose_pub;
tf::TransformBroadcaster *real_odom_broadcaster;



void poseCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
	
	
	//first, we'll publish the transform over tf
	geometry_msgs::TransformStamped real_odom_trans;
	real_odom_trans.header.frame_id = "odom";
	real_odom_trans.child_frame_id = "base_link";
	
	real_odom_trans.header.stamp = ros::Time::now();
		
	geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(msg->pose.pose.orientation.z);

	real_odom_trans.transform.translation.x = - msg->pose.pose.position.y;
	real_odom_trans.transform.translation.y = msg->pose.pose.position.x;
	real_odom_trans.transform.translation.z = 0.0;
	real_odom_trans.transform.rotation = odom_quat;

	//send the transform
	real_odom_broadcaster->sendTransform(real_odom_trans);
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "realodom");
	ros::NodeHandle nh;
	real_odom_broadcaster = new tf::TransformBroadcaster();
	//ros::Publisher
	ros::Subscriber pose_sub = nh.subscribe("odom", 1, &poseCallback);
	ros::Rate loop_rate(10);

	

	while (ros::ok())
	{
		ros::spinOnce();
		loop_rate.sleep();
	}


return 0;
}

