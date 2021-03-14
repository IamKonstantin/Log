#include "log.h"

#include "log_object.h"

#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>
#include <thread>
#include <chrono>
#include <cassert>


static LogObject* singleton = nullptr;  // TODO: Add dynamic library tests. Enable mulitple log objects


std::string time_str()
{
    std::time_t t = std::time(nullptr);
    char chars[128];

    // TODO: use only chrono or only c functions
    using namespace std::chrono;
    auto ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count() % 1000llu;
    
    std::strftime(chars, sizeof(chars), "%F %T.", std::localtime(&t));
    return chars + std::to_string(ms);
}

std::string pid_str()
{
    std::stringstream ss;
    ss << "(" << std::this_thread::get_id() << ")";  // TODO: write PID which user see in system utilities
    return ss.str();
}


static std::ofstream log_file;

LogBuffer::LogBuffer(const char* file_, int line_, char type_)  // TODO: write own __FILE__ macro to show relative path
    : std::stringstream()
    , file(file_)
    , line(line_)
    , type(type_)
{
    *this << time_str() << ' ' << pid_str()
           << ' ' << (type == 'O' ? "OUT" : "ERR") << ' ';
}

LogBuffer::~LogBuffer()
{
    *this << " in " << file << ":" << line;
    singleton->push(str(), type);
}

LogObject::LogObject(const std::string& filename)
    : file(filename)
{
    assert(!singleton && "Initialize LogObject in main()");
    singleton = this;
}

LogObject::~LogObject()
{
    singleton = nullptr;
}

void LogObject::push(const std::string& line, char type)
{
    std::lock_guard<std::mutex> guard(m);

    // TODO: Can I move actions out of guard here?
    file << line << std::endl;
    if (type == 'O')
        std::cout << line << std::endl;
    else
        std::cerr << line << std::endl;
}
