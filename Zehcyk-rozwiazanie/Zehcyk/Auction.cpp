#include "Auction.h"
#include <iostream>
#include "Text.h"
#include <stdlib.h>
#include <iomanip>
#include <vector>


using namespace std;

short* Auction::game_type_auct;
vector <string> Auction::auction_log = {};


Auction::Auction(Player* players_adress, short* game_type_in_Run_class, short &player_who_has_started_the_auction)
	:SIX_OPTIONS_TO_CHOSE(6), FIVE_OPTIONS_TO_CHOSE(5), PLAYER_WHO_HAS_STARTED_THE_AUCTION(player_who_has_started_the_auction),
	NUMBER_OF_PLAYERS(3), HEARTS(1), TILES(2), PIKES(3), CLOVERS(4), ALL_CARDS_IN_HAND(8), FIRST_FOUR(4), ALL_CARDS_FOR_MISERY(9), WARSOW(5), DOUBLE_THE_STAKE(6)
{
	auction_counter = 0;
	agree_to_play_on_current_terms = 0;
	player_with_initiative = PLAYER_WHO_HAS_STARTED_THE_AUCTION;
	log_counter = 0;
	player_choice = 0;
	game_type_auct = game_type_in_Run_class;

	players_auct[0] = &players_adress[0];
	players_auct[1] = &players_adress[1];
	players_auct[2] = &players_adress[2];
}

short Auction::get_player_with_initiative() {
	return player_with_initiative;
}

void Auction::reset_private_variables() {
	auction_counter = 0;
	player_with_initiative = 0;
	auction_log.clear();
	log_counter = 0;
}

short Auction::show_first_auction_menu(short which_player) {
	if (which_player != PLAYER_WHO_HAS_STARTED_THE_AUCTION) {
		Text::read_text(Text::log_frames, 0, 1);
		read_auction_log();
	}
	players_auct[which_player]->show(4, "AUCTION");
	switch (auction_counter) {
	case 0:
		Text::read_text(Text::A_4, 6, 2);
		Text::read_text(Text::A_4, 10, 1);
		return FIVE_OPTIONS_TO_CHOSE;
		break;
	case 1:
		Text::read_text(Text::A_4, 6, 1);
		Text::read_text(Text::A_4, 8, 1);
		Text::read_text(Text::A_4, 10, 1);
		return SIX_OPTIONS_TO_CHOSE;
		break;
	case 2:
		Text::read_text(Text::A_4, 6, 1);
		Text::read_text(Text::A_4, 9, 2);
		return SIX_OPTIONS_TO_CHOSE;
		break;
	default:
		cout << "BLAD. WARSZAWA MA ZA DUZY LICZNIK KONTR" << endl;
	}
}

void Auction::player_picked_colour(short which_player) {
	history_actualization(which_player, 5 + player_choice);
	player_with_initiative = which_player;
	auction_counter = 0;
	*game_type_auct = player_choice;
}


string Auction::first_auction_player_see_four_cards()
{
	short how_many_options_to_chose = 0;
	log_counter = 0;
	auction_counter = 0;
	player_choice = 0;
	sort_players_cards(FIRST_FOUR);
	

	for (short i = 0; i < NUMBER_OF_PLAYERS; i++) {
		do {
			how_many_options_to_chose = show_first_auction_menu(i);
			cin >> player_choice;
			Text::cin_check(player_choice, how_many_options_to_chose);
			system("CLS");
		} while (player_choice == 0);


		if (player_choice == HEARTS || player_choice == TILES || player_choice == PIKES || player_choice == CLOVERS) {
			player_picked_colour(i);
			sort_players_cards(ALL_CARDS_IN_HAND);
			return "COLOUR";
		} else if (player_choice == WARSOW) {
			history_actualization(i, auction_counter);
			if (auction_counter == 0) 
				contra(i);
		} else if (player_choice == 6) {
			history_actualization(i, 3 + auction_counter);
			contra(i);
		}
	}
	sort_players_cards(ALL_CARDS_IN_HAND);
	*game_type_auct = player_choice;
	return "WARSOW";
}

void Auction::sort_players_cards(short how_many_cards_to_sort) {
	for (short i = 0; i < NUMBER_OF_PLAYERS; i++)
		players_auct[i]->sort_cards(how_many_cards_to_sort);
}

					short Auction::player_after_player_with_initiative(short which_after) {
						return ((player_with_initiative + which_after) % 3);
					}



					void Auction::history_actualization(short who, short what, short what2)
					{
						string log_line = players_auct[who]->get_name();
						log_line.append(" -> ");
						log_line.append(Text::log_message[what]);
						if (what2 != 100)
							log_line.append(Text::log_message[what2]);

						auction_log.push_back(log_line);
					}



					void Auction::read_auction_log(bool all) {

						if (all == true) {
							for (short i = 0; i < auction_log.size(); i++) {
								cout << setw(10) << "* " << setw(55);
								short size_of_the_log = auction_log[i].size();
								for (short j = 0; j < 53 - size_of_the_log; j++) {
									auction_log[i].append(" ");
								}
								if (i == auction_log.size() - 1)
									auction_log[auction_log.size() - 1].append("*");
								cout << auction_log[i] << endl;
							}
						}
						else {
							cout << setw(10) << "* " << setw(55);
							short size_of_the_log = auction_log.back().size();
							for (short j = 0; j < 53 - size_of_the_log; j++) {
								auction_log.back().append(" ");
							}
							if( auction_log.back().back() != '*' )
								auction_log.back().append("*");
							cout << auction_log.back() << endl;
						}
					}



