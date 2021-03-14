<<<<<<< HEAD
Log
Message log in a multithreaded c ++ program 



Usage
1) Include log_object.h in main.cpp and initialize LogObject class in main()

#include "log_object.h"

int main(int argc, char* argv[])
{
    LogObject log("filepath.log");
    ...
    return 0;
}

2) Include "log.h" and use ERR and OUT macros in code

#include "log.h"

void some_function() {
    ERR << "Error text";
    OUT << "Info message";
}
=======
# Log
Message log in a multithreaded c ++ program 
>>>>>>> b562c685b952e6ec12928858c9807c2b99e63458
