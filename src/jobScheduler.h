#pragma once
#include "task.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>

namespace Scheduler{

using DependencyGraph = std::unordered_map<std::string, std::set<std::string>>;

class JobScheduler{
public:
    void run(const std::string &taskName);
    void addJob(const Task& task);
private:
    std::unordered_map<std::string, Task> nameToTask_;
    DependencyGraph dependencyGraph_; 

    void runDependencies(DependencyGraph &graph, const std::string &task) const;
    bool hasCyclicDependencies();

};

}