bool Auction::player_see_eight_cards_decision_play_or_resign()
{
	short decision = 0;

	do
	{
		system("CLS");
		Text::read_text(Text::log_frames, 0, 1);
		read_auction_log();
		players_auct[player_with_initiative]->show(8, "AUCTION");
		Text::read_text(Text::A_8, 0, 1);
		cin >> decision;
		Text::cin_check(decision, 2);
		system("CLS");

		if (decision == 1) {
			history_actualization(player_with_initiative, 9, 5 + *game_type_auct);
			auction_counter++;
			return true;
		}
		else if (decision == 2) {
			system("CLS");
			Text::read_text(Text::log_message, 17, 1);
			cout << players_auct[player_with_initiative]->get_name();
			Text::read_text(Text::log_message, 18, 1);
			for (short i = 0; i < 3; i++) {
				players_auct[i]->throw_out_all_remain_cards();
			}
			return false;
		}
	} while (decision != 1 && decision != 2);
}



void Auction::players_see_eight_cards_decision_contra_misery_durh()
{
	short did_agreement_was_made = false;

	short i = 1;
	do {

		switch (subfunction(player_after_player_with_initiative(i)))
		{
		case 1:
			agree_to_play_on_current_terms++;
			history_actualization(player_after_player_with_initiative(i), 18);
			if (agree_to_play_on_current_terms == 2 || (agree_to_play_on_current_terms == 1 && player_with_initiative == player_after_player_with_initiative(i))) {
				cout << "GRAMY HEJ HO!" << endl;
				system("pause");
				did_agreement_was_made = true;
			}
			i++;
			break;
		case 2:
			if (*game_type_auct == 7 || *game_type_auct == 8)
				history_actualization(player_after_player_with_initiative(i), 9 + auction_counter, 9 + *game_type_auct);
			else history_actualization(player_after_player_with_initiative(i), 9 + auction_counter, 5 + *game_type_auct);
			auction_counter++;
			agree_to_play_on_current_terms = 0;
			if (i == 0) {
				i = 1;
			}
			else i = 0;
			break;
		case 3:
			history_actualization(player_after_player_with_initiative(i), 16);
			breaking_colour(i);
			*game_type_auct = 7;
			break;
		case 4:
			history_actualization(player_after_player_with_initiative(i), 17);
			breaking_colour(i);
			*game_type_auct = 8;
			break;
		}
	} while (auction_counter < 6 && did_agreement_was_made == false);
}







short Auction::get_auction_counter() {
	return auction_counter;
}





//PRIVATE METHODS************************************************************************************************************************************

void Auction::contra(short& who) {
	player_with_initiative = who;
	auction_counter++;
}



short Auction::subfunction(short who) {
	short choice = 0;
	short how_many_options = 0;

	do {
		system("CLS");
		Text::read_text(Text::log_frames, 0, 1);
		read_auction_log();
		players_auct[who]->show(8, "AUCTION");
		Text::read_text(Text::A_8, 2, 2);
		switch (auction_counter) {
		case 1:
			Text::read_text(Text::A_8, 4, 1);
			break;
		case 2:
			Text::read_text(Text::A_8, 5, 1);
			break;
		case 3:
			Text::read_text(Text::A_8, 6, 1);
			break;
		case 4:
			Text::read_text(Text::A_8, 7, 1);
			break;
		case 5:
			Text::read_text(Text::A_8, 8, 1);
			break;
		default:
			cout << "Bledna wartosc auction_counter" << endl;
			system("pause");
			break;
		}
		if (*game_type_auct != 7 && *game_type_auct != 8) {
			Text::read_text(Text::A_8, 9, 2);
			how_many_options = 4;
		}
		else if (*game_type_auct != 7) {
			Text::read_text(Text::A_8, 9, 1);
			how_many_options = 3;
		}
		else how_many_options = 2;
		Text::read_text(Text::A_8, 11, 1);
		cin >> choice;
		Text::cin_check(choice, how_many_options);
	} while (choice == 0);
	return choice;
}



void Auction::breaking_colour(short& who) {

	player_with_initiative = player_after_player_with_initiative(who);
	agree_to_play_on_current_terms = 0;
	auction_counter = 1;
	who = 1;
}