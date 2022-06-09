#include "robosense_gazebo_plugins/PclMerger.h"

pclmerger::pclmerger()
    : pub(n.advertise<sensor_msgs::PointCloud2>("rslidar_points", 100)),
      onesub(n, "/one", 1), twosub(n, "/two", 1), threesub(n, "/three", 1),
      foursub(n, "/four", 1), fivesub(n, "/five", 1),
      sync(TimePolicy(10), onesub, twosub, threesub, foursub, fivesub) {

  sync.registerCallback(&pclmerger::callback, this);
  std::cout << "pclmerger object has been created!" << std::endl;
}

void pclmerger::callback(const sensor_msgs::PointCloud2ConstPtr &onef,
                         const sensor_msgs::PointCloud2ConstPtr &twof,
                         const sensor_msgs::PointCloud2ConstPtr &threef,
                         const sensor_msgs::PointCloud2ConstPtr &fourf,
                         const sensor_msgs::PointCloud2ConstPtr &fivef) {

  pcl::concatenatePointCloud(*fourf, *fivef, result);
  pcl::concatenatePointCloud(result, *threef, result);
  pcl::concatenatePointCloud(result, *twof, result);
  pcl::concatenatePointCloud(result, *onef, result);
  result.fields[3].name = "intensity";
  result.header.frame_id = "rslidar";
  pub.publish(result);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "pclmerger");

  pclmerger obj;

  ros::spin();
  return 0;
}
