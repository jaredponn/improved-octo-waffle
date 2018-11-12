#pragma once

#include <iostream>

class Logger
{
    private:
	static constexpr unsigned int LOGGING_LEVEL = 0;

    public:
	static void logMessage(const char *const a)
	{
		std::cout << a << std::endl;
	}
};
