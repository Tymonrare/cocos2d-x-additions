#include "H/SystemInput.h"

#include <boost/algorithm/string.hpp>

//Treading
#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include <mutex>

using namespace sys;
std::mutex mutex;

SystemInput *SystemInput::instance = nullptr;

void SystemInput::standartInputHandle(){
	std::string input;
	while(true){
		std::cout << "$:";

		std::getline(std::cin >> std::ws,input);


		std::lock_guard<std::mutex> guard(mutex);
		lastInput = input;

		std::string args = "";
		auto argsindex = input.find_first_of(" ");
		if(argsindex != input.npos)
			 args = input.substr(argsindex+1);

		proceedCommand(input.substr(0, argsindex), args);
	}
}

SystemInput::SystemInput(){
	instance = this;

	std::thread thread(&SystemInput::standartInputHandle, this);
	thread.detach();

	listenCommand("call", 
			[](const std::vector<std::string>& v)
			{
			std::cout << "calling.... ";
				for(auto i : v){
					std::cout << i << '\n';
				}
			});
}

SystemInput::~SystemInput(){
}

std::string SystemInput::getLastInput(){
	std::lock_guard<std::mutex> guard(mutex);
	return lastInput;
}

int SystemInput::listenCommand(const std::string &command, std::function<void(const std::vector<std::string>&)> listener){
	Handler h {
		command,
		listener,
		(int)instance->handlers.size()
	};

	instance->handlers.push_back(h);

	return h.ID;
}
void SystemInput::proceedCommand(const std::string &command, const std::string &rawargs){
	std::cout << "Command is: " << command << ";\n";
	std::cout << "Arguments is: " << rawargs << ";\n";

	std::vector<std::string> args;
	boost::split(args, rawargs, boost::is_any_of("\t "));

	for(auto i : handlers){
		if(i == command)
			i.funtion(args);
	}
}
