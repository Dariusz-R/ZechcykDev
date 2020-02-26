#include "Game_Colour.h"
#include "Run.h"
#include <iomanip>





//vector <string> Game_Colour::game_log = {};

Game_Colour::Game_Colour(Player* players_adress, short trump_copy)
	: player_who_chose_colour(get_important_player()),
	trump(trump_copy),
	was_colour_successful(variable_replaced_by_reference)
{
	basic_stake = 3;
	thrown[0] = NULL;
	thrown[1] = NULL;
	thrown[2] = NULL;
	
	throwing_player = player_who_chose_colour;
	players_pointer[0] = &players_adress[0];
	players_pointer[1] = &players_adress[1];
	players_pointer[2] = &players_adress[2];
	values_of_thrown_cards[3-1] = { 0 };
	sum_of_points_from_current_trick = 0;
	did_other_players_meld = DID_NOT_MELD;
	did_player_who_chose_color_meld = DID_NOT_MELD;
	variable_replaced_by_reference = NO_ANSWER_YET;
	did_other_players_won_a_trick = false;
	did_player_who_picked_a_colour_won_a_trick = false;
}

bool Game_Colour::checking_the_condition_which_depends_from_gametype(short i) {
	if (who_is_winning_trick == player_who_chose_colour)
		did_player_who_picked_a_colour_won_a_trick = true;
	else
		did_other_players_won_a_trick = true;


	if (players_pointer[player_who_chose_colour]->get_trick_points() > 65) {
		was_colour_successful = true;
		return false;
	}
	else if (players_pointer[(player_who_chose_colour + 1) % 3]->get_trick_points() + players_pointer[(player_who_chose_colour + 2) % 3]->get_trick_points() > 65) {
		was_colour_successful = false;
		return false;
	}
	else if (i = NUMBER_OF_CARDS_IN_PLAYER_HAND_BEFORE_THROWING - 1 && was_colour_successful == NO_ANSWER_YET) {
		was_colour_successful = (player_who_won_the_trick == player_who_chose_colour) ? true : false;
			return true;
	}
}

void Game_Colour::show_info_about_game() {
	if (variable_replaced_by_reference == false)
		std::cout << "Kolor przegral " << players_pointer[player_who_chose_colour]->get_name() << endl;
	else std::cout << "Kolor wygral " << players_pointer[player_who_chose_colour]->get_name() << endl;
	system("pause");
}

void Game_Colour::sum_up_and_give_trick_points_to_player_who_won_trick() {
	sum_of_points_from_current_trick = values_of_thrown_cards[0] + values_of_thrown_cards[1] + values_of_thrown_cards[2];
	players_pointer[who_is_winning_trick]->add_trick_points(sum_of_points_from_current_trick);
}

void Game_Colour::game_log_update(short who, short situation)
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
		std::string sum = std::to_string(sum_of_points_from_current_trick);
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

std::vector<short> Game_Colour::what_player_can_throw(short id_player) {
	std::vector <short> values_of_the_player_cards_in_colour, player_cards_in_colour, player_cards_winning;
	player_cards_in_colour = players_pointer[id_player]->how_many_card_in_thrown_colour_i_have(thrown[throwing_player]->colour);
	if(thrown[throwing_player]->colour != trump && player_cards_in_colour.empty())
		player_cards_in_colour = players_pointer[id_player]->how_many_card_in_thrown_colour_i_have(trump);
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

short Game_Colour::compare_two_cards(short id_player, short id2_player)
{
	if (thrown[id_player]->colour != trump && thrown[id2_player]->colour == trump)
		return id2_player;
	else {
		if (thrown[id_player]->colour == thrown[id2_player]->colour) {

			return (values_of_thrown_cards[id_player] < values_of_thrown_cards[id2_player]) ? id2_player : id_player;

		}
		else
			return id_player;
	}
		
}

void Game_Colour::player_throws_card_then_it_is_evaluated(short id_player) {
	if (id_player == throwing_player) {
		thrown[throwing_player] = players_pointer[throwing_player]->which_card_I_throw();
		add_points_if_meld();
	}

	else
		thrown[id_player] = players_pointer[id_player]->which_card_I_throw(what_player_can_throw(id_player));

	game_log_update(id_player, 1);
	card_evaluation(thrown[id_player], values_of_thrown_cards[id_player]);
	system("CLS");
}

void  Game_Colour::add_points_if_meld() {
	if (does_player_meld() == true) {
		if (thrown[throwing_player]->colour == trump){
			players_pointer[throwing_player]->add_trick_points(NUMBER_OF_POINTS_FOR_MELD_IN_TRUMP_COLOUR);
			note_who_meld(NUMBER_OF_POINTS_FOR_MELD_IN_TRUMP_COLOUR);
		}
		else {
			players_pointer[throwing_player]->add_trick_points(NUMBER_OF_POINTS_FOR_MELD_IN_OTHER_COLOUR);
			note_who_meld(NUMBER_OF_POINTS_FOR_MELD_IN_OTHER_COLOUR);
		}
	}
}

void Game_Colour::note_who_meld(short number_of_points) {
	if (throwing_player == player_who_chose_colour)
		did_player_who_chose_color_meld = number_of_points;
	else
		did_other_players_meld = number_of_points;

}

bool Game_Colour::does_player_meld() {
	bool does_player_meld = false;
	if (players_pointer[throwing_player]->do_I_have_queen_and_king_in_one_colour() == true) {
		if (players_pointer[throwing_player]->do_I_want_to_meld() == true)
			return true;
	}
	else
		return false;
}

void Game_Colour::basic_stake_modification() {
	if (was_colour_successful) {
		if (players_pointer[(player_who_chose_colour + 1) % 3]->get_game_points() + players_pointer[(player_who_chose_colour + 2) % 3]->get_game_points() > 32)
			basic_stake = 1;
		else if (did_other_players_won_a_trick)
			basic_stake = 2;
	} else {
		if (players_pointer[player_who_chose_colour]->get_game_points() > 32)
			basic_stake = 1;
		else if (did_player_who_picked_a_colour_won_a_trick)
			basic_stake = 2;
	}
}


void Game_Colour::distribute_game_points() {
	basic_stake_modification();
	if (was_colour_successful) {
		players_pointer[player_who_chose_colour]->add_game_points(basic_stake * 2 ^ (get_game_points_multiplier() - 1));
	}
	else {
		players_pointer[(player_who_chose_colour + 1) % 3]->add_game_points(basic_stake * 2 ^ (get_game_points_multiplier() - 1));
		players_pointer[(player_who_chose_colour + 2) % 3]->add_game_points(basic_stake * 2 ^ (get_game_points_multiplier() - 1));
	}
}










