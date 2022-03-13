#include <thread>

#include "log_object.h"
#include "log.h"
#include "lib.h"


int main(int argc, char* argv[])
{
  LogObject l("test_static.log");

  std::thread foo(test_lib_function);

  ERR << "It's an error";
  OUT << "It's fine";

  for (int i = 0; i < 10000; ++ i) {
    ERR << "Two wrongs don't make a right. " << i;
  }
  
  foo.join();

  return 0;
}
