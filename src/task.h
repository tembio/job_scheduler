#pragma once
#include "nativeCommandRunner.h"
#include <vector>
#include <string>
#include <istream>
#include <memory>

namespace Scheduler{

class Task{
public:
    Task(std::istream &taskFile, std::shared_ptr<INativeCommandRunner> = nullptr);
    std::string name() const;
    std::vector<std::string> dependencies() const;
    void run() const;
private:
    std::string name_;
    std::string command_;
    std::vector<std::string> dependencies_;
    std::shared_ptr<INativeCommandRunner> cmdRunner_;
};

}