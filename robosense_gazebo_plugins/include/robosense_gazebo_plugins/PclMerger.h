#ifndef PCLMERGER_H
#define PCLMERGER_H

#include <iostream>
#include <ros/ros.h>

class pclmerger {
public:
  pclmerger();

  void start();

private:
  ros::NodeHandle n;
};

#endif /*                                                                      \
          PCLMERGER_H  */
