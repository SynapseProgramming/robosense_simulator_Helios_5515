#ifndef PCLMERGER_H
#define PCLMERGER_H

#include <iostream>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <pcl_ros/point_cloud.h>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

class pclmerger {
public:
  pclmerger();

  void callback(const sensor_msgs::PointCloud2ConstPtr &threef,
                const sensor_msgs::PointCloud2ConstPtr &fourf,
                const sensor_msgs::PointCloud2ConstPtr &fivef);

private:
  ros::NodeHandle n;
  ros::Publisher pub;

  message_filters::Subscriber<sensor_msgs::PointCloud2> threesub;
  message_filters::Subscriber<sensor_msgs::PointCloud2> foursub;
  message_filters::Subscriber<sensor_msgs::PointCloud2> fivesub;
  message_filters::TimeSynchronizer<sensor_msgs::PointCloud2,
                                    sensor_msgs::PointCloud2,
                                    sensor_msgs::PointCloud2>
      sync;

  sensor_msgs::PointCloud2 result;
};

#endif /*                                                                      \
          PCLMERGER_H  */
