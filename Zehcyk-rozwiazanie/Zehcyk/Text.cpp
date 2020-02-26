#include "Text.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Auction.h"
#include "Game.h"


std::vector <std::string> Text::pl_OR_eng;
std::vector <std::string> Text::start_menu;
std::vector <std::string> Text::A_4;
std::vector <std::string> Text::A_8;
std::vector <std::string> Text::Warsow_txt;
std::vector <std::string> Text::log_frames;
std::vector <std::string> Text::log_message;
std::vector <std::string> Text::game_log_message;
std::vector <std::string> Text::frames;
std::vector <std::string> Text::auction_text;
std::string Text::language_version;
std::string Text::one_line_frame = "\t\t\t\t\t\t\t\t*\r\t*";

void Text::set_language_version(std::string lang) {
	language_version = lang; 
}


void Text::read_text(std::vector <std::string> what, short begin, short end) {
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

short Text::cin_check(short& cin_value , short range, bool first_menu)
{

	
		if (std::cin.fail() || cin_value > range || cin_value < 1)
		{
			std::cin.clear();
			std::cin.ignore(100, '\n'); ///// !!!!!!!!!!!!!!!!!!!!!!1
			system("CLS");
			if (first_menu == true) {
				read_text(pl_OR_eng, 1, 1);
				std::cout << std::endl;
				read_text(pl_OR_eng, 2, 1);
				std::cout << std::endl << std::endl << "                 ";
			}
			else{
				if (language_version == "Polish") {
					read_text(pl_OR_eng, 1, 1);
					std::cout << std::endl << std::endl << "                 ";
				}
				else if (language_version == "English") {
					read_text(pl_OR_eng, 2, 1);
					std::cout << std::endl << std::endl << "                 ";
				}
			}
			system("pause");
			system("CLS");
			return cin_value = 0;
		}
		else return cin_value;
	
}
void Text::cin_check(short& cin_value, short range, std::vector <short> allowed_values)
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
			read_text(pl_OR_eng, 1, 1);
		}
		else if (language_version == "English") {
			read_text(pl_OR_eng, 2, 1);
			
		}
		std::cout << std::endl << std::endl << "                 ";
		system("pause");
		cin_value = -1;


	}

	

}





void Text::load_language_file(std::vector <std::string> &vector_name, std::string file_name , char delim) {

	std::string line;
	std::fstream file;
	
	std::string path;

	if (language_version == "Polish") {
		path = ".\\Polish\\";
		path.append(file_name);
	}
	else if (language_version == "English") {
		path = ".\\English\\";
		path.append(file_name);
	}
	else if (language_version == "") path = ".\\Select_language\\pl_OR_eng.txt";
		
		
	file.open(path, std::ios::in);


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

void Text::load_language_version()
{
	if (language_version == "") load_language_file(pl_OR_eng);
	else {
		load_language_file(start_menu, "start_menu_pl.txt");
		load_language_file(log_frames, "log_frames_pl.txt");
		load_language_file(log_message, "auction_log_message_pl.txt", '\n');
		load_language_file(A_4, "auction_four_cards_pl.txt");
		load_language_file(A_8, "auction_eight_cards_pl.txt");
		load_language_file(Warsow_txt, "game_warsow_pl.txt");
		load_language_file(game_log_message, "game_log_message_pl.txt", '\n');
		load_language_file(frames, "frames_pl.txt");
		load_language_file(auction_text, "auction_pl.txt");
	}
}



void Text::show_first_auction_menu(Player * player, short situation) {

	std::cout << Text::frames[1];
	Auction::read_auction_log(true);
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
	


	
void Text::show_game(Player* player, std::vector<short> what_may_I_throw_copy) {

	std::cout << frames[1];
	Auction::read_auction_log(false);
	std::cout << frames[0];
	std::cout << frames[2];
	Game::read_game_log();
	Game::read_trick_log();
	std::cout << frames[0];
	player->show(8, "GAME");
	player->show_me_what_I_can_throw(what_may_I_throw_copy);
	std::cout << frames[12];
}

