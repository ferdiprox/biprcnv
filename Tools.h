#pragma once

#include "DefaultPrms.h"
#include "fFile.h"
#include "errout.h"

// TODO: using SFML to convert audio formats is cringy...
// i should find another way.
#include <SFML/Audio.hpp>

extern size_t processNum;

void RunToolReverseAudio(const std::string & mainArg);

void RunToolAudio(const std::string & mainArg);