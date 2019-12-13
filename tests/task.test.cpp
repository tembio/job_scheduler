#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "nativeCommandRunner.mock.h"
#include "task.h"
#include <bits/stdc++.h> 
#include <string>
#include <sstream>
#include <vector>

namespace Scheduler{

class TaskTest : public ::testing::Test {
  protected:
  std::string taskName;
  std::string command;
  std::string dependencies;
};

// Constructor 

TEST_F(TaskTest, CtorThrowsExecptionWhitInvalidStream){
  std::stringstream taskContent;
  taskContent.setstate(std::ios::badbit);

  try{
    Task task(taskContent);
    FAIL();
  }
  catch(const std::runtime_error &e){
    EXPECT_STREQ("Error reading task", e.what());
  }
}

// Name

TEST_F(TaskTest, NameReturnsNameOfCreatedTask){
  taskName = "A";

  std::stringstream taskContent;
  taskContent << taskName << "\n" 
              << command  << "\n" 
              << dependencies; 

  Task task(taskContent);
  
  EXPECT_EQ(taskName, task.name());
}

// Dependencies

TEST_F(TaskTest, DependenciesReturnsEmptyListWhenNoDepenecies){
  taskName = "A";
  std::stringstream taskContent;
  taskContent << taskName << "\n" 
              << command  << "\n";

  Task task(taskContent);
  
  auto dependencies = task.dependencies();
  
  EXPECT_EQ(0, dependencies.size());
}

TEST_F(TaskTest, DependenciesReturnsListOfDepenecies){
  taskName = "A";
  command = "command";
  dependencies = "B, C";
  std::stringstream taskContent;
  taskContent << taskName << "\n" 
              << command  << "\n" 
              << dependencies; 

  Task task(taskContent);
  
  auto dependencies = task.dependencies();

  EXPECT_EQ("B", dependencies[0]);
  EXPECT_EQ("C", dependencies[1]);
}

// Run

TEST_F(TaskTest, RunExecutesCallsNativeCommand){
  taskName = "A";
  command = "nativeCommand";
  std::stringstream taskContent;
  taskContent << taskName << "\n" 
              << command  << "\n";

  auto mockCommandRunner = std::make_shared<MockNativeCommandRunner>();

  Task task(taskContent, mockCommandRunner);
  
  EXPECT_CALL(*mockCommandRunner, run(command)).Times(1);

  task.run();
}


}