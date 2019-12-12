#pragma once
#include <vector>
#include <string>

namespace Scheduler{

class ArgParser{
public:
	void parse(int argc, char* argv[]);
	std::vector<std::string> taskFiles();
	std::string taskToExecute();
private:
	std::vector<std::string> taskFiles_;
	std::string taskToExecute_;
};

}