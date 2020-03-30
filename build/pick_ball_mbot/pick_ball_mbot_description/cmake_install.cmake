# Install script for directory: /home/hyh/mc_ws/src/pick_ball_mbot/pick_ball_mbot_description

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/hyh/mc_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/hyh/mc_ws/build/pick_ball_mbot/pick_ball_mbot_description/catkin_generated/installspace/pick_ball_mbot_desciption.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pick_ball_mbot_desciption/cmake" TYPE FILE FILES
    "/home/hyh/mc_ws/build/pick_ball_mbot/pick_ball_mbot_description/catkin_generated/installspace/pick_ball_mbot_desciptionConfig.cmake"
    "/home/hyh/mc_ws/build/pick_ball_mbot/pick_ball_mbot_description/catkin_generated/installspace/pick_ball_mbot_desciptionConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pick_ball_mbot_desciption" TYPE FILE FILES "/home/hyh/mc_ws/src/pick_ball_mbot/pick_ball_mbot_description/package.xml")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pick_ball_mbot_desciption/config" TYPE DIRECTORY FILES "/home/hyh/mc_ws/src/pick_ball_mbot/pick_ball_mbot_description/config/")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pick_ball_mbot_desciption/launch" TYPE DIRECTORY FILES "/home/hyh/mc_ws/src/pick_ball_mbot/pick_ball_mbot_description/launch/")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pick_ball_mbot_desciption/meshes" TYPE DIRECTORY FILES "/home/hyh/mc_ws/src/pick_ball_mbot/pick_ball_mbot_description/meshes/")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pick_ball_mbot_desciption/urdf" TYPE DIRECTORY FILES "/home/hyh/mc_ws/src/pick_ball_mbot/pick_ball_mbot_description/urdf/")
endif()

