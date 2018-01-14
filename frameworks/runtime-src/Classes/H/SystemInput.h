#pragma once

#include <H/Source.h>
#include <functional>

namespace sys {
	class SystemInput
	{
		public:
			SystemInput();
			~SystemInput();

			std::string getLastInput();
			static int listenCommand(const std::string &command, std::function<void(const std::vector<std::string>&)> listener);

		private:
			static SystemInput *instance;

			void standartInputHandle();
			void proceedCommand(const std::string &command, const std::string &rawargs);

			struct Handler{
				std::string command;
				std::function<void(const std::vector<std::string>&)> funtion;
				int ID;
				bool operator== (const std::string &command) const { return this->command == command; }
			};
			std::vector<Handler> handlers;

			std::string lastInput;
	};

}
