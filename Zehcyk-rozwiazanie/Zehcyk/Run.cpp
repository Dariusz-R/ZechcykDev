#include <iostream>
#include "Run.h"
#include "Text.h"
#include <windows.h>
#include <vector>







Run::Run()
	:
	deck_pattern{ Card(0), Card(1), Card(2), Card(3), Card(4), Card(5), Card(6), Card(7), Card(8), Card(9), Card(10), Card(11), Card(12), Card(13), Card(14), Card(15),
	Card(16), Card(17), Card(18), Card(19), Card(20), Card(21), Card(22), Card(23) }
	
{
	for (short i = 0; i < 24; i++) {
		deck_pointers[i] = &(deck_pattern[i]);
	}
	game_type = 0;
	player_who_begins_the_auction = 0;

};

void Run::run_general() {
	select_language();
	start();
	meet_players();
	bool play = false;
	Auction auction(players, &game_type, player_who_begins_the_auction);

	std::string result_of_the_first_auction;
	do {
		player_who_begins_the_auction++;
		auction.reset_private_variables();
		shuffle_cards();
		give_cards_to_players();

		result_of_the_first_auction = auction.first_auction_player_see_four_cards();

		if (result_of_the_first_auction == "COLOUR")
			play = auction.player_see_eight_cards_decision_play_or_resign();
		else if (result_of_the_first_auction == "WARSOW") {
			Game::set_important_player(auction.get_player_with_initiative());
			Game::set_game_points_multiplier(auction.get_auction_counter());
			Game_Warsow game_warsow(players);
			game_warsow.play_game();
		}

	} while (play == false);

	auction.players_see_eight_cards_decision_contra_misery_durh();
	Game::set_important_player(auction.get_player_with_initiative());
	Game::set_game_points_multiplier(auction.get_auction_counter());
	if (game_type > 0 && game_type < 5){
		Game_Colour game_colour(players, game_type);
		game_colour.play_game();
	} else if (game_type == 7) {
		Game_Durh game_durh(players);
		game_durh.play_game();
	} else if (game_type == 8) {
		Game_Misery game_misery(players);
		game_misery.play_game();
	}
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
		std::cin >> want_to_play;
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
	players_introduction();
	system("CLS");
}

void Run::players_introduction()
{
	system("CLS");
	for (short i = 0; i < 3; i++) {
		Text::read_text(Text::start_menu, 5 + i, 1);
		std::cout << players[i].get_name();
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

void Run::give_cards_to_players()
{
	for (short h = 0 ; h < 2 ; h++)
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
		{
			players[i].take_card(deck_pointers[12*h+4*i+j]);
		}
		
	
}






