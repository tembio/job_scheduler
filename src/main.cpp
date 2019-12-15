#include <stdexcept>
#include <iostream>
#include <fstream>
#include "argParser.h"
#include "jobScheduler.h"
#include "task.h"


int main(int argc, char* argv[]){
	try{
		Scheduler::ArgParser parser(argc, argv);
		Scheduler::JobScheduler scheduler;

		for(auto taskFile : parser.taskFiles()){
			std::ifstream file(taskFile);
			Scheduler::Task task(file);
			file.close();

			scheduler.addJob(task);
		}

		scheduler.run(parser.taskToExecute());

	}catch(const std::runtime_error& e){
		std::cout<<e.what()<<"\n";
	}
}