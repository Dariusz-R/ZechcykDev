#ifndef GAME_WARSOW
#define GAME_WARSOW

#include "Player.h"	
#include "Game.h"
//#include "Card.h"


using namespace std ;

class Game_Warsow :public Game
{
public:
	Game_Warsow(Player*, short);
	void play_warsow(short);
	
	
	
	short play_trick();
	void game_log_actualization(short, short = 1);
	short who_has_the_most_points();
	short sum_of_points_from_current_trick;
};

#endif