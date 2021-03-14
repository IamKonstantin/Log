#pragma once

#include <fstream>
#include <mutex>
#include <string>


class LogObject {
public:
  LogObject(const std::string& filename);
  ~LogObject();

  void push(const std::string& line, char type);  // TODO: Use stack as buffer to able to log memory leaks
private:
  std::mutex m;
  std::ofstream file;
};
