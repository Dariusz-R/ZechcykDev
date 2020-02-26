#include <iostream>
#include <string>
#include "Game.h"
#include "Text.h"



short Game::important_player;
short Game::game_points_multiplier;

void Game::set_important_player(short which_player) {
	important_player = which_player;
}
void Game::set_game_points_multiplier(short which_player) {
	important_player = which_player;
}
short Game::get_important_player() {
	return important_player;
}
short & Game::get_important_player_adress() {
	return important_player;
}
short Game::get_game_points_multiplier() {
	return game_points_multiplier;
}
// PUBLIC METHODS ORDERED CHRONOLOGICALLY:

void Game::read_game_log(short situation) {

	switch (situation)
	{
	case 1:
		for (short i = 0; i < game_log.size(); i++) {
			std::cout << std::endl << game_log[i];
			break;
		}
	case 2:
		if (!game_log.empty())
		{
			if (game_log.size() == 1)
				std::cout << std::endl << game_log.end()[-1];
			else {
				std::cout << std::endl << game_log.end()[-2];
				std::cout << std::endl << game_log.end()[-1];
			}
		}
		break;
	}
	std::cout << std::endl;

}

void Game::play_game() {
	for (int i = 0; i < NUMBER_OF_CARDS_IN_PLAYER_HAND_BEFORE_THROWING; i++) {
		 player_who_won_the_trick = play_trick();
		if (checking_the_condition_which_depends_from_gametype(i) == false)
			break;
	}
	distribute_game_points();
	clear_players_hands();
	show_info_about_game();
}

// PROTECTED METHODS ORDERED CHRONOLOGICALLY:

short Game::play_trick()
{
	who_is_winning_trick = ANY_OF_PLAYERS;
	thrown[0] = {};
	thrown[1] = {};
	thrown[2] = {};


	player_throws_card_then_it_is_evaluated(throwing_player);
	who_is_winning_trick = throwing_player;
	player_throws_card_then_it_is_evaluated(which_player(1));
	who_is_winning_trick = compare_two_cards(throwing_player, which_player(1));
	player_throws_card_then_it_is_evaluated(which_player(2));
	who_is_winning_trick = compare_two_cards(who_is_winning_trick, which_player(2));

	sum_up_and_give_trick_points_to_player_who_won_trick();
	
	game_log_update(who_is_winning_trick, 2);
	remove_thrown_cards_from_players_hands();
	throwing_player = who_is_winning_trick;

	return who_is_winning_trick;
}

short Game::which_player (short which_after_player_with_initiative) {
	return ((throwing_player + which_after_player_with_initiative) % 3);
}

void Game::player_throws_card_then_it_is_evaluated(short id_player) {
	if (id_player == throwing_player)
		thrown[throwing_player] = players_pointer[throwing_player]->which_card_I_throw();
	else
		thrown[id_player] = players_pointer[id_player]->which_card_I_throw(what_player_can_throw(id_player));

	game_log_update(id_player, 1);
	card_evaluation(thrown[id_player], values_of_thrown_cards[id_player]);
	system("CLS");
}

std::vector<short> Game::what_player_can_throw(short id_player) {
	std::vector <short> values_of_the_player_cards_in_colour, player_cards_in_colour, player_cards_winning;
	player_cards_in_colour = players_pointer[id_player]->how_many_card_in_thrown_colour_i_have(thrown[throwing_player]->colour);
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
		std::cout << "BLEDNE CZYTANIE SYMBOLU PRZY EWALUACJI";
		break;
	}

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

void Game::sum_up_and_give_trick_points_to_player_who_won_trick() {
	;
}

void Game::remove_thrown_cards_from_players_hands() {
	for (short i = 0; i < NUMBER_OF_PLAYERS; i++)
		players_pointer[i]->erase_thrown_card();
}

void Game::distribute_game_points() {
	if (variable_replaced_by_reference == true)
		players_pointer[important_player]->add_game_points(basic_stake * 2 ^ (game_points_multiplier - 1));
	else {
		players_pointer[(important_player + 1) %3]->add_game_points(basic_stake * 2 ^ (game_points_multiplier - 1));
		players_pointer[(important_player + 2) %3]->add_game_points(basic_stake * 2 ^ (game_points_multiplier - 1));
	}
}

void Game::clear_players_hands() {
	for (short i = 0; i < NUMBER_OF_PLAYERS; i++)
		players_pointer[i]->throw_out_all_remain_cards();
}