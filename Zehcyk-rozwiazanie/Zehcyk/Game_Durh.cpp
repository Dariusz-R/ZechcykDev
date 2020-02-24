
#include <iostream>
#include "Game_Durh.h"
#include "Text.h"

using namespace std;

Game_Durh::Game_Durh(Player* players_adress, short player_with_initiative_copy)
	: player_who_chose_durh(player_with_initiative_copy)
{
	thrown[0] = NULL;
	thrown[1] = NULL;
	thrown[2] = NULL;
	player_with_initiative = player_with_initiative_copy;
	players_pointer[0] = &players_adress[0];
	players_pointer[1] = &players_adress[1];
	players_pointer[2] = &players_adress[2];
	values_of_thrown_cards[3-1] = { 0 };
	was_durh_successful = true; 
}



void Game_Durh::play_durh(short game_points_multiplier) {

	was_durh_successful = true;

	for (int i = 0; i < NUMBER_OF_CARDS_IN_PLAYER_HAND_BEFORE_THROWING; i++) {
		if (play_trick() != player_who_chose_durh) {
			was_durh_successful = false;
			break;
		}
	}
	
	player_with_initiative = player_who_chose_durh;
	if (was_durh_successful == true) {
		players_pointer[which_player_after_player_with_initiative(0)]->add_game_points(BASE_STAKE_FOR_DURH * 2 ^ (game_points_multiplier - 1));
		cout << "Durh wygrany";
		system("pause");
	} else {
		players_pointer[which_player_after_player_with_initiative(1)]->add_game_points(BASE_STAKE_FOR_DURH * 2 ^ (game_points_multiplier - 1));
		players_pointer[which_player_after_player_with_initiative(2)]->add_game_points(BASE_STAKE_FOR_DURH * 2 ^ (game_points_multiplier - 1));
		cout << "Durh przegrany";
		system("pause");
	}
	
	
}


short Game_Durh::play_trick()
{
	who_is_winning_trick = ANY_OF_PLAYERS;
	thrown[0] = {};
	thrown[1] = {};
	thrown[2] = {};


	player_throws_card_then_it_is_evaluated(player_with_initiative);
	who_is_winning_trick = player_with_initiative;
	player_throws_card_then_it_is_evaluated(which_player_after_player_with_initiative(1));
	who_is_winning_trick = compare_two_cards(player_with_initiative, which_player_after_player_with_initiative(1));
	player_throws_card_then_it_is_evaluated(which_player_after_player_with_initiative(2));
	who_is_winning_trick = compare_two_cards(who_is_winning_trick, which_player_after_player_with_initiative(2));


	game_log_actualization(who_is_winning_trick, 2);
	remove_thrown_cards_from_players_hands();
	player_with_initiative = who_is_winning_trick;

	return who_is_winning_trick;
}

void Game_Durh::game_log_actualization(short who, short situation)
{
	string log_line = "";
	short tab_counter = 0;
	log_line.append("\t*");
	tab_counter++;
	short number_of_spaces = 0;
	if (situation == 1) {

		for (short i = 0; i < NUMBER_OF_PLAYERS; i++) {
			if (thrown[which_player_after_player_with_initiative(i)] != NULL) {
				log_line.append("\t");
				tab_counter++;
				log_line.append(players_pointer[which_player_after_player_with_initiative(i)]->get_name(), 0, 2);
				log_line.append(":  ");
				log_line.append(thrown[which_player_after_player_with_initiative(i)]->symbol);
			}

		}

		number_of_spaces = 65 - log_line.size() - tab_counter * 7;
		log_line.append(number_of_spaces, ' ');
	}
	else if (situation == 2) {
		short log_size = Text::game_log_message[0].size() + players_pointer[who]->get_name().size();
		number_of_spaces = (54 - log_size - (54 - log_size) % 2) / 2;

		log_line.append(number_of_spaces, ' ');
		log_line.append(Text::game_log_message[0]);
		log_line.append(players_pointer[who]->get_name());
		log_line.append(number_of_spaces, ' ');
	}


	log_line.append("*");
	game_log.push_back(log_line);
}
