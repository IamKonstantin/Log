/*

MIT License

Copyright (c) 2021 Konstantin Ivanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

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
  using namespace std::chrono;
  auto time_point = system_clock::now();
  std::time_t ctime = system_clock::to_time_t(time_point);
  char time_str[24];
  int ms = duration_cast< milliseconds >(time_point.time_since_epoch()).count() % 1000llu;
  std::strftime(time_str, sizeof(time_str), "%F %T.", std::localtime(&ctime));  // TODO: use localtime_s
  std::sprintf(time_str + 20, "%.3d", ms);   // TODO: use sprintf_s

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
  *this << " in " << file << ":" << line << std::endl;
  singleton->push(str(), type);
}

LogObject::LogObject(const std::string& filename)
    : file(filename)
{
  log_set_log_object(this);
}

LogObject::~LogObject()
{
  log_reset_log_object();
}

void LogObject::push(const std::string& line, char type)
{
  file << line << std::flush;
  if (type == 'O')
    std::cout << line << std::flush;
  else
    std::cerr << line << std::flush;
}

void log_set_log_object(LogObject* log_object) {
  assert(!singleton && "Log object is already set");
  singleton = log_object;
}
void log_reset_log_object() {
  assert(singleton && "Nothing to reset");
  singleton = nullptr;
}
