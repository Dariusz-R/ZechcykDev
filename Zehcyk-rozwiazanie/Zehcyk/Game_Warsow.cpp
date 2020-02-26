#include "Game_Warsow.h"
#include "Run.h"
#include <iomanip>






Game_Warsow::Game_Warsow(Player* players_adress)
	: player_who_begins_the_game(get_important_player()),
	player_who_lost_warsow(get_important_player_adress())
{
	basic_stake = 1;
	thrown[0] = NULL;
	thrown[1] = NULL;
	thrown[2] = NULL;
	player_with_initiative = player_who_begins_the_game;
	players_pointer[0] = &players_adress[0];
	players_pointer[1] = &players_adress[1];
	players_pointer[2] = &players_adress[2];
	values_of_thrown_cards[3-1] = { 0 };
	sum_of_points_from_current_trick = 0;
	
}

bool Game_Warsow::checking_the_condition_which_depends_from_gametype(short i) {
	if (players_pointer[player_with_initiative]->get_trick_points() > 60) {
		player_who_lost_warsow = player_with_initiative;
		return false;
	}
	else if (i = NUMBER_OF_CARDS_IN_PLAYER_HAND_BEFORE_THROWING - 1 && variable_replaced_by_reference == ANY_OF_PLAYERS) {
		player_who_lost_warsow = who_has_the_most_points();
	}
	return true;
}

void Game_Warsow::show_info_about_game() {
	std::cout << "Warszawe przegral " << players_pointer[player_who_lost_warsow]->get_name() << std::endl <<
		"PKT SZTYCHOWE " << players_pointer[player_who_lost_warsow]->get_trick_points() << std::endl
		<< "PKT GRY ktore uzyskali pozostali gracze " << players_pointer[(player_who_lost_warsow + 1) % 3]->get_game_points();
	system("pause");
}

void Game_Warsow::sum_up_and_give_trick_points_to_player_who_won_trick() {
	sum_of_points_from_current_trick = values_of_thrown_cards[0] + values_of_thrown_cards[1] + values_of_thrown_cards[2];
	players_pointer[who_is_winning_trick]->add_trick_points(sum_of_points_from_current_trick);
}

void Game_Warsow::game_log_update(short who, short situation)
{
	string log_line = "";
	short tab_counter = 0;
	log_line.append("\t*");
	tab_counter++;
	short number_of_spaces = 0;
	if (situation == 1) {

		for (short i = 0; i < NUMBER_OF_PLAYERS; i++) {
			if (thrown[queue_of_throwing(i)] != NULL) {
				log_line.append("\t");
				tab_counter++;
				log_line.append(players_pointer[queue_of_throwing(i)]->get_name(), 0, 2);
				log_line.append(":  ");
				log_line.append(thrown[queue_of_throwing(i)]->symbol);
			}

		}

		number_of_spaces = 65 - log_line.size() - tab_counter * 7;
		log_line.append(number_of_spaces, ' ');
	}
	else if (situation == 2) {
		string sum = to_string(sum_of_points_from_current_trick);
		short log_size = Text::game_log_message[0].size() + players_pointer[who]->get_name().size()
			+ Text::game_log_message[1].size() + sum.size() + Text::game_log_message[2].size();
		number_of_spaces = (54 - log_size - (54 - log_size) % 2) / 2;

		log_line.append(number_of_spaces, ' ');
		log_line.append(Text::game_log_message[0]);
		log_line.append(players_pointer[who]->get_name());
		log_line.append(Text::game_log_message[1]);
		log_line.append(sum);
		log_line.append(Text::game_log_message[2]);
		(sum.size() == 2) ? number_of_spaces++ : number_of_spaces += 2;
		log_line.append(number_of_spaces, ' ');
	}


	log_line.append("*");
	game_log.push_back(log_line);
}


short Game_Warsow::who_has_the_most_points()
{
	short who = ANY_OF_PLAYERS;
	who = (	players_pointer[0]->get_trick_points() > players_pointer[1]->get_trick_points()) ? 0 : 1;
	who = (players_pointer[who]->get_trick_points() > players_pointer[2]->get_trick_points()) ? who : 2;
	return who;
}


void Game_Warsow::distribute_game_points() {
		players_pointer[(player_who_lost_warsow + 1) % 3]->add_game_points(basic_stake * 2 ^ (get_game_points_multiplier() - 1));
		players_pointer[(player_who_lost_warsow + 2) % 3]->add_game_points(basic_stake * 2 ^ (get_game_points_multiplier() - 1));
	}

















