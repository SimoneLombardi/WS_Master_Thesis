#include <rclcpp/rclcpp.hpp>
#include "EnvCloudManager.hpp"

using namespace UseCase1;

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);

  // Create and spin the node
  auto node = std::make_shared<EnvCloudManager>();
  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}
