#include <thread>

#include "log_object.h"
#include "log.h"
#include "test_lib.h"


int main(int argc, char* argv[])
{
  LogObject l("test.log");

  std::thread foo(test_lib_function);

  ERR << "It's an error";
  OUT << "It's fine";

  foo.join();

  return 0;
}
