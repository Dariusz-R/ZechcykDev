#include <iostream>
#include "Run.h"

using namespace std;



//***************************************************************************************************************************************************************************
// USES FUNION ABOVE AND ASKS IF USER WANT TO PLAY


void Run::start()
{

	short want_to_play = NULL;
	bool loop_choice = NULL;

	do
	{

		showing_txt("Tekst_Menu1.txt");

		cout << "\tTwoja odpowiedz: ";

		cin >> want_to_play;
		loop_choice = false;
		want_to_play = cin_check(want_to_play, "Tekst_Menu1.txt");
	
		switch (want_to_play)
		{

		case 1:
			system("CLS");
			cout << "To gramy!" << endl;
			Sleep(1000);
			loop_choice = true;
			system("CLS");
			break;

		case 2:
			cout << "No to nie gramy! Czesc!" << endl;
			exit(0);
			break;

		case 3: 
			ShellExecute(GetDesktopWindow(), L"open", L"ZECHCYK2.pdf", NULL, NULL, SW_SHOWMAXIMIZED);
			system("CLS");
			break;

		default:
			cout << "Dokonales wyboru, ktorego nie uwzglednia program. Sprobuj ponownie." << endl;
			Sleep(1000);
			system("CLS");
			break;

		}

	} while (loop_choice == false);


}


//***************************************************************************************************************************************************************************
//CREATING PLAYERS (OBJECTS), ASKS THEM TO GIVE THEIR NAMES AND TO CONFIRM THAT THEY WERE PROPERLY ENTERED - SHOWS THEM ON THE SCREEN

Player players[3];

void Run::meet_players()
{
	short number = NULL;

	for (int i = 0; i < 3; i++)
	{
		number = i + 1;
		players[i].name_players(number);
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
	int values[6] = { 0, 2, 3, 4, 10, 11 };
	char symbol[6] = { '9', 'J', 'D', 'K', '1', 'A' };
	char colour[4] = { '\3', '\4', '\6', '\5' };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
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
		which_game = players[i].choice_game_type(warsow);
		if (which_game == 5)
		{
			switch (warsow)
			{
			case NULL:
				warsow++;
				cout << players[i].name << " - Warszawa!\n\n";
				break;

			case 1:
				cout << players[i].name << " - Z Warszawa!\n\n";
				break;

			case 2:
				cout << players[i].name << " - Z Kontra-Warszawa\n\n";
				break;

			default:
				cout << "Blad w switchu 1 w run.cpp" << endl << endl;
				break;
			}

			system("Pause");
			system("ClS");

		}
		else if (which_game == 6)
		{
			switch (warsow)
			{

			case 1:
				cout << players[i].name << " - Kontra-Warszawa!\n\n";

			case 2:
				cout << players[i].name << " - Rekontra-Warszawa!\n\n";

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
		else if (which_game == 1 || which_game == 2 || which_game == 3 || which_game == 4)
		{
			which_player = i;
			which_trumph = which_game;
			cout << "Gracz " << players[i].name << " obral kolor! ";
			break;
		}
		
	}

	if (which_game == 1 || which_game == 2 || which_game == 3 || which_game == 4)
	{
		if (players[which_player].ask_or_not() == true);
		{
			short second_option = NULL;
			extern short contra_counter;
			do
			{
				second_option = players[(which_player + 1) % 3].other_player_asked(which_game, contra_counter);
				check_if(second_option, ((which_player + 1) % 3) , contra_counter);
				if (second_option == 1 && contra_counter < 5)
				{
					second_option = players[(which_player + 2) % 3].other_player_asked(which_game, contra_counter);
					check_if(second_option, ((which_player + 2) % 3), contra_counter);
				}
				if (second_option == 2 && contra_counter < 5)
				{
					second_option = players[which_player % 3].other_player_asked(which_game, contra_counter);
					check_if(second_option, (which_player % 3), contra_counter);
				}
			} while (second_option == 2);
			if (which_game == 7)
			{
				do
				{
					second_option = players[(which_player + 1) % 3].other_player_asked(which_game, contra_counter);
					check_if(second_option, ((which_player + 1) % 3), contra_counter);
					if (second_option == 1 && contra_counter < 5)
					{
						second_option = players[(which_player + 2) % 3].other_player_asked(which_game, contra_counter);
						check_if(second_option, ((which_player + 2) % 3), contra_counter);
					}
					if (second_option == 2 && contra_counter < 5)
					{
						second_option = players[which_player % 3].other_player_asked(which_game, contra_counter);
						check_if(second_option, (which_player % 3), contra_counter);
					}
				} while (second_option == 2);
			}
			if (which_game == 8)
			{
				do
				{
					second_option = players[(which_player + 1) % 3].other_player_asked(which_game, contra_counter);
					check_if(second_option, ((which_player + 1) % 3), contra_counter);
					if (second_option == 1 && contra_counter < 5)
					{
						second_option = players[(which_player + 2) % 3].other_player_asked(which_game, contra_counter);
						check_if(second_option, ((which_player + 2) % 3), contra_counter);
					}
					if (second_option == 2 && contra_counter < 5)
					{
						second_option = players[which_player % 3].other_player_asked(which_game, contra_counter);
						check_if(second_option, (which_player % 3), contra_counter);
					}
				} while (second_option == 2);
			}


		}



	}



	else if (which_game == 5 || which_game == 6)
	{

		switch (warsow)
		{
		case 1:
			cout << "Gramy w Warszawe. Zaczyna gracz " << players[which_player].name << endl << endl;
			break;

		case 2:
			cout << "Gramy w Kontre-Warszawe. Zaczyna gracz " << players[which_player].name << endl << endl;
			break;

		case 3:
			cout << "Gramy w Rekontre-Warszawe. Zaczyna gracz " << players[which_player].name << endl << endl;
			break;

		default:
			cout << "Blad w 3 switchu w run.cpp" << endl << endl;
			break;

		}

	}









	return which_game;
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
		cout << "Przegral gracz " << players[who_lose].name << " uzyskujac " << playing_warsow.players_points[who_lose] << "pkt.\n";
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
		Game_Colour playing_colour;
		playing_colour.share_players(players);
		short initiative = 0;
		for (int i = 0; i < 8; i++)
			initiative = playing_colour.take_and_compare(initiative);
		who_lose = playing_colour.who_won();
		cout << "Przegral gracz " << players[who_lose].name << " uzyskujac " << playing_colour.players_points[who_lose] << "pkt.\n";
		if (warsow == 1)
		{
			cout << "Gracz " << players[who_lose].name << " przegral za 1 punkt meczowy";
		}
		else if (warsow == 2)
		{
			cout << "Gracz " << players[who_lose].name << " przegral za 2 punkty meczowe";
		}
		else if (warsow == 3)
		{
			cout << "Gracz " << players[who_lose].name << " przegral za 4 punkty meczowe";
		}

	}
}

