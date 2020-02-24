#ifndef GAME
#define GAME

#include <iostream>
#include "Player.h"

using namespace std ;

class Game
{	
public:
	static void read_game_log(short);
protected:
	enum {
		ANY_OF_PLAYERS = 4,
		NUMBER_OF_PLAYERS = 3,
		NUMBER_OF_CARDS_IN_PLAYER_HAND_BEFORE_THROWING = 8
	};
	Card const* thrown[3];
	static vector <string> game_log;
	short players_points[3];
	Player* players_pointer[3];
	short values_of_thrown_cards[3];
	short player_with_initiative;
	short who_is_winning_trick;
	virtual void game_log_actualization(short, short = 1) = 0;

	void player_throws_card_then_it_is_evaluated(short id_player);
	void card_evaluation(Card const*, short&);
	short which_player_after_player_with_initiative(short);
	void remove_thrown_cards_from_players_hands();
	virtual vector <short> what_player_can_throw(short);
	
	virtual short compare_two_cards(short, short);

};
#endif