cmake_minimum_required(VERSION 2.8.3)
project(mimage2bag)


find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
)

find_package(OpenCV)
include_directories(include ${OpenCV_INCLUDE_DIRS})

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES mimage2bag
#  CATKIN_DEPENDS cv_bridge image_transport
#  DEPENDS system_lib
)

include_directories(include ${OpenCV_INCLUDE_DIRS})
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(my_publisher src/img2bag_publisher.cpp)
target_link_libraries(my_publisher ${catkin_LIBRARIES})
