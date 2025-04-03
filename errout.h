#pragma once

#include "fFile.h"
#include <iostream>

// critical error at the tool runtime
#define TOOL_ERR(msg) SaveErrorFile(msg, "Tool", __FILE__, __LINE__)

#define SET_FH() errFuncHandle = __FUNCTION__
#define RESET_FH() errFuncHandle.clear()

static std::string errFuncHandle;

inline void SaveErrorFile(const std::string& message, const std::string& errpoint, const std::string& srcfile, int srcline) {
	std::cout
		<< "CRITICAL ERROR HANDLED\n"
		<< '"' << message << "\"\n"
		<< "See "<<errpoint <<".err.log to get more error information.\n";
	
	fFile out(errpoint + ".err.log", fFile::AS_OUTPUT);

	out.fileData =
		errpoint + " runtime error;\n" +
		"Error message=" + message + ";\n" +
		"Error func=" + (errFuncHandle.empty() ? "<UNHANDLED>" : errFuncHandle) + ";\n" +
		"Error file=" + srcfile + ";\n" + 
		"Error line=" + std::to_string(srcline) + ";\n";

	out.Close();

	exit(-1);
}