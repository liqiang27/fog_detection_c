cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

project(test)

SET(PROJECT_PATH ${PROJECT_SOURCE_DIR})
SET(BUILD_PATH ${PROJECT_BINARY_DIR})

INCLUDE_DIRECTORIES (
        "${PROJECT_PATH}/include"
)

find_package(OpenCV REQUIRED)
find_package(Torch REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

add_executable(test_object      main.cpp 
                                                                ${PROJECT_PATH}/src/get_darkchanel.cc 
                                                                ${PROJECT_PATH}/src/get_slice.cc 
                                                                ${PROJECT_PATH}/src/get_tensor.cc)

target_link_libraries(test_object ${OpenCV_LIBS} ${TORCH_LIBRARIES})
