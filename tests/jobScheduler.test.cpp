#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "jobScheduler.h"
#include "task.h"
#include "nativeCommandRunner.mock.h"
#include <string>
#include <vector>

using ::testing::InSequence;

namespace Scheduler{

class JobSchedulerTest : public ::testing::Test {
  protected:
    JobScheduler scheduler;
    std::shared_ptr<MockNativeCommandRunner> cmdRunnerMock;

    void SetUp() override {
        cmdRunnerMock = std::make_shared<MockNativeCommandRunner>();
    }

    Task createTask(std::string name, std::string dependencies, std::string command){
        std::stringstream taskContent;
        taskContent << name << "\n" 
                    << command  << "\n" 
                    << dependencies; 
        return Task(taskContent, cmdRunnerMock);
    }
};

// Constructor

TEST_F(JobSchedulerTest, RunThrowsExceptionIfNoTasksDefinitionsProvided){
  try{
    scheduler.run("taskName");
    FAIL();
  }
  catch(const std::runtime_error &e){
    EXPECT_STREQ("No task definition provided for taskName", e.what());
  }
}

TEST_F(JobSchedulerTest, RunExecutesTargetTaskWhenDefinitionIsProvided){

    std::string command{"commandA"};
    std::string target{"A"};

    Task job =  createTask(target, "", command);
    scheduler.addJob(job);

    EXPECT_CALL(*cmdRunnerMock, run(command)).Times(1);

    scheduler.run(target);
}

TEST_F(JobSchedulerTest, RunExecutesDependenciesWhenDefinitionIsProvided){
    Task job1 =  createTask("A", "B1, B2", "commandA");
    Task job2 =  createTask("B1", "C", "commandB1");
    Task job3 =  createTask("B2", "", "commandB2");
    Task job4 =  createTask("C", "",  "commandC");
    
    scheduler.addJob(job1);
    scheduler.addJob(job2);
    scheduler.addJob(job3);
    scheduler.addJob(job4);

    {
        InSequence s;
        EXPECT_CALL(*cmdRunnerMock, run("commandC")).Times(1);
        EXPECT_CALL(*cmdRunnerMock, run("commandB1")).Times(1);
        EXPECT_CALL(*cmdRunnerMock, run("commandB2")).Times(1);
        EXPECT_CALL(*cmdRunnerMock, run("commandA")).Times(1);
    }

    scheduler.run("A");
}

TEST_F(JobSchedulerTest, RunThrowsExceptionWhenDependenciesDefinitionIsNotProvided){
    Task job1 =  createTask("A", "B", "commandA");
    Task job2 =  createTask("B", "C", "commandB");
    
    scheduler.addJob(job1);
    scheduler.addJob(job2);

    try{
        scheduler.run("A");
        FAIL();
    }
    catch(const std::runtime_error &e){
        EXPECT_STREQ("No task definition provided for C", e.what());
    }
}


TEST_F(JobSchedulerTest, RunThrowsExceptionWhenCyclicDependencies){
    Task job1 =  createTask("A", "B", "commandA");
    Task job2 =  createTask("B", "A", "commandB");

    scheduler.addJob(job1);
    scheduler.addJob(job2);

    try{
        scheduler.run("A");
        FAIL();
    }
    catch(const std::runtime_error &e){
        EXPECT_STREQ("Cyclic dependencies", e.what());
    }
}

}