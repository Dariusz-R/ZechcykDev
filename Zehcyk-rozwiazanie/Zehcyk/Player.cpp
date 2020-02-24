#include "Text.h"
#include <iostream>
#include "Player.h"
#include <windows.h>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <string>
#include "Auction.h"
#include <iomanip>
#include "Game_Warsow.h"

using namespace std;

Player::Player()
:SORT_LIKE_FOR_MISERY(9)
{
	string name = "";
	trick_points = 0; 
	game_points = 0;
	last_thrown_card_iterator = 8;
}



void Player::name_player(short text_line_number) {
	string name_to_pass = "";
	bool incorrect_name = true;
	do {
		Text::read_text(Text::start_menu, text_line_number, 1);
		getline(cin >> ws, name_to_pass, '\n');
		if (name_to_pass.size() < 15)
			incorrect_name = false;
		else {
			system("CLS");
			cout << endl;
			Text::read_text(Text::start_menu, 9, 1);
			cout << endl << endl << "                    ";
			system("Pause");
			system("CLS");
		}

	} while (incorrect_name == true);
	name = name_to_pass;
}



string Player::get_name() {
	return name;
}



void Player::take_card(const Card* card_to_take) {
	player_cards.push_back(card_to_take);
}



void Player::sort_cards(short how_many_cards)
{
	short sort_value[8] = {0,0,0,0,0,0,0,0};
	bool misery = false;

	if ( how_many_cards == SORT_LIKE_FOR_MISERY) {
		how_many_cards = 8;
		misery = true;
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
			if (misery == true) sort_value[i] += 1;
			else sort_value[i] += 5;
			break;
		case 'A':
			sort_value[i] += 6;
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
	}
	else if (name.size() % 2 == 0) {
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

	} else if (when == "GAME"){
		Text::read_text(Text::A_4, 3, 1);
		for (short i = 0; i < 8; i++)
		{
			if (i < how_many) cout << i + 1 << "     ";
			else cout << "      ";

		}
		Text::read_text(Text::A_4, 4, 2);
		cout << endl;

	}


}



void Player::throw_out_all_remain_cards() {
	player_cards.clear();
}



void Player::add_game_points(short points) {
	trick_points += points; 
}



short Player::get_game_points(){ 
	return game_points; 
}



void Player::add_trick_points(short points) {
	trick_points += points;
}



short Player::get_trick_points() {
	return trick_points;
}



void Player::reset_trick_points() {
	trick_points = NULL;
}


vector <short> Player::how_many_card_in_colour_i_have(short colour) {
	vector <short> iterators_of_cards_in_colour = {};
	for (short i = 0; i < player_cards.size(); i++) {
		if (player_cards[i]->colour == colour) {
			iterators_of_cards_in_colour.push_back(i);
		}
	}
	return iterators_of_cards_in_colour;
}


 Card const * Player::share_card(short i) {
	 return player_cards[i];
}




 bool Player::do_I_have_queen_and_king_in_one_colour() {
	 if (player_cards[last_thrown_card_iterator]->symbol[2] == 'D' && (last_thrown_card_iterator + 1) < player_cards.size()) {
		 if (player_cards[last_thrown_card_iterator + 1]->symbol[2] == 'K' && player_cards[last_thrown_card_iterator]->colour == player_cards[last_thrown_card_iterator + 1]->colour)
			 return true;
	 }
	 else if (player_cards[last_thrown_card_iterator]->symbol[2] == 'K' && (last_thrown_card_iterator - 1) > 0) {
		 if (player_cards[last_thrown_card_iterator - 1]->symbol[2] == 'D' && player_cards[last_thrown_card_iterator]->colour == player_cards[last_thrown_card_iterator - 1]->colour)
			 return true;
	 }
	 return false;
 }

 bool Player::do_I_want_to_meld() {

	 system("CLS");
	 short yes_or_no = 3;
	 cout << " CHcesz zameldowac?" << endl;
	 cin >> yes_or_no;
	 Text::cin_check(yes_or_no, 2);

	 if (yes_or_no == 2)
		 return false;
	 if (yes_or_no == 1)
		 return true;
 }

Card const * Player::which_card_I_throw(vector<short> what_may_I_throw)
{
	if (player_cards.size() != 1)
	{	
		
		do
		{
			last_thrown_card_iterator = 0;
			Text::read_text(Text::log_frames, 0, 1);
			Auction::read_auction_log(false);
			Text::read_text(Text::log_frames, 1, 1);
			Game_Warsow::read_game_log(2);
			show(player_cards.size(), "GAME");
			show_me_what_I_can_throw(what_may_I_throw);
			Text::read_text(Text::Warsow_txt, 0, 1);
			cin >> last_thrown_card_iterator;
			last_thrown_card_iterator--;
			Text::cin_check(last_thrown_card_iterator, player_cards.size(), what_may_I_throw);
			system("CLS");
		} while (last_thrown_card_iterator == -1);
		return player_cards[last_thrown_card_iterator];
	}
	else
	{
		show(player_cards.size(), "GAME");
		cout << "Ostatnia Twoja karta zostanie rzucona\n\n";
		system("PAUSE");
		return player_cards[0];
	}
	}


void Player::show_me_what_I_can_throw(vector<short> what_may_I_throw)
{
	if (what_may_I_throw.empty()) {
		Text::read_text(Text::log_frames, 3, 1);
	}
	else {
		string information_for_me = "";
		Text::read_text(Text::log_frames, 2, 1);
		cout << setw(9) << "*";

		if (what_may_I_throw.size() == 1) {
			cout << setw(28) << what_may_I_throw[0] + 1 << setw(28) << "*" << endl;
		}
		else if ((what_may_I_throw.size() % 2) == 1) {
			for (short i = 0; i < what_may_I_throw.size(); i++) {
				string number = to_string(what_may_I_throw[i] + 1);
				information_for_me.append("   ");
				information_for_me.append(number);
			}
			short how_many_signes_from_center = 4 * (what_may_I_throw.size() - 1) / 2;
			cout << setw(28 + how_many_signes_from_center) << information_for_me << setw(28 - how_many_signes_from_center) << "*" << endl;
		}
		else if ((what_may_I_throw.size() % 2) == 0) {
			for (short i = 0; i < what_may_I_throw.size(); i++) {
				string number = to_string(what_may_I_throw[i] + 1);
				information_for_me.append("   ");
				information_for_me.append(number);
			}
			short how_many_signes_from_center = 4 * what_may_I_throw.size() / 2 - 2;
			cout << setw(28 + how_many_signes_from_center) << information_for_me << setw(28 - how_many_signes_from_center) << "*" << endl;
		}
		Text::read_text(Text::log_frames, 4, 1);
	}
}





void Player::erase_thrown_card()
{
	player_cards.erase(player_cards.begin() + last_thrown_card_iterator);
}
