
#include <iostream>
#include <cassert>
#include <thread>

#include "ToolsInterface.h"
#include "ArgsParser.h"

void PrintHelp() {
	std::cout <<
		R"(
Biprolex resources Converter.

Converts Biprolex resources <-> usable extensions.

Usage:
	biprcnv <tool name> <tool arg call1> <tool arg call2> ... [custom parameters: <param> <value>   <param> <value> ...]
Usage example:
	biprcnv -aud EFFECT00.DAT EFFECT01.DAT @ox mp3 @od Converted

Custom parameters:
	@sr(sampleRate): default 22050 
	@cc(channelsCount): default 2
	@ox(outExtension): default "wav" for ToolAudio, "dat" for ToolReverseAudio
	@od(outDirectory): default ""

Tools:
)";

	for (int i = 0; i < TOOL__MAX; i++) {
		std::cout << '\t' << toolCallStrings[i] << ": " << toolDescriptions[i] << '\n';
	}

}

int main( int argc, char** argv)
{
	// tool id; 
	// -1 if unrecognized 
	char tool = -1;
	// one tool call == one argumet
	std::vector<std::string> toolCalls;

	ArgsParser argsParser;

	argsParser.LoadArguments(argc, argv);
	ParseResult parseResult = argsParser.Parse();

	if (parseResult.helpRequested) {
		PrintHelp();
		return 0;
	}

	// get id of tool from parseResult.toolName
	for (int i = 0; i < TOOL__MAX; i++) {
		if (toolCallStrings[i] == parseResult.toolName) {
			tool = i;
			break;
		}
	}

	// copy content from parseResult.toolArgs into toolCalls
	toolCalls.insert(toolCalls.begin(), parseResult.toolArgs.begin(), parseResult.toolArgs.end());

	// process custom parameters
	for (std::string*& customPrm : parseResult.customPrmsArgs) {
		customPrm[0].erase(0, 1); // erase '$' at the begin
		dprm::tryAssign(customPrm[0], customPrm[1]);

		delete[] customPrm;
	}

	if (tool == -1) {
		std::cout << "No selected tool! Try -help .\n";
		return 1;
	}
	
	ToolFuncPtr = ToolFuncsTable[tool];

	// start tools threads
	for (const std::string& callArg : toolCalls) {
		processNum++;

		std::thread(*ToolFuncPtr, callArg).detach();
	}

	std::cout << "Started " << toolCalls.size() << " processes.\n";
	std::cout << "(you can press Ctrl+C to abort processes)\n";

	// wait until all tools processes ends
	while (1) {
		if (!processNum) break;
		std::cout << "Active processes left: " << processNum << '\r';

		sf::sleep(sf::seconds(1));
	}

	return 0;
}