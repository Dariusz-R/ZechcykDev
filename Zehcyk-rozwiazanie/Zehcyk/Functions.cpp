
#include "Functions.h"

using namespace std;

//***************************************************************************************************************************************************************************
// SHOWING THE MENU FROM TEXT FILE

void showing_txt(string file_name)
{
	fstream menu1;
	menu1.open(file_name, ios::in);

	if (menu1.good() == false)
	{
		cout << "Blad podczas otwierania skryptu." << endl << endl;
		exit(0);
	}

	string line;

	while (getline(menu1, line))
	{
		cout << line << endl;
	}

	menu1.close();
}

//***************************************************************************************************************************************************************************
// CHECKS IF VALUE OF CIN HAS SAME TYPE AS IT WAS DEFINED. OTHERWISE FUNCTION ASKS ONCE AGAIN TO ENTER THE DATA
// CIN IGNORE NEED TO BE MORE SECURED.

short cin_check(short& cin_value, short range)
{
	while (1)
	{

		if (cin.fail() || cin_value > range || cin_value < 1)
		{
			cin.clear();
			cin.ignore(100, '\n');
			system("CLS");
			cout << "Wprowadzono bledne dane. Sprobuj jeszcze raz." << endl;
			system("pause");
			system("CLS");
			return cin_value = NULL;
		}
		else
		{
			return cin_value;
		}
	}
}

string start_menu = "";
string meet_1 = "", meet_2 = "", meet_3;
string intro_1 = "", intro_2 = "", intro_3 = "", intro_4;
string show_txt = "", your_choice = "";
string auct_1 = "", auct_2 = "", auct_3 = "", auct_4 = "";
string resp_1 = "", resp_2 = "", resp_3 = "", resp_4 = "";


void load_language_version(string language)
{
	fstream language_version;

	if (language == "POLISH") language_version.open("POLISH.txt", ios::in);
	else if (language == "ENGLISH")	language_version.open("ENGLISH.txt", ios::in);
	if (language_version.good() == false)
	{
		cout << "Blad podczas otwierania skryptu." << endl << endl;
		exit(0);
	}
	string line;
	short line_counter = 1; 

	while (getline(language_version, line))
	{
		if (line_counter < 15) {
			if (start_menu == "") { start_menu = line; }
			else { start_menu = start_menu + "\n" + line; }
		}
		else if (line_counter == 15) { meet_1 = line; }
		else if (line_counter == 16) { meet_1 = meet_1 + "\n" + line; }
		else if (line_counter == 17) { meet_2 = line; }
		else if (line_counter == 18) { meet_3 = line; }
		else if (line_counter == 19) { intro_1 = line; }
		else if (line_counter == 20) { intro_2 = line; }
		else if (line_counter == 21) { intro_3 = line; }
		else if (line_counter == 22) { intro_4 = line; }
		else if (line_counter == 23) { show_txt = line; }
		else if (line_counter > 23 && line_counter < 31) {
			if (auct_1 == "") { auct_1 = line; }
			else { auct_1 = auct_1 + "\n" + line; }
		}
		else if (line_counter == 31) {
			auct_2 = auct_1;
			auct_3 = auct_1;
			auct_1 = auct_1 + "\n" + line;
		}
		else if (line_counter > 31 && line_counter < 34) { auct_2 = auct_2 + "\n" + line; }
		else if (line_counter > 33 && line_counter < 36) { auct_3 = auct_3 + "\n" + line; }
		else if (line_counter == 36) { your_choice = line; }
		else if (line_counter == 37) { resp_1 = line; }
		else if (line_counter == 38) { resp_2 = line; }
		else if (line_counter == 39) { resp_3 = line; }
		else if (line_counter == 40) { resp_4 = line; }
		line_counter++;
	}
		

	language_version.close();

	//cout << start_menu << endl << auct_1 << endl << auct_2 << endl << auct_3 << endl;
}
