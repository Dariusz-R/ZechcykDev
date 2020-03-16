#pragma once
#include "TextLoading.h"
#include <vector>
class TextLoadingPathToLanguageVersionFiles :
	public TextLoading
{

	static void AddNewPathToLanguageFilesFolder(std::string&);
	static void AddNewLanuguageFileNames(std::vector<std::string>&);
};

