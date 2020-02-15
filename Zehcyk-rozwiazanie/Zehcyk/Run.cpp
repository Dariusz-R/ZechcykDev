#include <iostream>
#include "Run.h"
#include "Text.h"
#include <windows.h>

using namespace std;


void Run::set_game_type(short number) { game_type = number; }
short* Run::get_game_type_pointer() { return &game_type; }
short Run::get_game_type() { return game_type; }
//Player[] Run::get_players() { return players; }







//***************************************************************************************************************************************************************************
// USES FUNION ABOVE AND ASKS IF USER WANT TO PLAY


void Run::select_language() {
	short language_pack;
	do {
		Text::load_language_version();
		Text::read_text(Text::pl_OR_eng, 0, 1);
		cin >> language_pack;
		Text::cin_check(language_pack, 2, true);
		if (language_pack == 1) { system("CLS");  Text::set_language_version("Polish"); }
		else if (language_pack == 2) { system("CLS");  Text::set_language_version("English");}
	} while (language_pack == NULL);
	Text::load_language_version();

}

void Run::start()
{

	short want_to_play = NULL;
	bool loop_choice = false;

	do
	{
		Text::read_text(Text::start_menu,0,1);
		cin >> want_to_play;
		loop_choice = false;
		Text::cin_check(want_to_play, 3);
		if (want_to_play == 1) { loop_choice = true; system("CLS"); }
		else if (want_to_play == 2) { Text::read_text(Text::start_menu, 1, 1); system("pause"); exit(0); }
		else if (want_to_play == 3) {  
			ShellExecute(GetDesktopWindow(), L"open", L"\\Polish\\ZECHCYK2.pdf", NULL, NULL, SW_SHOWMAXIMIZED);
			system("CLS");
		}
	} while (want_to_play != 1);


}


//***************************************************************************************************************************************************************************
//CREATING PLAYERS (OBJECTS), ASKS THEM TO GIVE THEIR NAMES AND TO CONFIRM THAT THEY WERE PROPERLY ENTERED - SHOWS THEM ON THE SCREEN
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
extern string meet_1, meet_2, meet_3;

void Run::meet_players()
{
	for (short i = 0; i < 3; i++) {
		Text::read_text(Text::start_menu, i + 2, 1);
		players[i].name_player(i + 1);
	}
	who_plays();
	system("CLS");
}

//***************************************************************************************************************************************************************************
// PUTS DATA TO THE EMPTY CARD OBJECTS




void Run::create_cards()
{
	short values[6] = { 0, 2, 3, 4, 10, 11 };
	char symbol[6] = { '9', 'J', 'D', 'K', '1', 'A' };
	char colour[4] = { '\3', '\4', '\6', '\5' };

	for (short i = 0; i < 4; i++){
		for (short j = 0; j < 6; j++){
			deck_pattern[6 * i + j].create_card((6 * i + j), values[j], symbol[j], colour[i], i+1);
			//cout <<endl << deck_1[ 6 * i + j ].symbol <<"  " << deck_1[ 6 * i + j ].value << " " << deck_1[6*i+j].colour;       //TEST CZY PRZETASOWANO KARTY
		}
	}
}


//***************************************************************************************************************************************************************************
//SHUFFLE EXISTING CARD IN THE 24 CARDS DECK.

void Run::shuffle_cards()
{

	
	int fate[24] = {};

	for (int i = 0; i < 24; i++){
		fate[i] = rand() % 24;
		cout << fate[i] << endl;
		deck_2[i] = &deck_1[fate[i]];
		for (int j = 0; j < i; j++){

			if (fate[i] == fate[j]){
				i--;
				j = i;
			}
		}
	}
	system("pause");
}


//***************************************************************************************************************************************************************************
// GIVES 8 SHUFFLED BEFORE CARDS TO EACH PLAYER.

void Run::give_cards_to_players()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			players[i].take_card(*deck_2[8 * i + j]);
		}
		players[i].sort_cards();
	}
}

/*
//***************************************************************************************************************************************************************************
void Run::check_if(short &what, short who, short count)
{
	if (what == 7 || what == 8)
	{
		which_player = who;
		what = 3; 
	}

	if (count == 5)
		what = 1;

}



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
}

*/
void Run::run_general() {
	select_language();
	start();
	meet_players();
	create_cards();
	bool play = false;
	do {
		shuffle_cards();
		give_cards_to_players();
		Auction auction;
		auction.share_players(players);
		auction.game_type_auction_four_cards();
		play = auction.ask_or_not();
		auction.game_type_auction_eight_cards();
	} while (play == false);
}