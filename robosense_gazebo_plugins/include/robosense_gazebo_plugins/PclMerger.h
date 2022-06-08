#ifndef PCLMERGER_H
#define PCLMERGER_H

#include <iostream>
#include <pcl_ros/point_cloud.h>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

class pclmerger {
public:
  pclmerger();

  void start();

private:
  ros::NodeHandle n;
  ros::Publisher pub;

  sensor_msgs::PointCloud2 result;
  sensor_msgs::PointCloud2 five;
  sensor_msgs::PointCloud2 four;
};

#endif /*                                                                      \
          PCLMERGER_H  */
