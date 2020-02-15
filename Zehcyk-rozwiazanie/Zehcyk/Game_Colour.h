#ifndef GAME_COLOUR
#define GAME_COLOUR


#include "Player.h"	



using namespace std ;

class Game_Colour
{
	short trumph;
public:
	Card thrown[3];
	Player players_game_colour[3];
	short players_points[3] = { NULL };
	
	


	//void share_players(Player[]);
	//short compare(short&, short&, short&, short);
	//short take_and_compare(short);
	//short who_won();
	//void set_trumph(short&);
	//short get_trumph();






};
#endif