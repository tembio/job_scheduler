#include "gtest/gtest.h"
#include "argParser.h"
#include <string>
#include <vector>


namespace Scheduler{

class ArgParserTest : public ::testing::Test {
  protected:
    ArgParser parser;
    char executableName[15] = "job_scheduler";
    char taskToRun[10] = "A";
};

// parse 

TEST_F(ArgParserTest, ThrowsExceptionIfNumArgsIsLowerThan3){
  char* args[1];
  char err[] = "Invalid number of arguments";

  for(auto numArgs=0;numArgs<3;numArgs++){
    try{
      parser.parse(numArgs, args);
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
    parser.parse(argc, nullptr);
  }
  catch(const std::runtime_error &e){
    EXPECT_STREQ(err, e.what());
  }
}

TEST_F(ArgParserTest, ThrowsExceptionIfCorrespondingTaskFileIsMissing){
  const int argc = 3;
  char taskFile[] = "B.task";
  char* args[argc] = {executableName, taskToRun, taskFile};

  try{
    parser.parse(argc,args);
  }
  catch(const std::runtime_error &e){
    EXPECT_STREQ("Task file not found", e.what());
  }
}

TEST_F(ArgParserTest, DoesNotThrowExceptionIfCorrespondingTaskFileIsFound){
  const int argc = 4;
  char taskFiles[2][10] = {"B.task", "A.task"};
  char* args[argc] = {executableName, taskToRun, taskFiles[0], taskFiles[1]};

  EXPECT_NO_THROW(parser.parse(argc,args));
}

// taskFiles

TEST_F(ArgParserTest, TaskFilesReturnsEmptyVectorIfParseHasNotBeenCalled){
  auto taskFilesRead = parser.taskFiles();

  EXPECT_EQ(std::vector<std::string>{}, taskFilesRead);
}

TEST_F(ArgParserTest, TaskFilesReturnsVectorWithParsedFileNames){
  const int argc = 4;
  char taskFiles[2][10] = {"A.task", "B.task"};
  char* args[argc] = {executableName, taskToRun, taskFiles[0], taskFiles[1]};

  parser.parse(argc,args);
  
  auto taskFilesRead = parser.taskFiles();

  EXPECT_EQ(2, taskFilesRead.size());
  EXPECT_EQ(taskFiles[0], taskFilesRead[0]);
  EXPECT_EQ(taskFiles[1], taskFilesRead[1]);
}

// taskToExecute

TEST_F(ArgParserTest, TaskToExecuteReturnsEmptyStringIfParseHasNotBeenCalled){
  auto taskRead = parser.taskToExecute();

  EXPECT_EQ(std::string{}, taskRead);
}

TEST_F(ArgParserTest, TaskToExecuteNameOfTask){
  const int argc = 3;
  char taskFile[] = {"A.task"};
  char* args[argc] = {executableName, taskToRun, taskFile};

  parser.parse(argc,args);
  
  auto taskRead = parser.taskToExecute();

  EXPECT_EQ(std::string{taskToRun}, taskRead);
}

}