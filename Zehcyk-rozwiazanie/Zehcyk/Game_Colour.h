#ifndef GAME_COLOUR
#define GAME_COLOUR

#include "Player.h"	
#include "Game.h"
//#include "Card.h"


using namespace std ;

class Game_Colour :public Game
{
	short const player_who_chose_colour;
	short const trump;
public:
	Game_Colour(Player*, short, short);
	enum {
		DID_NOT_MELD,
		MELD_IN_OTHER_THAN_TRUMP_COLOUR = 20,
		MELD_IN_TRUMP_COLOUR = 40,
		NUMBER_OF_POINTS_FOR_MELD_IN_TRUMP_COLOUR = 40,
		NUMBER_OF_POINTS_FOR_MELD_IN_OTHER_COLOUR = 20
	};
	void play_colour(short);
	short did_player_who_chose_color_meld;
	short did_other_players_meld;
	
	
	
	
	short play_trick();
	void game_log_actualization(short, short = 1);
	short sum_of_points_from_current_trick;
	vector <short> what_player_can_throw(short);
	short compare_two_cards(short, short);
	void player_throws_card_then_it_is_evaluated(short id_player);
	void add_points_if_meld();
	bool does_player_meld();
	void note_who_meld(short);
};

#endif