#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_datatypes.h>
 
// Send a simple navigation goal
 
geometry_msgs::PoseStamped constructPoseStampedMsg(float xPos, float yPos, float angle)
{
        geometry_msgs::PoseStamped poseMsg;
        poseMsg.header.frame_id = "/map";
        poseMsg.header.stamp = ros::Time::now();
        poseMsg.pose.position.x = xPos;
        poseMsg.pose.position.y = yPos;
        poseMsg.pose.position.z = 0;
        tf::Quaternion quat = tf::createQuaternionFromYaw(angle);
        tf::quaternionTFToMsg(quat, poseMsg.pose.orientation);
        return poseMsg;
}
 
void publishNavGoal(ros::Publisher pub, geometry_msgs::PoseStamped poseMsg)
{
        ros::Rate loop_rate(1);
        for(int ctr=0;ctr<2;ctr++)
        {      
                pub.publish(poseMsg);
                ros::spinOnce();               
                loop_rate.sleep();     
        }
        return;
}
 
int main(int argc, char **argv)
{
        ros::init(argc, argv, "guard");
        ros::NodeHandle node;
        ros::Publisher pub = node.advertise<geometry_msgs::PoseStamped> ("/move_base_simple/goal",30);
        geometry_msgs::PoseStamped destination = constructPoseStampedMsg(12,8,0);
        publishNavGoal(pub, destination);
        return 1;
}

