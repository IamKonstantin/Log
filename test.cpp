// ------------- NOT main.cpp -----------------

#include "log.h"

void bar() {
    ERR << "foo bar";
}



// -------------   main.cpp   -----------------

#include <thread>
#include "log_object.h"

int main(int argc, char* argv[])
{
    LogObject l("test.log");

    std::thread foo(bar);

    ERR << "It's an error";
    OUT << "It's fine";

    foo.join();

    return 0;
}
