#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf/transform_datatypes.h>



int main(int argc, char** argv){
	ros::init(argc,argv,"robot_position_node");
	ros::NodeHandle nh;
	
	ros::Publisher pub = nh.advertise<geometry_msgs::TransformStamped>("robot_position",10);
	
	tf::TransformListener listener;
	
	ros::Rate rate(10.0);
	while (nh.ok()){
		tf::StampedTransform transform;
		try{
			listener.lookupTransform("/base_link","/map",ros::Time(0),transform);
		}
		catch(tf::TransformException &ex){
			ROS_ERROR("%s",ex.what());
			ros::Duration(1.0).sleep();
			continue;
		}
		geometry_msgs::TransformStamped pos;
		tf::transformStampedTFToMsg(transform,pos);	
		pub.publish(pos);
		rate.sleep();
	
	}
	
	return 0;
}
