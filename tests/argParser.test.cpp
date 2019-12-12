#include "gtest/gtest.h"
#include "argParser.h"
#include <string>
#include <vector>


namespace Scheduler{

class ArgParserTest : public ::testing::Test {
  protected:
    char executableName[15] = "job_scheduler";
    char taskToRun[10] = "A";
};

// Constructor

TEST_F(ArgParserTest, ThrowsExceptionIfNumArgsIsLowerThan3){
  char* args[1];
  char err[] = "Invalid number of arguments";

  for(auto numArgs=0;numArgs<3;numArgs++){
    try{
      ArgParser parser(numArgs, args);
      FAIL();
    }
    catch(const std::runtime_error &e){
      EXPECT_STREQ(err, e.what());
    }
  }
}

TEST_F(ArgParserTest, ThrowsExceptionIfArgsIsNull){
  const int argc = 3;
  char err[] = "Null argument list";

  try{
    ArgParser parser(argc, nullptr);
    FAIL();
  }
  catch(const std::runtime_error &e){
    EXPECT_STREQ(err, e.what());
  }
}

// taskFiles

TEST_F(ArgParserTest, TaskFilesReturnsVectorWithParsedFileNames){
  const int argc = 4;
  char taskFiles[2][10] = {"A.task", "B.task"};
  char* args[argc] = {executableName, taskToRun, taskFiles[0], taskFiles[1]};

  ArgParser parser(argc, args);
  
  auto taskFilesRead = parser.taskFiles();

  EXPECT_EQ(2, taskFilesRead.size());
  EXPECT_EQ(taskFiles[0], taskFilesRead[0]);
  EXPECT_EQ(taskFiles[1], taskFilesRead[1]);
}

// taskToExecute

TEST_F(ArgParserTest, TaskToExecuteReturnsNameOfTask){
  const int argc = 3;
  char taskFile[] = {"A.task"};
  char* args[argc] = {executableName, taskToRun, taskFile};

  ArgParser parser(argc, args);
  
  auto taskRead = parser.taskToExecute();

  EXPECT_EQ(std::string{taskToRun}, taskRead);
}

}