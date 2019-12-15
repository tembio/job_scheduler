#include "argParser.h"
#include <stdexcept>

namespace Scheduler{

ArgParser::ArgParser(int argc, char* argv[]){
	if(argc < 3)
		throw std::runtime_error{"Invalid number of arguments"};
	if(argv == nullptr)
		throw std::runtime_error{"Null argument list"};

	taskToExecute_ = std::string{argv[1]};

	for(auto arg = 2; arg < argc; arg++){
		auto file = std::string{argv[arg]};
		taskFiles_.push_back(file);
	}
}

std::vector<std::string> ArgParser::taskFiles() const{
	return taskFiles_;
}

std::string ArgParser::taskToExecute() const{
	return taskToExecute_;
}

}