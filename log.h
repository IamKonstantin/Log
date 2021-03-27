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

#pragma once

#include <sstream>

#ifdef SOURCE_PATH_SIZE
#  define __FILENAME__ (__FILE__ + SOURCE_PATH_SIZE)
#else
#  define __FILENAME__ __FILE__
#endif

/*
 *  Usage:
 *  LOG << "Can't send message: " << exeption.what() << std::endl;
 *  OUT << "Waiting for listener..." << std::endl;
 *
 *  2020-08-26 20:17:08.921 (12345) ERR Can't send message: endpoint is empty in sender.cpp:26
 *  2020-08-26 20:17:08.921 (12345) OUT Waiting for listener... in listener.cpp:27
 */
#define ERR LogBuffer(__FILENAME__, __LINE__, 'E')
#define OUT LogBuffer(__FILENAME__, __LINE__, 'O')


class LogBuffer : public std::stringstream {
public:
  LogBuffer(const char* file, int line, char type);
  ~LogBuffer();
private:
  const char* file;
  const int line;
  const char type;
};
