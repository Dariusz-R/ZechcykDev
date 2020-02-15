#include "Auction.h"
#include <iostream>
#include "Text.h"
#include <stdlib.h>


using namespace std;



void Auction::contra(short& who ){
	player_with_initiative = who;
	auction_counter++;
}
void Auction::set_game_type_auct(short type) { game_type_auct = type; }
short Auction::get_game_type_auct() { return game_type_auct; }
void Auction::reset_game_type_auct() { game_type_auct = 0;  }
short Auction::get_auction_counter() { return auction_counter; }
void Auction::increment_auction_counter() { auction_counter++; }
void Auction::reset_auction_counter() { auction_counter = 0; }
void Auction::set_player_with_initiative(short the_man) { player_with_initiative = the_man; }
short Auction::get_player_with_initiative() { return player_with_initiative; }
void Auction::set_temp_string(string temp) { temp_string = temp; }
string Auction::get_temp_string() { return temp_string; }
void Auction::reset_temp_string() { temp_string = ""; }
void Auction::set_temp_string_2(string temp_2) { temp_string_2 = temp_2; }
string Auction::get_temp_string_2() { return temp_string_2; }
void Auction::reset_temp_string_2() { temp_string_2 = ""; }

void Auction::reset_player_with_initiative() { player_with_initiative = 10; } // player numbers : 0,1,2 - NULL is not the best option

void Auction::share_players(Player *players_adress)
{
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

string Auction::read_auction_log() {
	return auction_log;
}


short Auction::game_type_auction_four_cards()
{
	short choice = NULL, how_many_options = NULL;
	log_counter = 0;
	reset_auction_counter();

	for (short i = 0; i < 3; i++) {
		do {


			system("CLS");
			if (i > 0) {
				Text::read_text(Text::log_frame, 0, 2);
				cout << read_auction_log();
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
			return choice; 
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
	game_type_auct = 5;
	return 5;
}

bool Auction::ask_or_not()
{
	short decision = NULL;

	do
	{
		system("CLS");
		Text::read_text(Text::log_frame, 0, 2);
		read_auction_log();
		players_auct[player_with_initiative]->show(8, "AUCTION");
		Text::read_text(Text::A_8, 0, 1);
		cin >> decision;
		Text::cin_check(decision, 2);
		system("CLS");
	
		if (decision == 1) {
			history_actualization(player_with_initiative, 10 , 6 + game_type_auct);
			increment_auction_counter();
			system("pause");
			system("CLS");
			return true;
		}
		else if (decision == 2) {
			system("CLS");
			Text::read_text(Text::log_message, 17, 1);
			cout << players_auct[player_with_initiative]->get_name();
			Text::read_text(Text::log_message, 18, 1);
			system("pause");
			return false;
		}
	} while (decision != 1 && decision != 2);
}

short Auction::game_type_auction_eight_cards()
{
	for (int i = 0; i < 3; i++)
	{
		system("CLS");
		if (i > 0) {
			Text::read_text(Text::log_frame, 0, 2);
			cout << read_auction_log();
		}
		players_auct[i]->show(8, "AUCTION");
		Text::read_text(Text::A_4, 10, 1);
		

	}

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