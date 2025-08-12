cmake_minimum_required(VERSION 3.5)
project(keyboard_teleop_v3)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(keyboard_teleop_node src/keyboard_teleop.cpp)

ament_target_dependencies(keyboard_teleop_node rclcpp std_msgs)

install(TARGETS
  keyboard_teleop_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()

