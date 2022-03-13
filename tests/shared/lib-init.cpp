#include "lib.h"

#include "log_object.h"


void test_lib_function(LogObject* log_object) {
    log_set_log_object(log_object);
    log_smth();
    log_reset_log_object();
}

