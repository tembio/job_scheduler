#pragma once
#include <vector>
#include <string>

namespace Scheduler{

class ArgParser{
public:
	void parse(int argc, char* argv[]);
	std::vector<std::string> taskFiles();
private:
	std::vector<std::string> taskFiles_;
};

}