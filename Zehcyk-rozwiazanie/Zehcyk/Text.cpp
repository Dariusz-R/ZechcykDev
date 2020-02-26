#include "Text.h"
#include <iostream>
#include <fstream>
#include <sstream>


std::vector <std::string> Text::pl_OR_eng;
std::vector <std::string> Text::start_menu;
std::vector <std::string> Text::A_4;
std::vector <std::string> Text::A_8;
std::vector <std::string> Text::Warsow_txt;
std::vector <std::string> Text::log_frames;
std::vector <std::string> Text::log_message;
std::vector <std::string> Text::game_log_message;
std::string Text::language_version;

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
	}
}


void Text::placing_text_in_center_of_the_frame(std::string &name_of_the_player, short &letters_per_side, std::string word) {
	
	short one_if_even = 0;
	if (word == "EVEN")
		one_if_even = 1;

	for (short i = 0; i < 27 - letters_per_side; i++) {
		std::cout << " ";
	}
	std::cout << name_of_the_player;
	for (short i = 0; i < 27 + one_if_even - letters_per_side; i++) {
		std::cout << " ";
	}
}



	


	


