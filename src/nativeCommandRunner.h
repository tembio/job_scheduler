#pragma once

#include <string>

namespace Scheduler{

class INativeCommandRunner {
public:
    virtual void run(const std::string &command) = 0;
    virtual ~INativeCommandRunner() {};    
};

class NativeCommandRunner : public INativeCommandRunner {
public:
    void run(const std::string &command) override;
};

}