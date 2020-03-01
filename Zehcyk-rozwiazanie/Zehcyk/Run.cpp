#include "Run.h"
#include "Text.h"

#include <iostream>
#include <windows.h>
#include <vector>











Run::Run()
	:
	deck_pattern{ Card()}
	
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
		auction.resetPrivateVariables();
		shuffle_cards();
		give_cards_to_players();

		result_of_the_first_auction = auction.carryFirstAuction();

		if (result_of_the_first_auction == "COLOUR")
			play = auction.confirmThatGameLeaderWantToPlayAfterHeSawAllHisCards();
		else if (result_of_the_first_auction == "WARSOW") {
			Game::setGameLeader(auction.getGameLeader());
			Game::setGamePointsMultiplier(auction.getAuctionCounter());
			GameWarsow game_warsow(players);
			game_warsow.playGame();
		}

	} while (play == false);

	auction.carrySecondAuction();
	Game::setGameLeader(auction.getGameLeader());
	Game::setGamePointsMultiplier(auction.getAuctionCounter());
	if (game_type > 0 && game_type < 5){
		GameColour game_colour(players, game_type);
		game_colour.playGame();
	} else if (game_type == 7) {
		GameDurh game_durh(players);
		game_durh.playGame();
	} else if (game_type == 8) {
		GameMisery game_misery(players);
		game_misery.playGame();
	}
}

void Run::select_language() {
	short language_pack;
	do {
		Text::load_language_version();
		Text::readText(Text::pl_OR_eng, 0, 1);
		cin >> language_pack;
		Text::cinCheck(language_pack, 2, true);
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
		Text::readText(Text::start_menu,0,1);
		std::cin >> want_to_play;
		loop_choice = false;
		Text::cinCheck(want_to_play, 3);
		if (want_to_play == 1) { 
			loop_choice = true;
			system("CLS"); 
		} else if (want_to_play == 2) { 
			Text::readText(Text::start_menu, 1, 1);
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
		players[i].namePlayer(i + 2 );
	}
	players_introduction();
	system("CLS");
}

void Run::players_introduction()
{
	system("CLS");
	for (short i = 0; i < 3; i++) {
		Text::readText(Text::start_menu, 5 + i, 1);
		std::cout << players[i].getName();
	}
	Text::readText(Text::start_menu, 8, 1);
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
			players[i].takeCardFromTheDeck(deck_pointers[12*h+4*i+j]);
		}
		
	
}






