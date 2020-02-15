#include "Text.h"
#include <iostream>
#include <fstream>


using namespace std;
vector <string> Text::pl_OR_eng;
vector <string> Text::start_menu;
vector <string> Text::A_4;
vector <string> Text::A_8;
vector <string> Text::log_frame;
vector <string> Text::log_message;
string Text::language_version;

void Text::set_language_version(string lang) { language_version = lang; }


void Text::read_text(vector <string> what, short begin, short end) {
	if (end == 0) {
		end = what.size(); 
		for (short i = begin; i < end; i++)
			cout << what[i];
	}
	else if ((begin + end) <= what.size()) {
		for (short i = begin; i < (begin + end); i++)
			cout << what[i];
	}
	else cout << "Cos nie tak z czytaniem tekstu";
}

short Text::cin_check(short& cin_value , short range, bool first_menu)
{
	while (1)
	{
		if (cin.fail() || cin_value > range || cin_value < 1)
		{
			cin.clear();
			cin.ignore(100, '\n');
			system("CLS");
			if (first_menu == true) {
				read_text(pl_OR_eng, 1, 1);
				cout << endl;
				read_text(pl_OR_eng, 2, 1);
				cout << endl << endl << "                 ";
			}
			else{
				if (language_version == "Polish") {
					read_text(pl_OR_eng, 1, 1);
					cout << endl << endl << "                 ";
				}
				else if (language_version == "English") {
					read_text(pl_OR_eng, 2, 1);
					cout << endl << endl << "                 ";
				}
			}
			system("pause");
			system("CLS");
			return cin_value = NULL;
		}
		else return cin_value;
	}
}


void Text::load_language_file( vector <string> &vector_name, string file_name ) {

	string line;
	fstream file;
	
	string path;

	if (language_version == "Polish") {
		path = ".\\Polish\\";
		path.append(file_name);
	}
	else if (language_version == "English") {
		path = ".\\English\\";
		path.append(file_name);
	}
	else if (language_version == "") path = ".\\Select_language\\pl_OR_eng.txt";
		
		
	file.open(path, ios::in);


	if (file.good() == false)
	{
		cout << "Blad podczas otwierania skryptu." << endl << endl;
		exit(0);
	}
	while (getline(file, line, '#'))
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
		load_language_file(log_frame, "auction_log_frame_pl.txt");
		load_language_file(log_message, "auction_log_message_pl.txt");
		load_language_file(A_4, "auction_four_cards_pl.txt");
		load_language_file(A_8, "auction_eight_cards_pl.txt");
	}
}





	


	


