#ifndef GAME_WARSOW
#define GAME_WARSOW

#include "Player.h"	
#include "Game.h"
//#include "Card.h"




class GameWarsow :public Game
{
public:
	GameWarsow(Player*);
	short const & player_who_begins_the_game;
	short & player_who_lost_warsow;

	void sum_up_and_give_trick_points_to_player_who_won_trick();
	bool checking_the_condition_which_depends_from_gametype(short);
	void game_log_update(short, short = 1);
	short who_has_the_most_points();
	short sum_of_points_from_current_trick;
	void show_info_about_game();
	void distribute_game_points();
};

#endif