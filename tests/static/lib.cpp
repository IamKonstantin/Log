#include "lib.h"

#include "log.h"


void test_lib_function() {
  ERR << "test lib function error";
  for (int i = 0; i < 10000; ++ i) {
    ERR << "The pen is mightier than the sword. " << i;
  }
}
