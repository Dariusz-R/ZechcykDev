#include "Text.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Auction.h"
#include "Game.h"


std::vector <std::string> Text::start_menu;
std::string Text::one_line_frame = "\t\t\t\t\t\t\t\t*\r\t*";
std::vector <std::string> Text::pl_OR_eng;
std::vector <std::string> Text::A_4;
std::vector <std::string> Text::A_8;
std::vector <std::string> Text::Warsow_txt;
std::vector <std::string> Text::log_frames;
std::vector <std::string> Text::log_message;
std::vector <std::string> Text::game_log_message;
std::vector <std::string> Text::frames;
std::vector <std::string> Text::auction_text;
std::vector <std::string> Text::auction_summary;
std::string Text::language_version;


void Text::set_language_version(std::string lang) {
	language_version = lang; 
}


void Text::readText(std::vector <std::string> what, short begin, short end) {
	if (end == 0) {
		end = what.size(); 
		for (short i = begin; i < end; i++)
			std::cout << what[i];
	} else if ((begin + end) <= what.size()) {
		for (short i = begin; i < (begin + end); i++)
			std::cout << what[i];
	} else 
		std::cout << "Cos nie tak z czytaniem tekstu";
}

short Text::cinCheck(short& cin_value , short range, bool first_menu)
{

	
		if (std::cin.fail() || cin_value > range || cin_value < 1)
		{
			std::cin.clear();
			std::cin.ignore(100, '\n'); ///// !!!!!!!!!!!!!!!!!!!!!!1
			system("CLS");
			if (first_menu == true) {
				readText(pl_OR_eng, 1, 1);
				std::cout << std::endl;
				readText(pl_OR_eng, 2, 1);
				std::cout << std::endl << std::endl << "                 ";
			}
			else{
				if (language_version == "Polish") {
					readText(pl_OR_eng, 1, 1);
					std::cout << std::endl << std::endl << "                 ";
				}
				else if (language_version == "English") {
					readText(pl_OR_eng, 2, 1);
					std::cout << std::endl << std::endl << "                 ";
				}
			}
			system("pause");
			system("CLS");
			return cin_value = 0;
		}
		else return cin_value;
	
}
void Text::cinCheck(short& cin_value, short range, std::vector <short> allowed_values)
{
	bool correct_value = true;
	
	if (std::cin.fail() || cin_value > range - 1 || cin_value < 0)
	{
		std::cin.clear();
		std::cin.ignore(100, '\n'); ///// !!!!!!!!!!!!!!!!!!!!!!1
		correct_value = false;
	} else if (!allowed_values.empty()) {
		correct_value = false;
		for (short i = 0; i < allowed_values.size(); i++)
			if (cin_value == allowed_values[i])
				correct_value = true;
	}
	if (correct_value == false) {
		if (language_version == "Polish") {
			readText(pl_OR_eng, 1, 1);
		}
		else if (language_version == "English") {
			readText(pl_OR_eng, 2, 1);
			
		}
		std::cout << std::endl << std::endl << "                 ";
		system("pause");
		cin_value = -1;


	}

	

}











void Text::show_first_auction_menu(Player * player, short situation) {

	std::cout << Text::frames[1];
	Auction::displayAuctionLog(true);
	std::cout << Text::frames[0];
	player->show(4 , "AUCTION");
	std::cout << Text::frames[6];
	std::cout << Text::auction_text[0];
	switch (situation) {
	case 0:
		std::cout << Text::auction_text[1];
		break;
	case 1:
		std::cout << Text::auction_text[2];
		break;
	case 2:
		std::cout << Text::auction_text[3];
		break;
	default:
		system("CLS");
		std::cout << "ERROR 55" << std::endl;
		system("pause");
	}
	std::cout << Text::frames[9];
	std::cout << Text::frames[10];

}
	


	
void Text::showGame(Player* player, std::vector<short> what_may_I_throw_copy) {

	std::cout << frames[1];
	Auction::displayAuctionLog(false);
	std::cout << frames[0];
	std::cout << frames[2];
	Game::read_game_log();
	Game::read_trick_log();
	std::cout << frames[0];
	player->show(8, "GAME");
	player->showMeWhatICanThrow(what_may_I_throw_copy);
	std::cout << frames[12];
}

