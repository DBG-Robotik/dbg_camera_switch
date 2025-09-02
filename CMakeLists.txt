cmake_minimum_required(VERSION 3.8)
project(dbg_camera_switch)

# Compiler-Warnungen aktivieren (optional, aber empfohlen)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ROS 2-Pakete finden
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

# Ausführbare Datei erstellen
add_executable(camera_switch_node src/camera_switch_node.cpp)
ament_target_dependencies(camera_switch_node rclcpp sensor_msgs std_msgs)

install(
  DIRECTORY
    launch
  DESTINATION share/${PROJECT_NAME}
)

install(TARGETS
  camera_switch_node
  DESTINATION lib/${PROJECT_NAME}
)

# Paket-Konfiguration
ament_package()