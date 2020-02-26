#ifndef GAME_MISERY
#define GAME_MISERY


#include "Game.h"



class Game_Misery : public Game {

	// MEMBER DATA
	enum {
		 BASE_STAKE_FOR_MISERY = 6
	};
	short const player_who_chose_misery;
	short & was_misery_successful;
	void show_info_about_game();
	bool checking_the_condition_which_depends_from_gametype(short i);
	

public:
	Game_Misery(Player*);
	void game_log_update(short, short = 1);
	void card_evaluation(Card const* card_to_evaluate, short& conteiner);

	
	


};

#endif