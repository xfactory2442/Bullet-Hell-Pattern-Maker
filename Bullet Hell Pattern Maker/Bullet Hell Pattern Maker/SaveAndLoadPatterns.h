#pragma once
#include "Pattern.h"
class SaveAndLoadPatterns
{
public:
	static void SavePattern(Pattern* pattern);
	static Pattern* LoadPattern(std::string filename);
};

