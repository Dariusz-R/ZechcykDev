#include "Game_Warsow.h"

using namespace std ;

/*
void Game_Warsow::share_players(Player players_game_warsow_function[])
{
	players_game_warsow[0] = players_game_warsow_function[0]; 
	players_game_warsow[1] = players_game_warsow_function[1];
	players_game_warsow[2] = players_game_warsow_function[2];
}

short Game_Warsow::compare(short& a, short& b, short& c)
{

	if (thrown[a].colour == thrown[b].colour)
	{
		if (thrown[a].value > thrown[b].value)
		{
			if (thrown[a].colour == thrown[c].colour)
			{
				if (thrown[a].value > thrown[c].value)
				{
					return a;
				}
				else return c;
			}
			else return a;
		}
		else if (thrown[b].colour == thrown[c].colour)
		{
			if (thrown[b].value > thrown[c].value)
			{
				return  b;
			}
			else return c;
		}
		else return b;
	}
	else if (thrown[a].colour == thrown[c].colour)
	{
		if (thrown[a].value > thrown[c].value)
		{
			return a;
		}
		else return c;
	}
	else return a;

}

short Game_Warsow::take_and_compare(short init)
{
	short which_won = NULL, subsum = NULL, a = init % 3, b = (init + 1) % 3, c = (init + 2) % 3;
	thrown[a] = players_game_warsow[a].which_card_you_throw(0);
	system("CLS");
	thrown[ b ] = players_game_warsow[b].which_card_you_throw(1, thrown[a], players_game_warsow[a].get_name());
	system("CLS");
	thrown[c] = players_game_warsow[c].which_card_you_throw(2, thrown[a], thrown[b], players_game_warsow[a].get_name());
	system("CLS");
	which_won = compare(a,b,c);
	subsum = thrown[0].value + thrown[1].value + thrown[2].value;
	players_points[which_won] = players_points[which_won] + subsum ;
	cout << "Rozpoczal " << players_game_warsow[a].get_name() << ".\n Rzucono: " << thrown[a].symbol << "\t" << thrown[b].symbol << "\t" << thrown[c].symbol << endl;
	cout << "Sztych zdobyl gracz " << players_game_warsow[which_won].get_name()<< " i zdobyl " << subsum << "pkt.\n";
	system("PAUSE");
	system("CLS");

	for (short i = 0; i < 3; i++)
		players_game_warsow[i].destroy_thrown_card();
	
	return which_won;
}

short Game_Warsow::who_won()
{
	short who = NULL, who2 = NULL;
	who = (players_points[0] > players_points[1]) ? 0 : 1;
	who2 = (players_points[who] > players_points[2]) ? who : 2;
	return who2;
}*/