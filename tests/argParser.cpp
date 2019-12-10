#include "gtest/gtest.h"
#include "argParser.h"
#include <string>

class ArgParserTest : public ::testing::Test {
  protected:
    ArgParser parser;
    char executableName[15] = "job_scheduler";
    char taskToRun[10] = "A";
};

// Parse 

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
