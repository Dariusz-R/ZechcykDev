#include "Game_Colour.h"

using namespace std ;

void Game_Colour::set_trumph(short &trumph)
{
	this -> trumph = trumph;
}

short Game_Colour::get_trumph()
{
	return trumph;
}


void Game_Colour::share_players(Player players_game_warsow_function[])
{
	players_game_colour[0] = players_game_warsow_function[0]; 
	players_game_colour[1] = players_game_warsow_function[1];
	players_game_colour[2] = players_game_warsow_function[2];
}

short Game_Colour::compare(short& a, short& b, short& c, short trumph)
{
	bool if_trumph = NULL, normal_check = false;

	for (short i = 0; i < 3; i++)
	{
		if (thrown[i].colour == trumph)
			if_trumph += i;
	}
	if (if_trumph != 0 && if_trumph != (a + b + c))
	{
		if (if_trumph == a)
			return a;
		else if (if_trumph == b)
			return b;
		else if (if_trumph == c)
			return c;
		else if (if_trumph == (a + b))
		{
			if (thrown[a].value > thrown[b].value)
				return a;
			else return b;
		}
		else if (if_trumph == (a + c))
		{
			if (thrown[a].value > thrown[c].value)
				return a;
			else return c;
		}
		else if (if_trumph == (b + c))
		{
			if (thrown[b].value > thrown[b].value)
				return b;
			else return c;
		}
	
	}
	else
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

}

short Game_Colour::take_and_compare(short init)
{
	short which_won = NULL, subsum = NULL, a = init % 3, b = (init + 1) % 3, c = (init + 2) % 3;
	thrown[a] = players_game_colour[a].which_card_you_throw( 0, get_trumph());
	system("CLS");
	thrown[ b ] = players_game_colour[b].which_card_you_throw( 1, thrown[a], players_game_colour[a].name, get_trumph());
	system("CLS");
	thrown[c] = players_game_colour[c].which_card_you_throw( 2, thrown[a], thrown[b], players_game_colour[a].name, get_trumph());
	system("CLS");
	which_won = compare(a,b,c, trumph);
	subsum = thrown[0].value + thrown[1].value + thrown[2].value;
	players_points[which_won] = players_points[which_won] + subsum ;
	cout << "Rozpoczal " << players_game_colour[a].name << ". Rzucono: " << thrown[a].symbol << "\t" << thrown[b].symbol << "\t" << thrown[c].symbol << endl;
	cout << "Sztych zdobyl gracz " << players_game_colour[which_won].name << " i zdobyl " << subsum << "pkt.\n";
	system("PAUSE");
	system("CLS");

	for (short i = 0; i < 3; i++)
		players_game_colour[i].destroy_thrown_card();
	
	return which_won;
}

short Game_Colour::who_won()
{
	short who = NULL, who2 = NULL;
	who = (players_points[0] > players_points[1]) ? 0 : 1;
	who2 = (players_points[who] > players_points[2]) ? who : 2;
	return who2;
}