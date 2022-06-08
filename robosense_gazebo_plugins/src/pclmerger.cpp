#include "robosense_gazebo_plugins/PclMerger.h"

pclmerger::pclmerger() {
  std::cout << "pclmerger object has been created!" << std::endl;
}

void pclmerger::start() { std::cout << "merger has started!\n"; }

int main(int argc, char **argv) {
  ros::init(argc, argv, "pclmerger");

  pclmerger obj;
  obj.start();

  ros::spin();
  return 0;
}
