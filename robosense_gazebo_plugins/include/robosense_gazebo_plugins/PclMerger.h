#ifndef PCLMERGER_H
#define PCLMERGER_H

#include <iostream>
#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/time_synchronizer.h>
#include <pcl_ros/point_cloud.h>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

class pclmerger {
public:
  pclmerger();

  void callback(const sensor_msgs::PointCloud2ConstPtr &onef,
                const sensor_msgs::PointCloud2ConstPtr &twof,
                const sensor_msgs::PointCloud2ConstPtr &threef,
                const sensor_msgs::PointCloud2ConstPtr &fourf,
                const sensor_msgs::PointCloud2ConstPtr &fivef);

private:
  ros::NodeHandle n;
  ros::Publisher pub;

  typedef message_filters::sync_policies::ApproximateTime<
      sensor_msgs::PointCloud2, sensor_msgs::PointCloud2,
      sensor_msgs::PointCloud2, sensor_msgs::PointCloud2,
      sensor_msgs::PointCloud2>
      TimePolicy;

  message_filters::Subscriber<sensor_msgs::PointCloud2> onesub;
  message_filters::Subscriber<sensor_msgs::PointCloud2> twosub;
  message_filters::Subscriber<sensor_msgs::PointCloud2> threesub;
  message_filters::Subscriber<sensor_msgs::PointCloud2> foursub;
  message_filters::Subscriber<sensor_msgs::PointCloud2> fivesub;
  message_filters::Synchronizer<TimePolicy> sync;

  sensor_msgs::PointCloud2 result;
};

#endif /*                                                                      \
          PCLMERGER_H  */
