#include "robosense_gazebo_plugins/PclMerger.h"

pclmerger::pclmerger()
    : pub(n.advertise<sensor_msgs::PointCloud2>("final", 100)),
      foursub(n, "/four", 1), fivesub(n, "/five", 1),
      sync(foursub, fivesub, 10) {
  sync.registerCallback(&pclmerger::callback, this);

  std::cout << "pclmerger object has been created!" << std::endl;
}

void pclmerger::callback(const sensor_msgs::PointCloud2ConstPtr &fourf,
                         const sensor_msgs::PointCloud2ConstPtr &fivef) {

  pcl::concatenatePointCloud(*fourf, *fivef, result);
  std::cout << "ran\n";
  result.fields[3].name = "intensity";
  result.header.frame_id = "five";
  pub.publish(result);
}
// void pclmerger::start() {
//
//   boost::shared_ptr<sensor_msgs::PointCloud2 const> first;
//   boost::shared_ptr<sensor_msgs::PointCloud2 const> second;
//   while (ros::ok()) {
//     first = ros::topic::waitForMessage<sensor_msgs::PointCloud2>("/five");
//     if (first == NULL)
//       ROS_INFO("No laser messages received");
//     second = ros::topic::waitForMessage<sensor_msgs::PointCloud2>("/four");
//     if (second == NULL)
//       ROS_INFO("No laser messages received");
//
// pcl::concatenatePointCloud(*first, *second, result);
// std::cout << "ran\n";
// result.fields[3].name = "intensity";
// result.header.frame_id = "five";
// pub.publish(result);
//   }
// }

int main(int argc, char **argv) {
  ros::init(argc, argv, "pclmerger");

  pclmerger obj;
  // obj.sync.registerCallback(boost::bind(&obj.callback, _1, _2));
  // obj.start();

  ros::spin();
  return 0;
}
