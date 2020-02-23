#ifndef AUCTION
#define AUCTION

#include "Player.h"

class Auction
{

	short const SIX_OPTIONS_TO_CHOSE, FIVE_OPTIONS_TO_CHOSE;
	short const PLAYER_WHO_HAS_STARTED_THE_AUCTION;
	short const NUMBER_OF_PLAYERS;
	short const HEARTS, TILES, PIKES, CLOVERS;
	short const FIRST_FOUR, ALL_CARDS_IN_HAND, ALL_CARDS_FOR_MISERY;
	short const DOUBLE_THE_STAKE, WARSOW;

	// PRIVATE DATA MEMBERS
	short player_choice;
	void sort_players_cards(short);
	short auction_counter;
	static short* game_type_auct;
	short  player_with_initiative;
	static vector <string> auction_log;
	short log_counter;
	Player* players_auct[3];
	short agree_to_play_on_current_terms;

	//PUBLIC METHODS ORDERED BY THE SEQUENCE OF THE APPLICATION
public:
	Auction(Player*, short*, short &);
	void reset_private_variables();
	string first_auction_player_see_four_cards();
			short player_after_player_with_initiative(short);
			void history_actualization(short, short, short = 100);
			static void read_auction_log(bool = true);
	bool player_see_eight_cards_decision_play_or_resign();
	void players_see_eight_cards_decision_contra_misery_durh();
	short show_first_auction_menu(short);
	short get_auction_counter();
	short get_player_with_initiative();
	void player_picked_colour(short);

	
	
	
	// PRIVATE METHODS
private:
	
	void contra(short&);

	short subfunction(short);
	void breaking_colour(short&);
	
	
};


#endif 


