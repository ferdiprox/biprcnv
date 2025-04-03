#include "DefaultPrms.h"

#include <iostream>

namespace dprm {
	int sampleRate = 22050;
	int channelCount = 2;
	std::string outExtension = "";
	std::string outDirectory = "";
}

void dprm::tryAssign(const std::string& prmArg, const std::string& valArg)
{
	int asInt = atoi(valArg.c_str());

	if (prmArg == "sr") {
		dprm::sampleRate = asInt;
	}
	else if (prmArg == "cc") {
		dprm::channelCount = asInt;
	}
	else if (prmArg == "ox") {
		dprm::outExtension = valArg;
	}
	else if (prmArg == "od") {
		dprm::outDirectory = valArg + '/';
	}
	else {
		std::cout << "Unknown parameter argument: " << prmArg << '\n';
	}
}
