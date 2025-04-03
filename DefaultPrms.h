#pragma once

#include <string>

namespace dprm {
	extern int sampleRate;
	extern int channelCount;
	extern std::string outExtension;
	extern std::string outDirectory;

	void tryAssign(const std::string& prmArg, const std::string& valArg);
}

