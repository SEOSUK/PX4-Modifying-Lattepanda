cmake_minimum_required(VERSION 3.8)
project(quadrotor_controller)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(dynamixel_sdk REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(dynamixel_fix src/dynamixel_fix.cpp)
target_include_directories(dynamixel_fix PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(dynamixel_fix PUBLIC c_std_99 cxx_std_17)  
ament_target_dependencies(dynamixel_fix rclcpp std_msgs dynamixel_sdk)

install(TARGETS dynamixel_fix
  DESTINATION lib/${PROJECT_NAME})


# ---------------- dynamixel_reboot ----------------
add_executable(dynamixel_reboot src/dynamixel_reboot.cpp)
target_include_directories(dynamixel_reboot PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(dynamixel_reboot PUBLIC c_std_99 cxx_std_17)
ament_target_dependencies(dynamixel_reboot rclcpp dynamixel_sdk)

install(TARGETS dynamixel_reboot
  DESTINATION lib/${PROJECT_NAME})  

  
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
