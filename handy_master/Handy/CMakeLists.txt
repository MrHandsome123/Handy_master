cmake_minimum_required(VERSION 3.10)
project(opencv)

set(CMAKE_CXX_STANDARD 14)
set(OpenCV_DIR D:\\opencv_old\\build\\lib)

find_package(OpenCV REQUIRED)

aux_source_directory(. SOURCE_FILES)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCE_FILES} main.cpp BackgroundRemover.cpp FaceDetector.cpp FingerCount.cpp SkinDetector.cpp)
# add_executable(${PROJECT_NAME} ${SOURCE_FILES} main.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})