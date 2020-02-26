#include "Text.h"
#include <iostream>
#include "Player.h"
#include <windows.h>
#include <vector>
//#include <stdlib.h>
//#include <sstream>
#include <string>
#include "Auction.h"
#include <iomanip>
#include "Game_Warsow.h"



// METHODS DIVIDED IN THREE PHASES:
// 1 - begining
// 2 - auction
// 3 - game

//INSIDE PHASES  METHODS ORDERED CHRONLOGICALLY


// USED IN PHASE 1:

Player::Player()
:SORT_LIKE_FOR_MISERY(9)
{
	std::string name = "";
	trick_points = 0; 
	game_points = 0;
	last_thrown_card_iterator = 8;
}

void Player::name_player(short text_line_number) {
	std::string name_to_pass = "";
	bool incorrect_name = true;
	do {
		Text::read_text(Text::start_menu, text_line_number, 1);
		std::getline(std::cin >> std::ws, name_to_pass, '\n');
		if (name_to_pass.size() < 15)
			incorrect_name = false;
		else {
			system("CLS");
			std::cout << std::endl;
			Text::read_text(Text::start_menu, 9, 1);
			std::cout << std::endl << std::endl << "                    ";
			system("Pause");
			system("CLS");
		}

	} while (incorrect_name == true);
	name.append(name_to_pass);
	name_shortcut.append(name_to_pass, 0, 2);
}

std::string Player::get_name() {
	return name;
}

void Player::take_card(const Card* card_to_take) {
	player_cards.push_back(card_to_take);
}

// USED IN PHASE 1 AND 2:

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
			std::cout << "BLAD SORTOWANIA" << std::endl << std::endl;
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
			std::cout << "BLAD2 PODCZAS SORTOWANIA" << std::endl << std::endl;
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
				std::swap(sort_value[j], sort_value[j + 1]);
				std::swap(player_cards[j], player_cards[j + 1]);
				swapped = true;
			}
		}
		if (swapped == false)
			break;
	}
}

// USED IN PHASE 2 AND 3:

void Player::show(short how_many, std::string when)
{

	std::cout << "\t\t\t\t\t\t\t\t*\r\t*";
	std::cout << std::setw(27 + name.size() / 2) << name << std::endl;
	std::cout << Text::frames[0] << Text::frames[5];
	std::cout << "\t\t\t\t\t\t\t\t*\r\t*     ";

	for (short i = 0; i < 8; i++) {
		if (i < how_many)
			std::cout << player_cards[i]->symbol << "  ";
		else std::cout << "      ";
	}
	std::cout << std::endl;
	
	 if (when == "GAME"){
		std::cout << "\t\t\t\t\t\t\t\t*\r\t*      ";
		for (short i = 0; i < 8; i++)
		{
			i < how_many ? std::cout << i + 1 << "     " : std::cout << "      ";
		}
		std::cout << std::endl;
	 }
	 std::cout << Text::frames[9];

}

void Player::throw_out_all_remain_cards() {
	player_cards.clear();
}

void Player::add_game_points(short points) {
	game_points += points;
}

short Player::get_game_points() {
	return game_points;
}

// USED IN PHASE 3:

Card const* Player::which_card_I_throw(std::vector<short> what_may_I_throw)
{
	if (player_cards.size() != 1)
	{

		do
		{
			last_thrown_card_iterator = 0;
			Text::show_game(this, what_may_I_throw);
			std::cin >> last_thrown_card_iterator;
			last_thrown_card_iterator--;
			Text::cin_check(last_thrown_card_iterator, player_cards.size(), what_may_I_throw);
			system("CLS");
		} while (last_thrown_card_iterator == -1);
		return player_cards[last_thrown_card_iterator];
	}
	else
	{
		show(player_cards.size(), "GAME");
		std::cout << "Ostatnia Twoja karta zostanie rzucona\n\n";
		system("PAUSE");
		return player_cards[0];
	}
}

void Player::show_me_what_I_can_throw(std::vector<short> what_may_I_throw)
{
	if (what_may_I_throw.empty()) {
		std::cout << Text::frames[7];
	}
	else {
		std::string what_may_I_throw_text_for_player = "";
		for (short i = 0; i < what_may_I_throw.size(); i++) {
			what_may_I_throw_text_for_player.append("   ");
			what_may_I_throw_text_for_player.append(std::to_string(what_may_I_throw[i]+1));
		}

		std::cout << Text::frames[8];
		std::cout << "\t\t\t\t\t\t\t\t*\r\t*";
		if (what_may_I_throw.size() % 2 == 1)
			std::cout << std::setw(27 + 4 * (what_may_I_throw.size() / 2)) << what_may_I_throw_text_for_player << std::endl;
		else {
			std::cout << std::setw(25 + 2 * what_may_I_throw.size()) << what_may_I_throw_text_for_player << std::endl;
		}
		std::cout << Text::frames[0];
	}
}

std::vector <short> Player::how_many_card_in_thrown_colour_i_have(short colour) {
	std::vector <short> iterators_of_cards_in_colour = {};
	for (short i = 0; i < player_cards.size(); i++) {
		if (player_cards[i]->colour == colour) {
			iterators_of_cards_in_colour.push_back(i);
		}
	}
	return iterators_of_cards_in_colour;
}

Card const* Player::share_card(short i) {
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
	std::cout << " CHcesz zameldowac?" << std::endl;
	std::cin >> yes_or_no;
	Text::cin_check(yes_or_no, 2);

	if (yes_or_no == 2)
		return false;
	if (yes_or_no == 1)
		return true;
}

void Player::add_trick_points(short points) {
	trick_points += points;
}

short Player::get_trick_points() {
	return trick_points;
}

std::string Player::get_name_shortcut() {
	return name_shortcut;
}

void Player::reset_trick_points() {
	trick_points = NULL;
}

void Player::erase_thrown_card()
{
	player_cards.erase(player_cards.begin() + last_thrown_card_iterator);
}





















