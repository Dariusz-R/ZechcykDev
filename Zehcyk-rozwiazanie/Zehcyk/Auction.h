#ifndef AUCTION
#define AUCTION

#include "Player.h"

class Auction
{

	short auction_counter;
	short game_type_auct;
	short player_with_initiative;
	string auction_log;
	short log_counter;
	Player* players_auct[3];
	short agree_to_play_on_current_terms;
	
public:
	void contra(short&);
	void history_actualization(short, short, short = 100);
	short get_game_type_auct();
	void reset_private_variables();
	short player_after_player_with_initiative(short);



	short get_player_with_initiative();
	short get_auction_counter();
	short subfunction(short);
	void breaking_colour(short& );
	string first_auction_player_see_four_cards(short);
	short players_see_eight_cards_decision_contra_misery_durh();
	Auction(Player*);
	
	bool player_see_eight_cards_decision_play_or_resign();

	
};


#endif 


