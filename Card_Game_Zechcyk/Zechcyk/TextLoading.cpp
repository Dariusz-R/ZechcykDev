#include "TextLoading.h"
#include <iostream>
#include <fstream>


static std::string pathToTextFileFolder;
static std::vector <std::string> textFileNames;

void TextLoading::loadLanguageVersion()
{
	
	if (language_version == "") loadLanguageFile(pl_OR_eng);
	else if (language_version == "Polish") {
		loadLanguageFile(start_menu, "start_menu_pl.txt");
		loadLanguageFile(log_frames, "log_frames_pl.txt");
		loadLanguageFile(log_message, "auction_log_message_pl.txt", '\n');
		loadLanguageFile(A_4, "auction_four_cards_pl.txt");
		loadLanguageFile(A_8, "auction_eight_cards_pl.txt");
		loadLanguageFile(Warsow_txt, "game_warsow_pl.txt");
		loadLanguageFile(game_log_message, "game_log_message_pl.txt", '\n');
		loadLanguageFile(frames, "frames_pl.txt");
		loadLanguageFile(auction_text, "auction_pl.txt");
		loadLanguageFile(auction_summary, "auction_summary_pl.txt", '\n');
	}
	else if (language_version == "English") {
		loadLanguageFile(start_menu, "start_menu_eng.txt");
		loadLanguageFile(log_frames, "log_frames_eng.txt");
		loadLanguageFile(log_message, "auction_log_message_eng.txt", '\n');
		loadLanguageFile(A_4, "auction_four_cards_eng.txt");
		loadLanguageFile(A_8, "auction_eight_cards_eng.txt");
		loadLanguageFile(Warsow_txt, "game_warsow_eng.txt");
		loadLanguageFile(game_log_message, "game_log_message_eng.txt", '\n');
		loadLanguageFile(frames, "frames_eng.txt");
		loadLanguageFile(auction_text, "auction_eng.txt");
	}
}

void TextLoading::loadLanguageFile(std::vector <std::string>& vector_name, std::string file_name, char delim) {

	std::string line;
	std::fstream file;

	//std::string path;

	//if (language_version == "Polish") {
	//	path = ".\\Polish\\";
	//	path.append(file_name);
	//}
	//else if (language_version == "English") {
	//	path = ".\\English\\";
	//	path.append(file_name);
	//}
	//else if (language_version == "") path = ".\\Select_language\\pl_OR_eng.txt";


	file.open(pathToTextFileFolder+lan, std::ios::in);


	if (file.good() == false)
	{
		std::cout << "Blad podczas otwierania skryptu." << std::endl << std::endl;
		exit(0);
	}
	while (getline(file, line, delim))
	{
		vector_name.push_back(line);
	}
	file.close();

}
