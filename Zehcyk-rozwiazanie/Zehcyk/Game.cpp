#include <iostream>
#include <string>
#include "Game.h"
#include "Text.h"

using namespace std;


void Game::player_throws_card_then_it_is_evaluated(short id_player) {
	if (id_player == player_with_initiative)
		thrown[player_with_initiative] = players_pointer[player_with_initiative]->which_card_I_throw();
	else
		thrown[id_player] = players_pointer[id_player]->which_card_I_throw(what_player_can_throw(id_player));

	game_log_actualization(id_player, 1);
	card_evaluation(thrown[id_player], values_of_thrown_cards[id_player]);
	system("CLS");
}




short Game::which_player_after_player_with_initiative(short which_after) {
	return ((player_with_initiative + which_after) % 3);
}



void Game::read_game_log(short situation) {

	switch (situation)
	{
	case 1:
		for (short i = 0; i < game_log.size(); i++) {
			cout << endl << game_log[i];
		}
		break;
	case 2:
		if (!game_log.empty())
		{
			if (game_log.size() == 1)
				cout << endl << game_log.end()[-1];
			else {
				cout << endl << game_log.end()[-2];
				cout << endl << game_log.end()[-1];
			}
		}
		break;
	}
	cout << endl;
}

void Game::card_evaluation(Card const* card_to_evaluate, short& conteiner) {

	switch (card_to_evaluate->symbol[2]) {
	case '9':
		conteiner = 0;
		break;
	case 'J':
		conteiner = 2;
		break;
	case 'D':
		conteiner = 3;
		break;
	case 'K':
		conteiner = 4;
		break;
	case '1':
		conteiner = 10;
		break;
	case 'A':
		conteiner = 11;
		break;
	default:
		cout << "BLEDNE CZYTANIE SYMBOLU PRZY EWALUACJI";
		break;
	}

}

void Game::remove_thrown_cards_from_players_hands() {
	for (short i = 0; i < NUMBER_OF_PLAYERS; i++)
		players_pointer[i]->erase_thrown_card();
}

vector<short> Game::what_player_can_throw(short id_player) {
	vector <short> values_of_the_player_cards_in_colour, player_cards_in_colour, player_cards_winning;
	player_cards_in_colour = players_pointer[id_player]->how_many_card_in_colour_i_have(thrown[player_with_initiative]->colour);
	if (!player_cards_in_colour.empty()) {

		for (short i = 0; i < player_cards_in_colour.size(); i++) {
			values_of_the_player_cards_in_colour.push_back(0);
			card_evaluation(players_pointer[id_player]->share_card(player_cards_in_colour[i]), values_of_the_player_cards_in_colour[i]);
			if (values_of_the_player_cards_in_colour[i] > values_of_thrown_cards[who_is_winning_trick]) {
				player_cards_winning.push_back(player_cards_in_colour[i]);
			}

		}
		if (!player_cards_winning.empty())
			return player_cards_winning;
		else
			return player_cards_in_colour;
	}
	else
		return {};


}




short Game::compare_two_cards(short id_player, short id2_player)
{
	if (thrown[id_player]->colour == thrown[id2_player]->colour) {

		if (values_of_thrown_cards[id_player] < values_of_thrown_cards[id2_player])
			return id2_player;
		else
			return id_player;

	}
	else
		return id_player;
}
