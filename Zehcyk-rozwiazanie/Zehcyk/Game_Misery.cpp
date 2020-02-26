#include "Game_Misery.h"
#include <iostream>
#include "Text.h"


Game_Misery::Game_Misery(Player* players_adress)
	:player_who_chose_misery(get_important_player()),
	was_misery_successful(variable_replaced_by_reference)
{
	basic_stake = 6;
	thrown[0] = NULL;
	thrown[1] = NULL;
	thrown[2] = NULL;
	throwing_player = player_who_chose_misery;
	players_pointer[0] = &players_adress[0];
	players_pointer[1] = &players_adress[1];
	players_pointer[2] = &players_adress[2];
	values_of_thrown_cards[3-1] = { 0 };
	variable_replaced_by_reference = NO_ANSWER_YET;
}


bool Game_Misery::checking_the_condition_which_depends_from_gametype(short i) {
	if (play_trick() == player_who_chose_misery) {
		was_misery_successful = false;
		return false;
	}
	return true;
}

void Game_Misery::show_info_about_game() {
	if (was_misery_successful == false)
		std::cout << "Mizerke przegral " << players_pointer[player_who_chose_misery]->get_name() << std::endl;
	else std::cout << "Mizerke wygral " << players_pointer[player_who_chose_misery]->get_name() << std::endl;
	system("pause");
}



void Game_Misery::game_log_update(short who, short situation)
{
	std::string log_line = "";
	short tab_counter = 0;
	log_line.append("\t*");
	tab_counter++;
	short number_of_spaces = 0;
	if (situation == 1) {

		for (short i = 0; i < NUMBER_OF_PLAYERS; i++) {
			if (thrown[which_player(i)] != NULL) {
				log_line.append("\t");
				tab_counter++;
				log_line.append(players_pointer[which_player(i)]->get_name(), 0, 2);
				log_line.append(":  ");
				log_line.append(thrown[which_player(i)]->symbol);
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
		conteiner = 1;
		break;
	case 'A':
		conteiner = 11;
		break;
	default:
		std::cout << "BLEDNE CZYTANIE SYMBOLU PRZY EWALUACJI";
		break;
	}

}