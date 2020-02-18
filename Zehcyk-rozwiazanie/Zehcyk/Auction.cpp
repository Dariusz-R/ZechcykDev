#include "Auction.h"
#include <iostream>
#include "Text.h"
#include <stdlib.h>


using namespace std;

short Auction::player_after_player_with_initiative(short which_after) {
		return ((player_with_initiative + which_after) % 3);
}

void Auction::contra(short& who ){
	player_with_initiative = who;
	auction_counter++;
}
short Auction::get_game_type_auct() { 
	return game_type_auct; 
}
short Auction::get_auction_counter() { 
	return auction_counter; 
}


short Auction::get_player_with_initiative() { 
	return player_with_initiative;
}

void Auction::reset_private_variables() {
	auction_counter = 0;
	game_type_auct = 0;
	player_with_initiative = 0;
	auction_log = "";
	log_counter = 0;
}


Auction::Auction(Player *players_adress)
{
	auction_counter = 0;
	game_type_auct = 0;
	player_with_initiative = 0;
	auction_log = "";
	log_counter = 0;

	players_auct[0] = &players_adress[0];
	players_auct[1] = &players_adress[1];
	players_auct[2] = &players_adress[2];
}


void Auction::history_actualization(short who, short what , short what2)
{
	log_counter++;
	string log_player(players_auct[who]->get_name());
	if (what2 != 100) auction_log += (Text::log_frame[2] + log_player + " -> " + Text::log_message[what] + Text::log_message[what2]);
	else auction_log += (Text::log_frame[2] + log_player + " -> " + Text::log_message[what]);
	auction_log.resize(((56+log_counter)*log_counter), ' ');
	auction_log += Text::log_frame[3];
}



string Auction::first_auction_player_see_four_cards(short first_player_this_round_function)
{
	short choice = 0, how_many_options = 0;
	log_counter = 0;
	auction_counter = 0;
	player_with_initiative = first_player_this_round_function;
	
	for (short i = 0; i < 3; i++) {
		do {
		

			players_auct[player_after_player_with_initiative(i)]->sort_cards("FOUR_CARDS");
			if (i > 0) {
				Text::read_text(Text::log_frame, 0, 2);
				cout << auction_log;
			}
			players_auct[i]->show(4, "AUCTION");
			switch (auction_counter) {
			case 0:
				Text::read_text(Text::A_4, 6, 2);
				Text::read_text(Text::A_4, 10, 1);
				how_many_options = 5;
				break;
			case 1:
				Text::read_text(Text::A_4, 6, 1);
				Text::read_text(Text::A_4, 8, 1);
				Text::read_text(Text::A_4, 10, 1);
				how_many_options = 6;
				break;
			case 2:
				Text::read_text(Text::A_4, 6, 1);
				Text::read_text(Text::A_4, 9, 2);
				how_many_options = 6;
				break;
			default:
				cout << "BLAD. WARSZAWA MA ZA DUZY LICZNIK KONTR" << endl;
			}
			cin >> choice;
			Text::cin_check(choice, how_many_options);
			system("CLS");
		} while (choice == NULL);
		if(choice > 0 && choice < 5) { 
			history_actualization(i, 5 + choice);
			player_with_initiative = i;
			auction_counter = 0;
			game_type_auct = choice;
			return "COLOUR";
		}
		else if (choice == 5 ) {
			history_actualization(i, auction_counter);
			if (auction_counter == 0) contra(i);
		}
		else if (choice == 6) {
				history_actualization(i, 3 + auction_counter );
				contra(i);
		}
	} 
	game_type_auct = choice;
	return "WARSOW";
}

