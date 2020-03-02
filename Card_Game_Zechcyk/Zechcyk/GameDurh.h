#ifndef GAME_DURH
#define GAME_DURH


#include "Game.h"



class GameDurh : public Game {

	// MEMBER DATA
	enum {
		 BASE_STAKE_FOR_DURH = 8
	};

public:
	short const player_who_chose_durh;
	short& was_durh_successful;
	GameDurh(Player*);
	void show_info_about_game();
	void game_log_update(short, short = 1);
	bool checking_the_condition_which_depends_from_gametype(short);

	
	


};

#endif