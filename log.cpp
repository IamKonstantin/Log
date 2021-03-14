#include "log.h"

#ifdef __linux__
#  include <unistd.h>
#endif

#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>
#include <chrono>
#include <cassert>

#include "log_object.h"


static LogObject* singleton = nullptr;  // TODO: Enable mulitple log objects


LogBuffer::LogBuffer(const char* file_, int line_, char type_)
  : std::stringstream()
  , file(file_)
  , line(line_)
  , type(type_)
{
  auto time_point = std::chrono::system_clock::now();
  std::time_t ctime = std::chrono::system_clock::to_time_t(time_point);
  char time_str[24];
  using namespace std::chrono;
  int ms = std::chrono::duration_cast< std::chrono::milliseconds >(time_point.time_since_epoch()).count() % 1000llu;
  std::strftime(time_str, sizeof(time_str), "%F %T.", std::localtime(&ctime));
  std::sprintf(time_str + 20, "%.3d", ms);

  *this << time_str << " (";
#ifdef __linux__
  *this << getpid();
#else
#  error TODO: write Process ID which user see in system utilities on Windows
#endif
  *this << ") " << (type == 'O' ? "OUT" : "ERR") << ' ';
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
