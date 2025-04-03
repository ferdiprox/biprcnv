#include "Tools.h"

size_t processNum = 0;

#define END_PROCESS()	\
RESET_FH();		\
processNum--;	\
return

void ResetExtension(std::string & fname, const std::string & newExt) {
	size_t rightestDotPos = fname.rfind('.');

	// no extension
	if (rightestDotPos == std::string::npos) {
		fname += newExt;
		return;
	}

	rightestDotPos++;

	fname.erase(rightestDotPos, fname.size() - rightestDotPos);

	fname += newExt;
}

void RunToolAudio(const std::string& mainArg)
{
	SET_FH();

	if (dprm::outExtension.empty()) {
		dprm::outExtension = "wav";
	}

	fFile inputFile(fFile::AS_INPUT);

	fresult result = inputFile.Open(mainArg);

	if (result != fFile::CODE_SUCCESS) {
		//TOOL_ERR(fFile::strCode(result));
		END_PROCESS();
	}

	sf::SoundBuffer sndBuf;

	size_t sampleCount = inputFile.fileData.size() / dprm::channelCount;

	std::string outName = dprm::outDirectory + mainArg ;

	ResetExtension(outName, dprm::outExtension);

	if (!sndBuf.loadFromSamples(
		reinterpret_cast<const sf::Int16*>(inputFile.fileData.data()),
		sampleCount,
		dprm::channelCount, dprm::sampleRate)
		) {
		TOOL_ERR("Loading samples error");
	}

	if (!sndBuf.saveToFile(outName)) {
		TOOL_ERR("Saving samples error");
	}

	END_PROCESS();
}

void RunToolReverseAudio(const std::string& mainArg)
{
	SET_FH();

	if (dprm::outExtension.empty()) {
		dprm::outExtension = "dat";
	}

	sf::SoundBuffer sndBuf;

	if (!sndBuf.loadFromFile(mainArg)) {
		TOOL_ERR("Loading audio file error");
	}

	fFileStream out(fFile::AS_OUTPUT);

	std::string outName = mainArg;

	ResetExtension(outName, dprm::outExtension);

	fresult result = out.Open(outName);

	if (result != fFile::CODE_SUCCESS) {
		END_PROCESS();
	}

	const sf::Int16* samples = sndBuf.getSamples();
	size_t samplesCount = sndBuf.getSampleCount();

	int sampleRate = sndBuf.getSampleRate();
	int step = sampleRate / dprm::sampleRate; 
	if (step <= 0) {
		step = 1;
	}

	for (int i = 0; i < samplesCount; i += step) {
		out.Writeb(samples[i]);
	}

	out.Close();

	END_PROCESS();
}
