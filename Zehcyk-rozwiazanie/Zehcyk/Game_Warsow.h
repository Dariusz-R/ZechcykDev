#ifndef GAME_WARSOW
#define GAME_WARSOW

#include "Player.h"	
//#include "Card.h"


using namespace std ;

class Game_Warsow
{

public:
	short const ANY_OF_PLAYERS;
	short const NUMBER_OF_PLAYERS;
	short const NUMBER_OF_CARDS_IN_PLAYER_HAND_BEFORE_THROWING;
	short sum_of_points_from_current_trick;


	Card const *  thrown[3];
	static vector <string> game_log;
	void game_log_actualization(short, short = 1);
	static void read_game_log(short);
	Player* players_game_warsow[3];
	short players_points[3] = { NULL };
	vector < vector < short >> players_cards_values[3][8];
	short values_of_thrown_cards[3];
	short player_with_initiative;
	short which_player_after_player_with_initiative(short);
	void player_throws_card_then_it_is_evaluated(short id_player);
	vector <short> what_player_can_throw(short);
	//Methods:
	Game_Warsow(Player*, short);
	//void share_players(Player[]);
	void card_evaluation(Card const*, short&);
	short compare_two_cards(short, short);
	void play_warsow(short);
	void remove_thrown_cards_from_players_hands();
	
	void play_trick();
	short who_has_the_most_points();
	short who_is_winning_trick;






};

#endif