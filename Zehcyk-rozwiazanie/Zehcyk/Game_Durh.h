#ifndef GAME_DURH
#define GAME_DURH


#include "Game.h"



class Game_Durh : public Game {

	// MEMBER DATA
	enum {
		 BASE_STAKE_FOR_DURH = 8
	};
	short const player_who_chose_durh;
	short was_durh_successful;
	
	short play_trick();

public:
	Game_Durh(Player*, short);
	void play_durh(short game_points_multiplier);
	void game_log_actualization(short, short = 1);

	
	


};

#endif