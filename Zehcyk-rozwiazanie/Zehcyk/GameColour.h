#ifndef GAME_COLOUR
#define GAME_COLOUR

#include "Player.h"	
#include "Game.h"
//#include "Card.h"



class GameColour :public Game
{
	short const player_who_chose_colour;
	short const trump;
public:
	GameColour(Player*, short);
	enum {
		DID_NOT_MELD,
		MELD_IN_OTHER_THAN_TRUMP_COLOUR = 20,
		MELD_IN_TRUMP_COLOUR = 40,
		NUMBER_OF_POINTS_FOR_MELD_IN_TRUMP_COLOUR = 40,
		NUMBER_OF_POINTS_FOR_MELD_IN_OTHER_COLOUR = 20
	};
	
	short did_player_who_chose_color_meld;
	short did_other_players_meld;
	short & was_colour_successful;
	bool did_player_who_picked_a_colour_won_a_trick;
	bool did_other_players_won_a_trick;
	
	bool checking_the_condition_which_depends_from_gametype(short i);
	void sum_up_and_give_trick_points_to_player_who_won_trick();
	void show_info_about_game();
	//void game_log_update(short, short = 1);
	short sum_of_points_from_current_trick;
	std::vector <short> what_player_can_throw(short);
	short compare_two_cards(short, short);
	void player_throws_card_then_it_is_evaluated(short id_player);
	void add_points_if_meld();
	bool does_player_meld();
	void note_who_meld(short);
	void distribute_game_points();
	void basic_stake_modification();
};

#endif