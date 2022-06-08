#include "robosense_gazebo_plugins/PclMerger.h"

pclmerger::pclmerger()
    : pub(n.advertise<sensor_msgs::PointCloud2>("final", 100))

{
  std::cout << "pclmerger object has been created!" << std::endl;
}

void pclmerger::start() {

  boost::shared_ptr<sensor_msgs::PointCloud2 const> SharedPtr;
  while (ros::ok()) {
    SharedPtr = ros::topic::waitForMessage<sensor_msgs::PointCloud2>(
        "/five", ros::Duration(1));
    if (SharedPtr == NULL)
      ROS_INFO("No laser messages received");
    else
      five = *SharedPtr;
    SharedPtr = ros::topic::waitForMessage<sensor_msgs::PointCloud2>(
        "/four", ros::Duration(1));
    if (SharedPtr == NULL)
      ROS_INFO("No laser messages received");
    else
      four = *SharedPtr;

    pcl::concatenatePointCloud(five, four, result);
    result.fields[3].name = "intensity";
    result.header.frame_id = "five";
    pub.publish(result);
  }
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "pclmerger");

  pclmerger obj;
  obj.start();

  ros::spin();
  return 0;
}
