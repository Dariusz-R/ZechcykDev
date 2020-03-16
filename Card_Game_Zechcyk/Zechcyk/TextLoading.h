#pragma once
#include "Text.h"
#include <vector>

class TextLoading :
	public Text
{
protected:
	static std::string pathToTextFileFolder;
	static std::vector <std::string> textFileNames;

public:
	static void loadLanguageVersion();
	static void loadLanguageFile(std::vector<std::string>&, std::string = "", char = '#');

};

