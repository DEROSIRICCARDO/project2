#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "sensor_msgs/LaserScan.h"
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>


class LaserMerger {
private:
    ros::NodeHandle n;
    
    message_filters::Subscriber<sensor_msgs::LaserScan> sub_front_scan;
    message_filters::Subscriber<sensor_msgs::LaserScan> sub_rear_scan;
    
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::LaserScan, sensor_msgs::LaserScan> MySyncPolicy;
    
    typedef message_filters::Synchronizer<MySyncPolicy> Sync;
    boost::shared_ptr<Sync> sync;
        
    ros::Publisher  output_publisher;
    

    
    void Callback(const sensor_msgs::LaserScan::ConstPtr& front_scan, const sensor_msgs::LaserScan rear_scan) {
        

        ROS_INFO("I heard true position ");

    };
    
    void compute(){
        
        
        
        
    };
    
    
    
public:
    
    LaserMerger(){ // class constructor
      // all initializations here
        sub_front_scan.subscribe(n, "/front/scan", 1000);
        sub_rear_scan.subscribe(n, "/rear/scans",1000);
        
        sync.reset(new Sync(MySyncPolicy(10), sub_front_scan, sub_rear_scan));
        sync->registerCallback(&LaserMerger::Callback, this);
                
        this->output_publisher = this->n.advertise<sensor_msgs::LaserScan>("/CompleteScan", 1);

        

        ROS_INFO("Node %s ready to run.", ros::this_node::getName().c_str());
    };
    
    void main_loop(){
        sleep(1.0);
        ros::Rate rate(10);
        
        ROS_INFO("Node %s running.", ros::this_node::getName().c_str());
        
        while(ros::ok()){
            
            ros::spinOnce();
            rate.sleep();
            
        };
        
    };
    
};
    



int main(int argc, char **argv){
    ros::init(argc, argv, "LaserMerger");
    
    LaserMerger my_laser_merger;
    
    my_laser_merger.main_loop();
    
    ROS_INFO("node LaserMerger is shutting down");

  return 0;

}
    

