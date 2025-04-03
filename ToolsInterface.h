#pragma once

#include "Tools.h"

// all tools functions is accepts one string, and returns void
typedef void(*toolfuncptr_t)(const std::string& arg);

// enum of tools id's
enum TOOL_NAMES {
	TOOL_AUDIO,
	TOOL_REVERSEAUDIO,

	TOOL__MAX,
};

// strings to call tool in command line
std::string toolCallStrings[TOOL__MAX] = {
	"-aud",
	"-raud",
};

// strings for PrintHelp()
std::string toolDescriptions[TOOL__MAX] = {
	"Convert Biprolex audio file (EFFECT/SPEECH##.DAT) into wav or another audio extension using key @ox <your extension>",
	"Convert normal audio file into biprolex audio file (DAT)",
};

// ptr to the run function of selected tool
toolfuncptr_t ToolFuncPtr = 0;

// table of the run functions ptrs
toolfuncptr_t ToolFuncsTable[TOOL__MAX] = {
	&RunToolAudio,
	&RunToolReverseAudio,
};