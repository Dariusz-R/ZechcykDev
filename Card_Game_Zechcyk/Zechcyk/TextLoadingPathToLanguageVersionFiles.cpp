#include "TextLoadingPathToLanguageVersionFiles.h"

void TextLoadingPathToLanguageVersionFiles::AddNewPathToLanguageFilesFolder(std::string &path)
{
	pathToTextFileFolder = path;
}

void TextLoadingPathToLanguageVersionFiles::AddNewLanuguageFileNames(std::vector<std::string> &fileNames) {

	textFileNames = fileNames;

}