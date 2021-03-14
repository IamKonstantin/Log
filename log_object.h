#pragma once

#include <fstream>
#include <mutex>
#include <string>


class LogObject {
public:
    LogObject(const std::string& filename);
    ~LogObject();

    void push(const std::string& line, char type);
private:
    std::mutex m;
    std::ofstream file;
};
