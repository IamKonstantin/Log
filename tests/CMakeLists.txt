cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)


# The additional / is important to remove the last character from the path.
# Note that it does not matter if the OS uses / or \, because we are only
# saving the path size.
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DLOG_SOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")

project(test_log)

# test_static_lib
add_library(test_static_lib STATIC
  "static/lib.h"
  "static/lib.cpp"
)
target_include_directories(test_static_lib PRIVATE "..")

add_executable(test_static_lib_binary
  "static/main.cpp"
  "../log.h"
  "../log_object.h"
  "../log.cpp"
)
target_include_directories(test_static_lib_binary PRIVATE "..")
target_link_libraries(test_static_lib_binary test_static_lib)
if (UNIX)
  target_link_libraries(test_static_lib_binary "pthread")
endif(UNIX)


add_library(test_shared_lib SHARED 
  "shared/lib.h"
  "shared/lib.cpp"
  "shared/lib-init.cpp"
  "../log.h"
  "../log_object.h"
  "../log.cpp"
)
target_compile_definitions(test_shared_lib PRIVATE TEST_LIB_DECLARE_EXPORT)
target_include_directories(test_shared_lib PRIVATE "..")

add_executable(test_shared_lib_binary
  "shared/main.cpp"
  "../log.h"
  "../log_object.h"
  "../log.cpp"
)
#target_compile_definitions(test_shared_lib_binary PRIVATE TEST_LIB_DECLARE_IMPORT)
target_include_directories(test_shared_lib_binary PRIVATE "..")
target_link_libraries(test_shared_lib_binary test_shared_lib)
if (UNIX)
  target_link_libraries(test_shared_lib_binary "pthread")
endif(UNIX)

