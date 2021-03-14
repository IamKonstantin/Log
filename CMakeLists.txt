cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)

project(test-log)
add_library(test-lib
  "test_lib.h"
  "test_lib.cpp")
add_executable(${PROJECT_NAME}
  "test_main.cpp"
  "log.h"
  "log_object.h"
  "log.cpp")
target_link_libraries(${PROJECT_NAME} "pthread" test-lib)
