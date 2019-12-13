#include "gmock/gmock.h"
#include "nativeCommandRunner.h"

namespace Scheduler{

class MockNativeCommandRunner : public INativeCommandRunner {
 public:
  MOCK_METHOD1(run, void(const std::string&));
};

}