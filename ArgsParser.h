#pragma once

#include <string>
#include <vector>

struct ParseResult {
	std::string toolName;
	std::vector<std::string> toolArgs;

	std::vector<std::string*> customPrmsArgs;

	bool helpRequested = 0;
};

class ArgsParser
{
public:

	void LoadArguments(const int& argc, char** argv);
	ParseResult Parse();

private:

	std::vector < std::string> args;
};

