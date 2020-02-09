
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
			//if (file_name != "")
			//showing_txt(file_name);
			//cout << "\tTwoja wybor :";
			//cin >> cin_value;
			return cin_value = NULL;
		}
		else
		{
			return cin_value;
		}
	}
}

string start_menu = "", auct_1, auct_2 = "", auct_3 = "", auct_4 = "", meet_1 = "", meet_2 = "", meet_3;

void load_language_version(string language)
{
	fstream language_version;

	if (language == "POLISH") language_version.open("POLISH.txt", ios::in);
	else if (language == "ENGLISH")	language_version.open("ENGLISH.txt", ios::in);
	else {
		cout << "Blad podczas otwierania pakietu jezykowego\n\n";
		system("pause");
		exit(0);
	}
	if (language_version.good() == false)
	{
		cout << "Blad podczas otwierania skryptu." << endl << endl;
		exit(0);
	}
	
	string line;
	short line_counter = 1; 


	while (getline(language_version, line))
	{
		if (line_counter < 14) {
			if (start_menu == "") { start_menu = line; }
			else { start_menu = start_menu + "\n" + line; }
		}
		else if (line_counter > 13 && line_counter < 21) {
			if (auct_1 == "") { auct_1 = line; }
			else { auct_1 = auct_1 + "\n" + line; }
		}
		else if (line_counter == 21) {
			auct_2 = auct_1;
			auct_3 = auct_1;
			auct_1 = auct_1 + "\n" + line;
		}
		else if (line_counter > 21 && line_counter < 24) { auct_2 = auct_2 + "\n" + line; }
		else if (line_counter > 23 && line_counter < 26) { auct_3 = auct_3 + "\n" + line; }
		else if (line_counter == 26) { meet_1 = line; }
		else if (line_counter == 27) { meet_1 = meet_1 + "\n" + line; }
		else if (line_counter == 28) { meet_2 = line; }
		else if (line_counter == 29) { meet_3 = line; }
		line_counter++;
	}
		

	language_version.close();

	//cout << start_menu << endl << auct_1 << endl << auct_2 << endl << auct_3 << endl;
}
