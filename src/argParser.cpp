#include "argParser.h"
#include <iostream>

void ArgParser::parse(int argc, char* argv[]){
	if(argc < 3)
		throw std::runtime_error{"Invalid number of arguments"};
	if(argv == nullptr)
		throw std::runtime_error{"Null argument list"};

	auto task = std::string{argv[1]};
	bool taskFileFound = false;

	for(auto arg = 2; arg < argc && !taskFileFound; arg++){
		auto file = std::string{argv[arg]};
		if(file.find(task) != std::string::npos)
			taskFileFound = true;
	}

	if(!taskFileFound){
		throw std::runtime_error{"Task file not found"};
	}
}