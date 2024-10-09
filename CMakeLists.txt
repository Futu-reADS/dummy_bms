cmake_minimum_required(VERSION 3.8)
project(dummy_bms)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
#find_package(geometry_msgs REQUIRED)
#find_package(tier4_planning_msgs REQUIRED)
#find_package(tier4_external_api_msgs REQUIRED)
#find_package(autoware_adapi_v1_msgs REQUIRED)
#find_package(tier4_control_msgs REQUIRED)
#find_package(autoware_auto_vehicle_msgs REQUIRED)
#find_package(tier4_system_msgs REQUIRED)
#find_package(autoware_auto_perception_msgs REQUIRED)
#find_package(tier4_autoware_utils REQUIRED)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

# if(BUILD_TESTING)
#   find_package(ament_lint_auto REQUIRED)
#   # the following line skips the linter which checks for copyrights
#   # comment the line when a copyright and license is added to all source files
#   set(ament_cmake_copyright_FOUND TRUE)
#   # the following line skips cpplint (only works in a git repo)
#   # comment the line when this package is in a git repo and when
#   # a copyright and license is added to all source files
#   set(ament_cmake_cpplint_FOUND TRUE)
#   ament_lint_auto_find_test_dependencies()
# endif()

add_executable(dummy_bms src/main.cpp src/dummy_bms.cpp)
ament_target_dependencies(
  dummy_bms 
  rclcpp 
  std_msgs 
#  geometry_msgs 
#  tier4_planning_msgs 
#  autoware_adapi_v1_msgs 
#  autoware_auto_vehicle_msgs 
#  tier4_external_api_msgs
#  tier4_control_msgs
#  tier4_system_msgs
#  autoware_auto_perception_msgs
#  tier4_autoware_utils
  )
install(TARGETS
  dummy_bms
  DESTINATION lib/${PROJECT_NAME})
# Install launch files.

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)
ament_package()
