#ifndef AUCTION
#define AUCTION

#include "Player.h"

class Auction
{
	// PRIVATE DATA MEMBERS
	short auction_counter;
	short* game_type_auct;
	static short player_with_initiative;
	vector <string> auction_log;
	short log_counter;
	Player* players_auct[3];
	short agree_to_play_on_current_terms;

	//PUBLIC METHODS ORDERED BY THE SEQUENCE OF THE APPLICATION
public:
	Auction(Player*, short*, short);
	void reset_private_variables();
	string first_auction_player_see_four_cards(short);
			short player_after_player_with_initiative(short);
			void history_actualization(short, short, short = 100);
			void read_auction_log();
	bool player_see_eight_cards_decision_play_or_resign();
	void players_see_eight_cards_decision_contra_misery_durh();
	short get_player_with_initiative();
	short get_auction_counter();
			

	
	
	
	// PRIVATE METHODS
private:
	
	void contra(short&);

	short subfunction(short);
	void breaking_colour(short&);
	
	
};


#endif 


