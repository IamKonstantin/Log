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
