#include <iostream>
#include "Run.h"

using namespace std;


void Run::set_game_type(short number) { game_type = number; }
short* Run::get_game_type_pointer() { return &game_type; }
short Run::get_game_type() { return game_type; }
//Player[] Run::get_players() { return players; }







//***************************************************************************************************************************************************************************
// USES FUNION ABOVE AND ASKS IF USER WANT TO PLAY


string Run::select_language() {
	short language_pack;
	do {
		cout << "Please select language / Prosze, wybierz jezyk : \n\n1. POLSKI/POLISH\n2. ANGIELSKI/ENGLISH\n\nTwoj wybor: ";
		cin >> language_pack;
		cin_check(language_pack, 3);
		if (language_pack == 1) { system("CLS"); return "POLISH"; }
		else if (language_pack == 2) { system("CLS"); return "ENGLISH"; }
	} while (language_pack != 2);
}

void Run::start(string language_pack)
{

	short want_to_play = NULL;
	bool loop_choice = false;
	extern string start_menu;
	load_language_version(language_pack);

	do
	{
		cout << start_menu << endl;
		cout << "\tTwoja odpowiedz: ";

		cin >> want_to_play;
		loop_choice = false;
		cin_check(want_to_play, 3);
		if (want_to_play == 1) { loop_choice = true; system("CLS"); }
		else if (want_to_play == 2) { cout << "Program zostanie zamkniety.\n"; system("pause"); exit(0); }
		else if (want_to_play == 3) {  
			ShellExecute(GetDesktopWindow(), L"open", L"ZECHCYK2.pdf", NULL, NULL, SW_SHOWMAXIMIZED);
			system("CLS");
		}
	} while (want_to_play != 1);


}


//***************************************************************************************************************************************************************************
//CREATING PLAYERS (OBJECTS), ASKS THEM TO GIVE THEIR NAMES AND TO CONFIRM THAT THEY WERE PROPERLY ENTERED - SHOWS THEM ON THE SCREEN



void Run::meet_players()
{
	short number = NULL;

	for (int i = 0; i < 3; i++)
	{
		number = i + 1;
		players[i].name_player(number);
	}
	for (int i = 0; i < 3; i++)
	{
		number = i + 1;
		players[i].who_plays(number);
	}
	Sleep(2000);
	system("CLS");
}

//***************************************************************************************************************************************************************************
// PUTS DATA TO THE EMPTY CARD OBJECTS

Card deck_1[24];
Card* deck_2[24];



void Run::create_cards()
{
	short values[6] = { 0, 2, 3, 4, 10, 11 };
	char symbol[6] = { '9', 'J', 'D', 'K', '1', 'A' };
	char colour[4] = { '\3', '\4', '\6', '\5' };

	for (short i = 0; i < 4; i++)
	{
		for (short j = 0; j < 6; j++)
		{
			deck_1[6 * i + j].create_card((6 * i + j), values[j], symbol[j], colour[i], i+1);
			//cout <<endl << deck_1[ 6 * i + j ].symbol <<"  " << deck_1[ 6 * i + j ].value << " " << deck_1[6*i+j].colour;       //TEST CZY PRZETASOWANO KARTY
		}
	}
}


//***************************************************************************************************************************************************************************
//SHUFFLE EXISTING CARD IN THE 24 CARDS DECK.

void Run::shuffle_cards()
{
	srand(time(NULL));
	int fate[24];

	for (int i = 0; i < 24; i++)
	{

		fate[i] = rand() % 24;
		deck_2[i] = &deck_1[fate[i]];
		for (int j = 0; j < i; j++)
		{

			if (fate[i] == fate[j])
			{
				i--;
				j = i;

			}

		}
	}
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

short Run::which_gametype()
{
	for (int i = 0; i < 3; i++)
	{
		set_game_type(players[i].choice_game_type(warsow));
		if (get_game_type() == 5)
		{
			switch (warsow)
			{
			case NULL:
				warsow++;
				cout << players[i].get_name() << " - Warszawa!\n\n";
				break;

			case 1:
				cout << players[i].get_name() << " - Z Warszawa!\n\n";
				break;

			case 2:
				cout << players[i].get_name() << " - Z Kontra-Warszawa\n\n";
				break;

			default:
				cout << "Blad w switchu 1 w run.cpp" << endl << endl;
				break;
			}

			system("Pause");
			system("ClS");

		}
		else if (get_game_type() == 6)
		{
			switch (warsow)
			{

			case 1:
				cout << players[i].get_name() << " - Kontra-Warszawa!\n\n";
				break;

			case 2:
				cout << players[i].get_name() << " - Rekontra-Warszawa!\n\n";
				break;

			default:
				cout << "Blad w switchu 2 w run.cpp" << endl << endl;
				system("Pause");
				exit(0);

			}

			system("Pause");
			system("ClS");
			which_player = i;
			warsow++;
			break;
		}
		else if (get_game_type() == 1 || get_game_type() == 2 || get_game_type() == 3 || get_game_type() == 4)
		{
			which_player = i;
			cout << "Gracz " << players[i].get_name() << " obral kolor! ";
			break;
		}
		
	}

	if (get_game_type() == 1 || get_game_type() == 2 || get_game_type() == 3 || get_game_type() == 4)
	{
		if (players[which_player].ask_or_not() == true)
		{	
			short second_option = NULL;
			extern short contra_counter;
			do
			{
				second_option = players[(which_player + 1) % 3].other_player_asked(get_game_type_pointer(), contra_counter);
				check_if(second_option, ((which_player + 1) % 3) , contra_counter);
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









	return get_game_type();
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

