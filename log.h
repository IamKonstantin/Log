#pragma once

#include <sstream>


/*
 *  Usage:
 *  LOG << "Can't send message: " << exeption.what() << std::endl;
 *  OUT << "Waiting for listener..." << std::endl;
 *
 *  2020-08-26 20:17:08.921 (140596326537088) in sender.cpp:26 ERR Can't send message: endpoint is empty                               
 *  2020-08-26 20:17:08.921 (140596309591808) in listener.cpp:27 OUT Waiting for listener...                                 
 */
#define ERR LogBuffer(__FILE__, __LINE__, 'E')
#define OUT LogBuffer(__FILE__, __LINE__, 'O')


class LogBuffer : public std::stringstream {
public:
  LogBuffer(const char* file, int line, char type);
  ~LogBuffer();
private:
  const char* file;
  const int line;
  const char type;
};
