#include "ArgsParser.h"
#include <cassert>

void ArgsParser::LoadArguments(const int& argc,  char** argv)
{

	// skip first <this>.exe argument
	for (int i = 1; i < argc; i++) {
		args.push_back(argv[i]);
	}
}

ParseResult ArgsParser::Parse()
{
	ParseResult result;

	for (int i = 0; i < args.size(); i++) {
		if (args[i][0] == '-') {
			// handle -help/-h
			if (args[i] == "-help" || args[i] == "-h") {
				result.helpRequested = 1;
				continue;
			}

			result.toolName = args[i];
			continue;
		}

		if (args[i][0] == '@') {
			assert(i + 1 < args.size());

			result.customPrmsArgs.push_back(
				new std::string[2]
				{ args[i], args[i + 1] }
			);

			i++;
			continue;
		}

		result.toolArgs.push_back(args[i]);
	}

	return result;
}
