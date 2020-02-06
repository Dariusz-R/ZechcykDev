#include <iostream>
#include "Player.h"
#include <windows.h>
#include "Functions.h"
#include <vector>





using namespace std;


//***************************************************************************************************************************************************************************
// ASKS FOR PLAYER NAME
// SUBFUNCTION FOR: Run::meet_players()

void Player::name_players(short number)
{
	player_number = number - 1;
	cout << "Podaj nazwe gracza numer " << number << endl;
	cin >> name;

}

//***************************************************************************************************************************************************************************
// SHOWS NAMES OF THE PLAYERS
// SUBFUNCTION FOR: Run::meet_players()

void Player::who_plays(short number)
{
	if (number == 1)
	{
		system("CLS");
		cout << "Dzis zagraja : ";
	}
		

	switch (number)
	{

	case 1:
		cout << name << ", ";
		break;

	case 2:
		cout << name << " i ";
		break;

	case 3:
		cout << name << endl;
		break;

	default:
		cout << " Wystapil blad " << endl;
	}


}

//***************************************************************************************************************************************************************************
// COPY CARD FROM DECK (card_to_take says which one from the deck)
// SUBFUNCTION FOR: Run::give_cards_to_players()

void Player::take_card(Card card_to_take)
{
	player_cards.push_back(card_to_take);
}

//***************************************************************************************************************************************************************************
// SORT (BUBBLE SORT) CARDS IN PLAYERS HAND TO MAKE IT EASYER TO READ
// SUBFUNCTION FOR: Run::give_cards_to_players()

void Player::sort_cards()
{
	for (short i = 0; i < 8; i++)
		for (short j = 1; j < 8 - i; j++)
			if (player_cards[j - 1].sort_value > player_cards[j].sort_value)
				swap(player_cards[j - 1], player_cards[j]);
}
//***************************************************************************************************************************************************************************
// SHOW PLAYER CARDS FROM HIS HAND
// SUBFUNCTION FOR:


void Player::show(short how_many, short when)
{
	cout << name << " to Twoje karty: \n\n";
	for (int i = 0; i < how_many; i++)
	{
		cout << player_cards[i].symbol << "\t";
		
		
	}
	if (when == 2)
	{
		cout << endl;
		for (int i = 0; i < how_many; i++)
		{
			cout << i+1 << "\t";


		}
	}
	cout << endl << endl;
}

//***************************************************************************************************************************************************************************
// ASKS PLAYER IF HE WANT TO PICK A COLUR OR DECLARE "WARSAW"
// SUBFUNCTION FOR:


