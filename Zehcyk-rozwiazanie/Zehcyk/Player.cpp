#include "Text.h"
#include <iostream>
#include "Player.h"
#include <windows.h>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <string>


using namespace std;

Player::Player() {
	string name = "";
	short player_number = 0;
	short trick_points = 0; 
	short game_points = 0;
}

void Player::set_name(string given_name) { 
	name = given_name; 
}
string Player::get_name() {
	return name;
}
void Player::throw_out_all_remain_cards(short how_many) {
	for (short i = 0; i < how_many; i++) {
		player_cards.pop_back();
	}
}

void Player::add_trick_points(short points) { 
	trick_points += points; 
}
short Player::get_trick_points(){ 
	return trick_points; 
}
void Player::reset_trick_points() { 
	trick_points = NULL; 
}

void Player::add_game_points(short points) { trick_points += points; }
short Player::get_game_points(){ return game_points; }

void Player::set_player_number(short number) { player_number = number; }
short Player::get_player_number(){ return player_number; }

//***************************************************************************************************************************************************************************
// ASKS FOR PLAYER NAME
// SUBFUNCTION FOR: Run::meet_players()

void Player::name_player(short number)
{
	player_number = number;
	cin >> name; 

}

//***************************************************************************************************************************************************************************
// SHOWS NAMES OF THE PLAYERS
// SUBFUNCTION FOR: Run::meet_players()



//***************************************************************************************************************************************************************************
// COPY CARD FROM DECK (card_to_take says which one from the deck)
// SUBFUNCTION FOR: Run::give_cards_to_players()

void Player::take_card(const Card* card_to_take)
{
	player_cards.push_back( card_to_take );
	//cout << " U playera" << player_cards.back() << endl;
	//system("pause");
}

//***************************************************************************************************************************************************************************
// SORT (BUBBLE SORT) CARDS IN PLAYERS HAND TO MAKE IT EASYER TO READ
// SUBFUNCTION FOR: Run::give_cards_to_players()

void Player::sort_cards(string situation)
{
	short how_many_cards = 4;
	short sort_value[8];
	if (situation == "FOUR_CARDS") { 
		how_many_cards = 4;
	}

	else if ( situation == "EIGHT_CARDS" || situation == "MISERY"){
		how_many_cards = 8; 
	}

	for (short i = 0; i < how_many_cards; i++) {
		switch (player_cards[i]->colour) {
		case 1:
			break;
		case 2:
			sort_value[i] += 20;
			break;
		case 3:
			sort_value[i] += 40;
			break;
		case 4:
			sort_value[i] += 60;
			break;
		default:
			cout << "BLAD SORTOWANIA" << endl << endl;
			break;
		}
		switch (player_cards[i]->symbol[2]) {
		case '9':
			break;
		case 'J':
			sort_value[i] += 2;
			break;
		case 'D':
			sort_value[i] += 3;
			break;
		case 'K':
			sort_value[i] += 4;
			break;
		case '1':
			if (situation == "MISERY") sort_value[i] += 1;
			else sort_value[i] += 10;
			break;
		case 'A':
			sort_value[i] += 11;
			break;
		default:
			cout << "BLAD2 PODCZAS SORTOWANIA" << endl << endl;
			break;
		}
	}

	bool swapped;

	for (short i = 0; i < how_many_cards - 1; i++)
	{
		swapped = false;
		for (short j = 0; j < how_many_cards - i - 1; j++)
		{
			if (sort_value[j] > sort_value[j + 1])
			{
				swap(sort_value[j], sort_value[j + 1]);
				swap(player_cards[j], player_cards[j + 1]);
				swapped = true;
			}
		}
		if (swapped == false)
			break;
	}
}


void Player::show(short how_many, string when)
{
	
	Text::read_text(Text::A_4, 0, 1);
	short letters_per_side = 0;
	if (name.size() % 2 == 1) {
		letters_per_side = (name.size() - 1) / 2;
		Text::placing_text_in_center_of_the_frame(name, letters_per_side);
	} else if (name.size() % 2 == 0){
		letters_per_side = name.size() / 2;
		Text::placing_text_in_center_of_the_frame(name, letters_per_side, "EVEN");
	}
	Text::read_text(Text::A_4, 1, 1);
	for (short i = 0; i < 8; i++) {
		if (i < how_many) 
			cout << player_cards[i]->symbol << "  ";
		else cout << "      ";
	}
		
	Text::read_text(Text::A_4, 2, 1);
	if (when == "AUCTION") {
		Text::read_text(Text::A_4, 5, 1);
	}

	else if (when == "GAME")
	{
		Text::read_text(Text::A_4, 3, 1);
		for (short i = 0; i < 8; i++)
		{
			if (i < how_many) cout << i + 1 << "     ";
			else cout << "      ";
			
		}
		Text::read_text(Text::A_4,4 , 2);
	}
	
	
}

//***************************************************************************************************************************************************************************
// ASKS PLAYER IF HE WANT TO PICK A COLUR OR DECLARE "WARSAW"
// SUBFUNCTION FOR:



//***************************************************************************************************************************************************************************
// ASKS PLAYER WHO PICKED A COLOUR IF HE WANT TO PLAY OR RESIGN
// SUBFUNCTION FOR:



//***************************************************************************************************************************************************************************
// ASKS PLAYER WHAT ANSWER WILL HE GIVE TO THE PLAYER WHO PICK A COLOUR
// SUBFUNCTION FOR:

