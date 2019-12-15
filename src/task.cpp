#include "task.h"
#include "nativeCommandRunner.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>

namespace Scheduler{

Task::Task(std::istream &taskFile, std::shared_ptr<INativeCommandRunner> commandRunner){
    if(!taskFile) 
      throw std::runtime_error{"Error reading task file"};
    
    std::getline(taskFile, name_);
    std::getline(taskFile, command_);

    std::string dependency;
    while(taskFile >> dependency){
        auto endsInComma = dependency.size()>1 && dependency[dependency.size()-1]==',';
        if(endsInComma){
            dependencies_.push_back(dependency.substr (0,dependency.size()-1));
        }else{
            dependencies_.push_back(dependency);
        }
    }

    cmdRunner_ = commandRunner ? commandRunner : std::make_shared<NativeCommandRunner>(); 
    

}

std::string Task::name() const{
    return name_;
}

std::vector<std::string> Task::dependencies() const{
  return dependencies_;
}

void Task::run() const{
  cmdRunner_->run(command_);
}

}