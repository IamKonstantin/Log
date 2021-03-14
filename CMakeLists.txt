cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)


# The additional / is important to remove the last character from the path.
# Note that it does not matter if the OS uses / or \, because we are only
# saving the path size.
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")

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