/*
short Player::other_player_asked(short *game_type, short &contra_counter2)
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
		if(*game_type != 8) cout << "\n3. Durha!";
		if(*game_type != 7 && *game_type != 8) cout << "\n4. Mizerka!";

		cout << "\n\nTwoj wybor : ";
		
		cin >> decision;
		if (*game_type == 8 && (decision == 3 || decision == 4)) decision = 5;
		else if (*game_type == 7 && decision == 4) decision = 5;

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
			*game_type = 8;
			return 8;

		case 4:

			system("CLS");
			cout << "MIZERKA!\n\n";
			contra_reset();
			system("pause");
			system("CLS");
			*game_type = 7;

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

vector<short> Player::which_card_you_may_throw(Card &first, short trumph)
{
	vector <short> kill, be_killed, kill_with_trumph;
	
	for (int i = 0; i < player_cards.size(); i++)
	{
		if (first.colour == player_cards[i].colour)
		{
			if (first.value < player_cards[i].value)
				kill.push_back(i + 1);
			else
				be_killed.push_back(i + 1);
		}
		else if (first.colour != trumph && player_cards[i].colour == trumph)
			kill_with_trumph.push_back(i + 1);
	}
	if (kill.empty() == true)
	{
		if (kill_with_trumph.empty() == false)
		{
			return kill_with_trumph;
		}
		else if (be_killed.empty() == false)
			return be_killed;
		else
			return {};
	}
	else
		return kill;
}


Card Player::which_card_you_throw( short player, short trumph)
{
	if (player_cards.size() != 1)
	{
		bool correct = true;
		do
		{
			choice = NULL;
			switch (trumph)
			{
			case 1:
				cout << "Tromfem jest czerwien.\n";
				break;
			case 2:
				cout << "Tromfem jest dzwonek.\n";
				break;
			case 3:
				cout << "Tromfem jest wino.\n";
				break;
			case 4:
				cout << "Tromfem jest zoladz.\n";
				break;
			}
			show(player_cards.size(), 2);
			cout << "Ktora, karte chcesz rzucic?\n\nTwoj wybor: ";
			cin >> choice;
			Text::cin_check(choice,player_cards.size());

			if (choice > player_cards.size() || choice < 1)
			{
				correct = false;
				system("CLS");
				cout << "Wybrales numer, ktory nie reprezentuaje zadnej z kart. Sprobuj ponownie.\n\n";
				system("Pause");
			}
			else
				correct = true;

		} while (correct == false);
		choice--;
		return player_cards[choice];
	}
	else
	{
		show(player_cards.size(), NULL);
		cout << "Ostatnia Twoja karta zostanie rzucona\n\n";
		system("PAUSE");
		return player_cards[0];
	}
	}

Card Player::which_card_you_throw( short player, Card &first, string who_started_trick, short trumph)
{
	vector <short> may_throw = { NULL };
	if (player_cards.size() != 1)
	{
		bool correct = false;
		do {
			cout << "Rozpoczal " << who_started_trick <<". Rzucono: " << first.symbol << endl << endl;
			choice = NULL; switch (trumph)
			{
			case 1:
				cout << "Tromfem jest czerwien.\n";
				break;
			case 2:
				cout << "Tromfem jest dzwonek.\n";
				break;
			case 3:
				cout << "Tromfem jest wino.\n";
				break;
			case 4:
				cout << "Tromfem jest zoladz.\n";
				break;
			}
			show(player_cards.size(), 2);
			may_throw = which_card_you_may_throw(first, trumph);
			if (may_throw.empty() == false)
			{
				cout << "\nMozesz rzucic nr :\t";
				for (int i = 0; i < may_throw.size(); i++)
					cout << may_throw[i] << "  ";
				cout << endl << endl;
				cout << "Ktora, karte chcesz rzucic?\n\nTwoj wybor: ";
				cin >> choice;
				cin_check(choice, player_cards.size());

				if (choice > player_cards.size() || choice < 1)
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
						if (choice == may_throw[i])
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
				cin >> choice;
				Text::cin_check(choice, player_cards.size());

				if (choice > player_cards.size() || choice < 1)
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
		choice--;
		return player_cards[choice];
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

Card Player::which_card_you_throw (short player, Card &first, Card &second, string who_started_trick, short trumph)
{
	vector <short> may_throw = { NULL };
	if (player_cards.size() != 1)
	{
		bool correct = false;
		do {
			cout << "Rozpoczal " << who_started_trick << ". Rzucono: " << first.symbol << "\t" << second.symbol << endl << endl;
			choice = NULL;
			switch (trumph)
			{
			case 1:
				cout << "Tromfem jest czerwien.\n";
				break;
			case 2:
				cout << "Tromfem jest dzwonek.\n";
				break;
			case 3:
				cout << "Tromfem jest wino.\n";
				break;
			case 4:
				cout << "Tromfem jest zoladz.\n";
				break;
			}
			show(player_cards.size(), 2);
			Card to_fight = compare_two(first, second);
			may_throw = which_card_you_may_throw(to_fight, trumph);
			if (may_throw.empty() == false )
			{
				cout << "\nMozesz rzucic nr:\t";
				for (int i = 0; i < may_throw.size(); i++)
					cout << may_throw[i] << "  ";
				cout << endl << endl;
				cout << "Ktora, karte chcesz rzucic?\n\nTwoj wybor: ";
				cin >> choice;
				cin_check(choice, player_cards.size());

				if (choice > player_cards.size() || choice < 1)
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
						if (choice == may_throw[i])
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
				cin >> choice;
				Text::cin_check(choice, player_cards.size());

				if (choice > player_cards.size() || choice < 1)
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
		choice--;
		return player_cards[choice];
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

void Player::destroy_thrown_card()
{
	player_cards.erase(player_cards.begin() + (choice));
}*/
