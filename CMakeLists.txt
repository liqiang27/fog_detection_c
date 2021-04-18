# set the minimum required version of cmake for a project
cmake_minimum_required(VERSION 3.1)

# set the project name and version
project(test)


# specify the C++ standard , build type and optimize  choice
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(TOP_DIR ${CMAKE_CURRENT_LIST_DIR}/../)
​
add_subdirectory(${TOP_DIR}/hello)
#set variation
SET(PROJECT_PATH ${PROJECT_SOURCE_DIR})
SET(BUILD_PATH ${PROJECT_BINARY_DIR})
SET(CMAKE_PREFIX_PATH "~/libtorch//share/cmake/Torch")

#include path
include_directories ("${PROJECT_PATH}/include")
include_directories("~/libtorch/include")
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(("${PROJECT_PATH}/jsoncpp/json"))


find_package(OpenCV REQUIRED)
find_package(Torch REQUIRED)
find_package(Boost REQUIRED)


message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

aux_source_directory(${PROJECT_PATH} DIR_MAIN_SRC)
aux_source_directory(${PROJECT_PATH}/common DIR_COMMON_SRC)
aux_source_directory(${PROJECT_PATH}/imgCapture DIR_CAPTURE_SRC)
aux_source_directory(${PROJECT_PATH}/imgPreprocess DIR_PREPROCESS_SRC)
aux_source_directory(${PROJECT_PATH}/readConfig DIR_CONFIG_SRC)
aux_source_directory(${PROJECT_PATH}/taskQueue DIR_QUEUE_SRC)
aux_source_directory(${PROJECT_PATH}/testModule DIR_TEST_SRC)
aux_source_directory(${PROJECT_PATH}/VENet DIR_VENET_SRC)
aux_source_directory(${PROJECT_PATH}/writeDatabase DIR_DATABASE_SRC)
aux_source_directory(${PROJECT_PATH}/jsoncpp DIR_JSON_SRC)



add_library(venet SHARED ${DIR_MAIN_SRC}
                                                        ${DIR_COMMON_SRC}
                                                        ${DIR_CAPTURE_SRC}
                                                        ${DIR_PREPROCESS_SRC}
                                                        ${DIR_CONFIG_SRC}
                                                        ${DIR_QUEUE_SRC}
                                                        ${DIR_TEST_SRC}
                                                        ${DIR_VENET_SRC}
                                                        ${DIR_DATABASE_SRC}
                                                        ${DIR_JSON_SRC})

add_executable(main_process ${DIR_MAIN_SRC}
                                                                 ${DIR_COMMON_SRC}
                                                                 ${DIR_CAPTURE_SRC}
                                                                 ${DIR_PREPROCESS_SRC}
                                                                 ${DIR_CONFIG_SRC}
                                                                 ${DIR_QUEUE_SRC}
                                                                 ${DIR_TEST_SRC}
                                                                 ${DIR_VENET_SRC}
                                                                 ${DIR_DATABASE_SRC}
                                                                 ${DIR_JSON_SRC})

target_link_libraries(main_process pthread pqxx ${OpenCV_LIBS} ${CUDA_LIB2} ${CUDA_LIB} ${Boost_LIBRARIES} ${TORCH_LIBRARIES})


