#include <iostream>
#include "Auction.h"


using namespace std;

void Auction::increase_auction_counter() { auction_counter++; }
void Auction::reset_auction_counter() { auction_counter = NULL;  }


short Auction::player_first_auction()
{
	int option = 20;
	bool decision = false;

	players.show(4, NULL);
	cout << name;
	switch (warsow)
	{
	case NULL:
		showing_txt("PICK1.txt");
		break;
	case 1:
		showing_txt("PICK2.txt");
		break;
	case 2:
		showing_txt("PICK3.txt");
		break;
	default:
		cout << "Blad w switchu w player.cpp" << endl;
	}

	do
	{
		cout << "\n\nTwoj wybor : ";
		cin >> option;
		switch (option)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			decision = true;
			break;
		default:
			cout << "\nWybrales opcje spoza zakresu. Sprobuj ponownie" << endl;
		}
	} while (decision == false);
	system("CLS");
	return option;

}





void Auction::first_auction()
{






}