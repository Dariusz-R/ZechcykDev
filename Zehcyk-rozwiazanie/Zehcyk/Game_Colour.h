#ifndef GAME_COLOUR
#define GAME_COLOUR


#include "Player.h"	



using namespace std ;

class Game_Colour
{
public:
	Card thrown[3];
	Player players_game_colour[3];
	short players_points[3] = { NULL };
	

	//Methods:
	//Game_Warsow();
	void share_players(Player[]);
	short compare(short&, short&, short&);
	short take_and_compare(short);
	short who_won();






};
#endif