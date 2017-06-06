cmake_minimum_required(VERSION 2.8.3)
project(ironhide_agilus_cell_support)

find_package(catkin REQUIRED)

catkin_package()

install(DIRECTORY urdf launch config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
