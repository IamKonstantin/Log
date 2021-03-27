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
