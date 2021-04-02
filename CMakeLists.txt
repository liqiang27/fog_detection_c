cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# set(CMAKE_PREFIX_PATH "/home/liqiang/Documents/FOG_DETECTION/fog_detection_c/libtorch/share/cmake")

project(test)

SET(PROJECT_PATH ${PROJECT_SOURCE_DIR})
SET(BUILD_PATH ${PROJECT_BINARY_DIR})

include_directories ("${PROJECT_PATH}/include")
# include_directories("${PROJECT_PATH}/libtorch/include")
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})


find_package(OpenCV REQUIRED)
# find_package(Torch REQUIRED)
find_package(Boost REQUIRED)


message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

