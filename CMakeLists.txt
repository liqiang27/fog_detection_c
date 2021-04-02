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

add_executable(test_object      main.cpp  
                                                                ${PROJECT_PATH}/src/get_darkchanel.cc 
                                                                ${PROJECT_PATH}/src/get_slice.cc 
                                                                )

target_link_libraries(test_object  -lboost_filesystem -lboost_system ${OpenCV_LIBS} ${Boost_LIBRARIES})


add_executable(slicer    ${PROJECT_PATH}/script/createSplitimage.cc 
                                                                ${PROJECT_PATH}/src/get_darkchanel.cc 
                                                                ${PROJECT_PATH}/src/get_slice.cc )

target_link_libraries(slicer -lboost_filesystem -lboost_system ${OpenCV_LIBS} ${Boost_LIBRARIES})


add_executable(dark    ${PROJECT_PATH}/script/createDarkchanel.cc 
                                                                ${PROJECT_PATH}/src/get_darkchanel.cc 
                                                                ${PROJECT_PATH}/src/get_slice.cc )

target_link_libraries(dark -lboost_filesystem -lboost_system ${OpenCV_LIBS} ${Boost_LIBRARIES})
