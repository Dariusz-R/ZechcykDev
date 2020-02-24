#include "Game_Warsow.h"
#include "Run.h"
#include <iomanip>



using namespace std ;

vector <string> Game_Warsow::game_log = {};

Game_Warsow::Game_Warsow(Player* players_adress, short player_with_initiative_copy)
{
	thrown[0] = NULL;
	thrown[1] = NULL;
	thrown[2] = NULL;
	player_with_initiative = player_with_initiative_copy;
	players_pointer[0] = &players_adress[0];
	players_pointer[1] = &players_adress[1];
	players_pointer[2] = &players_adress[2];
	values_of_thrown_cards[3-1] = { 0 };
	sum_of_points_from_current_trick = 0;
}

void Game_Warsow::play_warsow(short game_points_multiplier) {
	for (int i = 0; i < NUMBER_OF_CARDS_IN_PLAYER_HAND_BEFORE_THROWING; i++)
		play_trick();
	player_with_initiative = who_has_the_most_points();

	players_pointer[which_player_after_player_with_initiative(1)]->add_game_points(2 ^ (game_points_multiplier - 1));
	players_pointer[which_player_after_player_with_initiative(2)]->add_game_points(2 ^ (game_points_multiplier - 1));
	cout << "Przegral gracz " << players_pointer[player_with_initiative]->get_name() << " uzyskujac " << players_pointer[player_with_initiative]->get_trick_points() << "pkt.\n";
	switch (game_points_multiplier)
	{
	case 1:
		cout << "Graliscie w Warszawe. Przegrana za 1 pkt!\n\n";
		break;

	case 2:
		cout << "Graliscie w kontre-warszawe. Przegrana za 2 pkt!\n\n";
		break;

	case 3:
		cout << "Graliscie w rekontre-warszawe. Przegrana za 4 pkt!\n\n";
		break;

	default:
		cout << "Blad w 4 switchu w run.cpp" << endl << endl;
		break;
	}



}
short Game_Warsow::play_trick()
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

	sum_of_points_from_current_trick = values_of_thrown_cards[0] + values_of_thrown_cards[1] + values_of_thrown_cards[2];

	players_pointer[who_is_winning_trick]->add_trick_points(sum_of_points_from_current_trick);
	game_log_actualization(who_is_winning_trick, 2);
	remove_thrown_cards_from_players_hands();
	player_with_initiative = who_is_winning_trick;

	return who_is_winning_trick;
}


void Game_Warsow::game_log_actualization(short who, short situation)
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
	short who = ANY_OF_PLAYERS, who2 = ANY_OF_PLAYERS;

	who = (players_points[0] > players_points[1]) ? 0 : 1;
	who2 = (players_points[who] > players_points[2]) ? who : 2;
	return who2;
}




