bool Auction::player_see_eight_cards_decision_play_or_resign()
{
	short decision = NULL;

	for (short i = 0; i < 3; i++) {
		players_auct[i]->sort_cards("EIGHT_CARDS");
	}


	do
	{
		system("CLS");
		Text::read_text(Text::log_frame, 0, 2);
		cout << auction_log;
		players_auct[player_with_initiative]->show(8, "AUCTION");
		Text::read_text(Text::A_8, 0, 1);
		cin >> decision;
		Text::cin_check(decision, 2);
		system("CLS");
	
		if (decision == 1) {
			history_actualization(player_with_initiative, 10 , 5 + game_type_auct);
			auction_counter++;
			system("pause");
			system("CLS");
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


short Auction::subfunction(short who) {
	short choice = 0;
	short how_many_options = 0;

	do {
		system("CLS");
		Text::read_text(Text::log_frame, 0, 2);
		cout << auction_log;
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
		if (game_type_auct != 7 && game_type_auct != 8) {
			Text::read_text(Text::A_8, 9, 2);
			how_many_options = 4;
		}
		else if (game_type_auct != 7) {
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

void Auction::breaking_colour(short &who) {

	player_with_initiative = player_after_player_with_initiative(who);
	agree_to_play_on_current_terms = 0;
	auction_counter = 1;
	who = 1;
}

short Auction::players_see_eight_cards_decision_contra_misery_durh()
{
	agree_to_play_on_current_terms = 0;

	for (short j = 0; j < 3; j++) {
		players_auct[j]->sort_cards("EIGHT_CARDS");
	}
	short i = 1; 
	do {
	
		switch (subfunction ( player_after_player_with_initiative( i ) ))
		{
		case 1:
			agree_to_play_on_current_terms++;
			history_actualization(player_after_player_with_initiative(i), 21);
			if (agree_to_play_on_current_terms == 2 || (agree_to_play_on_current_terms == 1 && player_with_initiative == player_after_player_with_initiative(i))) {
				cout << "GRAMY HEJ HO!" << endl;
				system("pause");
			}
			i++;
			break;
		case 2:
			history_actualization(player_after_player_with_initiative(i), 11 + auction_counter);
			auction_counter++; 
			agree_to_play_on_current_terms = 0;
			if (i == 0) {
				i = 1;
			} else i = 0;
			break;
		case 3:
			history_actualization(player_after_player_with_initiative(i), 19);
			breaking_colour(i);
			game_type_auct = 7;
			break;
		case 4:
			history_actualization(player_after_player_with_initiative(i), 20);
			breaking_colour(i);
			game_type_auct = 8;
			break;
		}
	} while (auction_counter < 6);

		cout << "gramy hej ho";
	system("pause");

	/*if (get_game_type() == 1 || get_game_type() == 2 || get_game_type() == 3 || get_game_type() == 4)
	{
		if (players[which_player].ask_or_not() == true)
		{
			short second_option = NULL;
			extern short contra_counter;
			do
			{
				second_option = players[(which_player + 1) % 3].other_player_asked(get_game_type_pointer(), contra_counter);
				check_if(second_option, ((which_player + 1) % 3), contra_counter);
				if (second_option == 1 && contra_counter < 5)
				{
					second_option = players[(which_player + 2) % 3].other_player_asked(get_game_type_pointer(), contra_counter);
					check_if(second_option, ((which_player + 2) % 3), contra_counter);
				}
				if (second_option == 2 && contra_counter < 5)
				{
					second_option = players[which_player % 3].other_player_asked(get_game_type_pointer(), contra_counter);
					check_if(second_option, (which_player % 3), contra_counter);
				}
			} while (second_option == 2);
			if (get_game_type() == 7)
			{
				do
				{
					second_option = players[(which_player + 1) % 3].other_player_asked(get_game_type_pointer(), contra_counter);
					check_if(second_option, ((which_player + 1) % 3), contra_counter);
					if (second_option == 1 && contra_counter < 5)
					{
						second_option = players[(which_player + 2) % 3].other_player_asked(get_game_type_pointer(), contra_counter);
						check_if(second_option, ((which_player + 2) % 3), contra_counter);
					}
					if (second_option == 2 && contra_counter < 5)
					{
						second_option = players[which_player % 3].other_player_asked(get_game_type_pointer(), contra_counter);
						check_if(second_option, (which_player % 3), contra_counter);
					}
				} while (second_option == 2);
			}
			if (get_game_type() == 8)
			{
				do
				{
					second_option = players[(which_player + 1) % 3].other_player_asked(get_game_type_pointer(), contra_counter);
					check_if(second_option, ((which_player + 1) % 3), contra_counter);
					if (second_option == 1 && contra_counter < 5)
					{
						second_option = players[(which_player + 2) % 3].other_player_asked(get_game_type_pointer(), contra_counter);
						check_if(second_option, ((which_player + 2) % 3), contra_counter);
					}
					if (second_option == 2 && contra_counter < 5)
					{
						second_option = players[which_player % 3].other_player_asked(get_game_type_pointer(), contra_counter);
						check_if(second_option, (which_player % 3), contra_counter);
					}
				} while (second_option == 2);
			}


		}



	}



	else if (get_game_type() == 5 || get_game_type() == 6)
	{

		switch (warsow)
		{
		case 1:
			cout << "Gramy w Warszawe. Zaczyna gracz " << players[which_player].get_name() << endl << endl;
			break;

		case 2:
			cout << "Gramy w Kontre-Warszawe. Zaczyna gracz " << players[which_player].get_name() << endl << endl;
			break;

		case 3:
			cout << "Gramy w Rekontre-Warszawe. Zaczyna gracz " << players[which_player].get_name() << endl << endl;
			break;

		default:
			cout << "Blad w 3 switchu w run.cpp" << endl << endl;
			break;

		}

	}








	*/
	return game_type_auct;
}