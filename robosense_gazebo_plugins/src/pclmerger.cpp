#include "robosense_gazebo_plugins/PclMerger.h"

pclmerger::pclmerger()
    : pub(n.advertise<sensor_msgs::PointCloud2>("final", 100)),
      threesub(n, "/three", 1), foursub(n, "/four", 1), fivesub(n, "/five", 1),
      sync(MySyncPolicy(10), threesub, foursub, fivesub) {
  sync.registerCallback(&pclmerger::callback, this);

  std::cout << "pclmerger object has been created!" << std::endl;
}

void pclmerger::callback(const sensor_msgs::PointCloud2ConstPtr &threef,
                         const sensor_msgs::PointCloud2ConstPtr &fourf,
                         const sensor_msgs::PointCloud2ConstPtr &fivef) {

  pcl::concatenatePointCloud(*fourf, *fivef, result);
  pcl::concatenatePointCloud(result, *threef, result);
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
