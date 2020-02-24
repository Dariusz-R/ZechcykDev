#ifndef GAME_MISERY
#define GAME_MISERY


#include "Game.h"



class Game_Misery : public Game {

	// MEMBER DATA
	enum {
		 BASE_STAKE_FOR_MISERY = 6
	};
	short const player_who_chose_misery;
	short was_misery_successful;
	
	short play_trick();

public:
	Game_Misery(Player*, short);
	void play_misery(short game_points_multiplier);
	void game_log_actualization(short, short = 1);

	
	


};

#endif