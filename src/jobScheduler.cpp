#include "jobScheduler.h"

namespace Scheduler{

std::string taskNotDefinedMsg(std::string taskName){
    return std::string{"No task definition provided for "} + taskName; 
}

bool checkForCycles(DependencyGraph &graph, std::unordered_set<std::string> &visited, const std::string &task){
    if(visited.find(task) != visited.end())
        return true;

    visited.insert(task);
    for(auto dependency : graph[task]){
        if(checkForCycles(graph, visited, dependency))
            return true;
    }
    return false;
}

bool JobScheduler::hasCyclicDependencies(){
    for(auto task : nameToTask_){
        std::unordered_set<std::string> visited;
        if(checkForCycles(dependencyGraph_, visited, task.first))
          return true;
    }
    return false;
}

void JobScheduler::runDependencies(DependencyGraph &graph, const std::string &task) const{
    for(auto dependency : graph[task]){
        runDependencies(graph, dependency);
    }

    try{
      nameToTask_.at(task).run();
    }catch(const std::out_of_range& oor){
      throw std::runtime_error{taskNotDefinedMsg(task).c_str()};
    }
}

void JobScheduler::run(const std::string &taskName){
    auto initalTaskDefined = nameToTask_.find(taskName) != nameToTask_.end();
    if(!initalTaskDefined)
      throw std::runtime_error{taskNotDefinedMsg(taskName).c_str()};

    if(hasCyclicDependencies())
      throw std::runtime_error{"Cyclic dependencies"};

    runDependencies(dependencyGraph_, taskName);
}

void JobScheduler::addJob(const Task& task){
    nameToTask_.insert({task.name(),task});

    auto dependencies = task.dependencies();
    dependencyGraph_.insert({task.name(), {dependencies.begin(), dependencies.end()}});
}

}