int Player::choice_game_type(short &warsow)
{
	int option = 20;
	bool decision = false;

	show(4, NULL);
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

//***************************************************************************************************************************************************************************
// ASKS PLAYER WHO PICKED A COLOUR IF HE WANT TO PLAY OR RESIGN
// SUBFUNCTION FOR:

bool Player::ask_or_not()
{
    short decision = 3 ;

    do
    {
        show(8,NULL) ;
        cout << endl << "\nPytasz sie, czy rezygnujesz? \n\n1. PYTAM SIE!\n2. REZYGNUJE.\n\nTwoj wybor : " ;
        cin >> decision ;
        system("CLS");
        switch (decision)
        {
        case 1 :
            
            cout << name <<" - PYTAM SIE!" ;
            Sleep(1000);
            system("CLS");
            return true ;
            break ;

        case 2 :

            cout << name <<" - Rzuciles kartami." ;
            return false ;
            break ;

        default:
            cout << "Do wyboru masz opcje 1 lub 2. Wybrano opcje spoza zakresu. Jeszcze raz!" ;
            Sleep(1000) ;
            system("CLS") ;
            break ;
        }
    }while ( decision != 1 && decision != 2 ) ;

}

//***************************************************************************************************************************************************************************
// ASKS PLAYER WHAT ANSWER WILL HE GIVE TO THE PLAYER WHO PICK A COLOUR
// SUBFUNCTION FOR:


short Player::other_player_asked(short &which_game, short &contra_counter2)
{
	string answer;
	short decision = NULL;
	do
	{
		
		show(8, NULL);
		cout << name << " - Co mowisz Ty?\n1. Graj.\n";
		if (contra_counter2 == 0) cout << "2. Kontra!";
		else if (contra_counter2 == 1)
		{
			cout << "2. Rekontra!";
			answer = "Rekontra!";
		}
		else if (contra_counter2 == 2)
		{
			cout << "2. Slupa!";
			answer = "Slupa!";
		}
		else if (contra_counter2 == 3)
		{
			cout << "2. Mord!";
			answer = "Mord!";
		}
		else if (contra_counter2 == 4)
		{
			cout << "2. Supermord!";
			answer = "Supermord!";
		}
		else cout << "Blad";
		if(which_game != 8) cout << "\n3. Durha!";
		if(which_game != 7 && which_game != 8) cout << "\n4. Mizerka!";

		cout << "\n\nTwoj wybor : ";
		
		cin >> decision;
		if (which_game == 8 && (decision == 3 || decision == 4)) decision = 5;
		else if (which_game == 7 && decision == 4) decision = 5;

		system("CLS");
		switch (decision)

		{
		case 1:

			cout << name << "Gramy";
			Sleep(1000);
			system("CLS");
			return 1;
			break;

		case 2:
			contra();
			system("CLS");
			cout << answer << endl << endl;
			system("pause");
			system("CLS");
			return 2;
			break;
		case 3:
			system("CLS");
			cout << "DURH!\n\n";
			contra_reset();
			system("pause");
			system("CLS");
			which_game = 8;
			return 8;

		case 4:

			system("CLS");
			cout << "MIZERKA!\n\n";
			contra_reset();
			system("pause");
			system("CLS");
			which_game = 7;

			return 7;
			break;

		default:
			cout << "Wybierz opcje z podanego zakresu. Jeszcze raz!";
			Sleep(1000);
			system("CLS");
			break;
		}
	} while (decision != 1 && decision != 2 && decision != 3 && decision != 4);
}

Card Player::compare_two(Card& first_comp, Card& second_comp)
{
	if (first_comp.colour == second_comp.colour)
	{
		return((first_comp.value > second_comp.value) ? first_comp : second_comp);
	}
	else return first_comp; 
}

vector<short> Player::which_card_you_may_throw(Card &first)
{
	vector <short> kill, be_killed;
	for (int i = 0; i < player_cards.size(); i++)
	{
		if (first.colour == player_cards[i].colour)
		{
			if (first.value < player_cards[i].value)
				kill.push_back(i+1);
			else
				be_killed.push_back(i+1);
		}
	}
	if (kill.empty() == true)
	{
		if (be_killed.empty() == true)
			return {};
		else
			return be_killed;
	}
	else
		return kill;
}


Card Player::which_card_you_throw(short choice_f[], short player)
{
	if (player_cards.size() != 1)
	{
		bool correct = true;
		do
		{
			choice_f[player] = NULL;
			show(player_cards.size(), 2);
			cout << "Ktora, karte chcesz rzucic?\n\nTwoj wybor: ";
			cin >> choice_f[player];
			cin_check(choice_f[player], "NULL");

			if (choice_f[player] > player_cards.size() || choice_f[player] < 1)
			{
				correct = false;
				system("CLS");
				cout << "Wybrales numer, ktory nie reprezentuaje zadnej z kart. Sprobuj ponownie.\n\n";
				system("Pause");
			}
			else
				correct = true;

		} while (correct == false);
		(choice_f[player])--;
		return player_cards[choice_f[player]];
	}
	else
	{
		show(player_cards.size(), NULL);
		cout << "Ostatnia Twoja karta zostanie rzucona\n\n";
		system("PAUSE");
		return player_cards[0];
	}
	}

Card Player::which_card_you_throw(short choice_f[], short player, Card &first, string& who_started_trick)
{
	vector <short> may_throw = { NULL };
	if (player_cards.size() != 1)
	{
		bool correct = false;
		do {
			cout << "Rozpoczal " << who_started_trick <<". Rzucono: " << first.symbol << endl << endl;
			choice_f[player] = NULL;
			show(player_cards.size(), 2);
			may_throw = which_card_you_may_throw(first);
			if (may_throw.empty() == false)
			{
				cout << "\nMozesz rzucic nr :\t";
				for (int i = 0; i < may_throw.size(); i++)
					cout << may_throw[i] << "  ";
				cout << endl << endl;
				cout << "Ktora, karte chcesz rzucic?\n\nTwoj wybor: ";
				cin >> choice_f[player];
				cin_check(choice_f[player], "NULL");

				if (choice_f[player] > player_cards.size() || choice_f[player] < 1)
				{
					correct = false;
					system("CLS");
					cout << "Wybrales numer, ktory nie reprezentuaje zadnej z kart. Sprobuj ponownie.\n\n";
					system("Pause");
					system("CLS");
				}
				else
				{
					bool throw_correct = false;
					for (int i = 0; i < may_throw.size(); i++)
					{
						if (choice_f[player] == may_throw[i])
						{
							correct = true;
							throw_correct = true;
						}
					}
					if (throw_correct == false)
					{
						system("CLS");
						cout << "Nie mozesz rzucic tej karty" << endl;
						system("Pause");
						system("CLS");
						correct = false;
					}

					
				}
			}
			else
			{
				cout << "Ktora, karte chcesz rzucic?\n\nTwoj wybor: ";
				cin >> choice_f[player];
				cin_check(choice_f[player], "NULL");

				if (choice_f[player] > player_cards.size() || choice_f[player] < 1)
				{
					correct = false;
					system("CLS");
					cout << "Wybrales numer, ktory nie reprezentuaje zadnej z kart. Sprobuj ponownie.\n\n";
					system("Pause");
					system("CLS");
				}
				else
					correct = true;
			}
		} while (correct == false);
		(choice_f[player])--;
		return player_cards[choice_f[player]];
	}
	else
	{
		cout << "Rozpoczal " << who_started_trick << ". Rzucono: " << first.symbol << endl << endl;
		show(player_cards.size(), NULL);
		cout << "Ostatnia Twoja karta zostanie rzucona\n\n";
		system("PAUSE");
		return player_cards[0];
	}
}

Card Player::which_card_you_throw(short choice_f[], short player, Card &first, Card &second, string &who_started_trick)
{
	vector <short> may_throw = { NULL };
	if (player_cards.size() != 1)
	{
		bool correct = false;
		do {
			cout << "Rozpoczal " << who_started_trick << ". Rzucono: " << first.symbol << "\t" << second.symbol << endl << endl;
			choice_f[player] = NULL;
			show(player_cards.size(), 2);
			Card to_fight = compare_two(first, second);
			may_throw = which_card_you_may_throw(to_fight);
			if (may_throw.empty() == false )
			{
				cout << "\nMozesz rzucic nr:\t";
				for (int i = 0; i < may_throw.size(); i++)
					cout << may_throw[i] << "  ";
				cout << endl << endl;
				cout << "Ktora, karte chcesz rzucic?\n\nTwoj wybor: ";
				cin >> choice_f[player];
				cin_check(choice_f[player], "NULL");

				if (choice_f[player] > player_cards.size() || choice_f[player] < 1)
				{
					correct = false;
					system("CLS");
					cout << "Wybrales numer, ktory nie reprezentuaje zadnej z kart. Sprobuj ponownie.\n\n";
					system("Pause");
					system("CLS");
				}
				else
				{
					bool throw_correct = false;
					for (int i = 0; i < may_throw.size(); i++)
					{
						if (choice_f[player] == may_throw[i])
						{
							correct = true;
							throw_correct = true;
						}
					}
					if (throw_correct == false)
					{
						system("CLS");
						cout << "Nie mozesz rzucic tej karty" << endl;
						system("Pause");
						system("CLS");
						correct = false;
					}
				}
			}
			else
			{
				cout << "Ktora, karte chcesz rzucic?\n\nTwoj wybor: ";
				cin >> choice_f[player];
				cin_check(choice_f[player], "NULL");

				if (choice_f[player] > player_cards.size() || choice_f[player] < 1)
				{
					correct = false;
					system("CLS");
					cout << "Wybrales numer, ktory nie reprezentuaje zadnej z kart. Sprobuj ponownie.\n\n";
					system("Pause");
					system("CLS");
				}
				else
					correct = true;
			}
		} while (correct == false);
		(choice_f[player])--;
		return player_cards[choice_f[player]];
	}
	else
	{
		cout << "Rozpoczal " << who_started_trick << ". Rzucono: " << first.symbol << "\t" << second.symbol << endl << endl;
		show(player_cards.size(), NULL);
		cout << "Ostatnia Twoja karta zostanie rzucona\n\n";
		system("PAUSE");
		return player_cards[0];
	}
}

void Player::destroy_thrown_card(short choice_f2[], short player_des)
{
	player_cards.erase(player_cards.begin() + (choice_f2[player_des]));
}
