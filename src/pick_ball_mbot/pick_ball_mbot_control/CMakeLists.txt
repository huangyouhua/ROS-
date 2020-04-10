cmake_minimum_required(VERSION 2.8.3)
project(pick_ball_mbot_control)

find_package(catkin REQUIRED
  roscpp
  rospy
  sensor_msgs
  std_msgs
  geometry_msgs
  pick_ball_mbot_msgs
  actionlib_msgs
  actionlib
)

catkin_package()

include_directories(
  include 
  ${catkin_INCLUDE_DIRS}
)

link_directories(
  ${catkin_LIB_DIRS} 
)

install(DIRECTORY config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

add_executable(motion_planning
  src/motion_planning.cpp
)
add_dependencies(motion_planning ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(motion_planning 
  ${catkin_LIBRARIES}
)

add_executable(paddle_control
  src/paddle_control.cpp
)
add_dependencies(paddle_control ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(paddle_control 
  ${catkin_LIBRARIES}
)