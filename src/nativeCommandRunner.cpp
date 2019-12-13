#include "nativeCommandRunner.h"

namespace Scheduler{

void NativeCommandRunner::run(const std::string &command){
  std::system(command.c_str());
}

}