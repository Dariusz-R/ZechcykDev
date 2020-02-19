#include <iostream>
#include "Run.h"
#include "Text.h"
#include <windows.h>
#include <vector>

using namespace std;





Run::Run()
	:

	deck_pattern{ Card(0), Card(1), Card(2), Card(3), Card(4), Card(5), Card(6), Card(7), Card(8), Card(9), Card(10), Card(11), Card(12), Card(13), Card(14), Card(15),
	Card(16), Card(17), Card(18), Card(19), Card(20), Card(21), Card(22), Card(23) }
{
	for (short i = 0; i < 24; i++) {
		deck_pointers[i] = &(deck_pattern[i]);
	}
	game_type = 0;
	first_player_this_round = 0;

};



void Run::run_general() {
	select_language();
	start();
	meet_players();
	bool play = false;
	Auction auction(players, &game_type, first_player_this_round);

	string result_of_the_first_auction;
	do {
		first_player_this_round++;
		auction.reset_private_variables();
		shuffle_cards();
		give_cards_to_players();

		result_of_the_first_auction = auction.first_auction_player_see_four_cards(first_player_this_round);


		if (result_of_the_first_auction == "COLOUR")
			play = auction.player_see_eight_cards_decision_play_or_resign();

		//else if (result_of_the_first_auction == "WARSOW") {
			//run_game_warsow();
		//}
	} while (play == false);

	auction.players_see_eight_cards_decision_contra_misery_durh();
}


void Run::select_language() {
	short language_pack;
	do {
		Text::load_language_version();
		Text::read_text(Text::pl_OR_eng, 0, 1);
		cin >> language_pack;
		Text::cin_check(language_pack, 2, true);
		if (language_pack == 1) { 
			system("CLS");  
			Text::set_language_version("Polish"); 
		} else if (language_pack == 2) {
			system("CLS");
			Text::set_language_version("English");
		}
	} while (language_pack == NULL);
	Text::load_language_version();

}

void Run::start()
{

	short want_to_play = 0;
	bool loop_choice = false;

	do
	{
		Text::read_text(Text::start_menu,0,1);
		cin >> want_to_play;
		loop_choice = false;
		Text::cin_check(want_to_play, 3);
		if (want_to_play == 1) { 
			loop_choice = true;
			system("CLS"); 
		} else if (want_to_play == 2) { 
			Text::read_text(Text::start_menu, 1, 1);
			system("pause"); exit(0); 
		} else if (want_to_play == 3) {  
			ShellExecute(GetDesktopWindow(), L"open", L"\\Polish\\ZECHCYK2.pdf", NULL, NULL, SW_SHOWMAXIMIZED);
			system("CLS");
		}
	} while (want_to_play != 1);


}

void Run::meet_players()
{
	for (short i = 0; i < 3; i++) {
		players[i].name_player(i + 2 );
	}
	who_plays();
	system("CLS");
}

void Run::who_plays()
{
	system("CLS");
	for (short i = 0; i < 3; i++) {
		Text::read_text(Text::start_menu, 5 + i, 1);
		cout << players[i].get_name();
	}
	Text::read_text(Text::start_menu, 8, 1);
	system("pause");
}

void Run::shuffle_cards()
{
	for (short j = 0 ; j < 3 ; j++)
	for (short i = 0; i < 24; i++)
	{
		int r = i + (rand() % (24 - i));

		swap(deck_pointers[i], deck_pointers[r]);
	}

}


//***************************************************************************************************************************************************************************
// GIVES 8 SHUFFLED BEFORE CARDS TO EACH PLAYER.

void Run::give_cards_to_players()
{
	for (short h = 0 ; h < 2 ; h++)
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
		{
			players[i].take_card(deck_pointers[12*h+4*i+j]);
		}
		
	
}



/*
void Run::run_game(short game_to_run)
{
	if (game_to_run == 5 || game_to_run == 6)
	{
		short choice = NULL, who_lose = NULL;
		Game_Warsow playing_warsow;
		playing_warsow.share_players(players);
		short initiative = 0;
		for (int i = 0; i < 8; i++)
			initiative = playing_warsow.take_and_compare(initiative);
		who_lose = playing_warsow.who_won();
		cout << "Przegral gracz " << players[who_lose].get_name() << " uzyskujac " << playing_warsow.players_points[who_lose] << "pkt.\n";
		switch (warsow)
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
	else if (game_to_run == 1 || game_to_run == 2 || game_to_run == 3 || game_to_run == 4)
	{
		short choice = NULL, who_lose = NULL;
		extern short contra_counter;
		Game_Colour playing_colour;
		playing_colour.share_players(players);
		playing_colour.set_trumph(game_to_run);
		playing_colour.get_trumph();
		short initiative = 0;
		for (int i = 0; i < 8; i++)
			initiative = playing_colour.take_and_compare(initiative);
		who_lose = playing_colour.who_won();
		cout << "Przegral gracz " << players[who_lose].get_name() << " uzyskujac " << playing_colour.players_points[who_lose] << "pkt.\n";
		if (contra_counter == 1)
		{
			cout << "Gracz " << players[who_lose].get_name() << " przegral za 1 punkt meczowy";
		}
		else if (warsow == 2)
		{
			cout << "Gracz " << players[who_lose].get_name() << " przegral za 2 punkty meczowe";
		}
		else if (warsow == 3)
		{
			cout << "Gracz " << players[who_lose].get_name() << " przegral za 4 punkty meczowe";
		}

	}
	
}*/





