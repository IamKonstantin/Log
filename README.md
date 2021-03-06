# Log
Message logging in a multithreaded c++ program
```text
2021-03-14 19:39:39.400 (21758) ERR No route to host 127.0.0.1 in src/network/socket.cpp:45
```

# Usage
1. Include `log_object.h` in `main.cpp` and initialize LogObject class in main().
```c++
#include "log_object.h"

int main(int argc, char* argv[])
{
    LogObject log("filepath.log");
    ...
    return 0;
}
```
2. Link the `log.cpp` object file to the executable as `main.cpp` does. For example in cmake:
```cmake
add_executable(${PROJECT_NAME}
  "log.h"
  "log_object.h"
  "log.cpp"
  ...
  "main.cpp")
```
3. Include `log.h` and use `ERR` and `OUT` macros in code
```c++
#include "log.h"

void some_function() {
    ERR << "Error text";
    OUT << "Info message";
}
```
4. Optinonally, it you want to see relative filepath, not absolute filepath, define global SOURCE_PATH_SIZE. For example in cmake:
```cmake
# The additional / is important to remove the last character from the path.
# Note that it does not matter if the OS uses / or \, because we are only
# saving the path size.
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")
```
