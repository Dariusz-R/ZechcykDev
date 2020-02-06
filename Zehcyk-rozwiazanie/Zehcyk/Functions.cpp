
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

short cin_check(short& cin_value, string file_name)
{
	while (1)
	{

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Podany znak nie jest cyfra. Sprobuj ponownie" << endl;
			Sleep(1000);
			system("CLS");
			if (file_name != "NULL")
			showing_txt(file_name);
			cout << "\tTwoja wybor :";
			cin >> cin_value;
		}
		else
			break;

	}
	cout << endl << endl;
	return cin_value;
}

string game_name(short& which_game)
{
	switch (which_game)
	{
	case 1:
		return "czerwien";
		break;
	case 2:
		return "dzwonek";
		break;
	case 3:
		return "wino";
		break;
	case 4:
		return "zoladz";
		break;
	case 5:
		return "warszawa";
		break;
	case 6:
		return "kontra-warszawa";
		break;
	case 7:
		return "durh";
		break;
	case 8:
		return "mizerka";
		break;

	}
}

