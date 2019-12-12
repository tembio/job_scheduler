#pragma once
#include <vector>
#include <string>

namespace Scheduler{

class ArgParser{
public:
	ArgParser(int argc, char* argv[]);
	std::vector<std::string> taskFiles() const;
	std::string taskToExecute() const;
private:
	std::vector<std::string> taskFiles_;
	std::string taskToExecute_;
};

}