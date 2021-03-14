cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)

project(Log)
add_executable(${PROJECT_NAME} "test.cpp" "log.cpp")
target_link_libraries(${PROJECT_NAME} "pthread")
