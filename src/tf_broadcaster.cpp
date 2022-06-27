#include "ros/ros.h"

#include "nav_msgs/Odometry.h"
#include "geometry_msgs/TransformStamped.h"

#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>

class tf_broadcaster  //header of the class
{
  private:
    ros::NodeHandle Handle;

    /* ROS topics */
    ros::Subscriber input_subscriber;
    

    /* TF Broadcaster */
    tf2_ros::TransformBroadcaster odom_broadcaster;
   

    /* ROS topic callbacks */
    void input_MessageCallback(const nav_msgs::Odometry::ConstPtr& odom)
{
   
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = odom->header.stamp;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_footprint";

    odom_trans.transform.translation.x = odom->pose.pose.position.x;
    odom_trans.transform.translation.y = odom->pose.pose.position.y;
    odom_trans.transform.translation.z = odom->pose.pose.position.z;
    odom_trans.transform.rotation.x = odom->pose.pose.orientation.x;
    odom_trans.transform.rotation.y = odom->pose.pose.orientation.y;
    odom_trans.transform.rotation.z = odom->pose.pose.orientation.z;
    odom_trans.transform.rotation.w = odom->pose.pose.orientation.w;
    
    //send the transform
    odom_broadcaster.sendTransform(odom_trans);
    
}
       
  
    

  public:
    tf_broadcaster(){
        /* ROS topics */
        this->input_subscriber = this->Handle.subscribe("/odom", 10, &tf_broadcaster::input_MessageCallback, this);
        
        ROS_INFO("Node %s ready to run.", ros::this_node::getName().c_str());
    };
    
    void RunPeriodically(void){
        ROS_INFO("Node %s running.", ros::this_node::getName().c_str());

        // Wait other nodes start
        sleep(1.0);
        
        ros::spin();
    };

};




int main(int argc, char **argv){
    ros::init(argc, argv, "tf_broadcaster");
    
    tf_broadcaster my_tf_broadcaster;
    
    my_tf_broadcaster.RunPeriodically();
    
    ROS_INFO("node tf_broadcaster is shutting down");

  return 0;

}
