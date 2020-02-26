#ifndef AUCTION
#define AUCTION

#include "Player.h"

class Auction
{
	short const PLAYER_WHO_HAS_STARTED_THE_AUCTION;

	// PRIVATE DATA MEMBERS
	short player_choice;
	void sort_players_cards(short);
	short auction_counter;
	static short* game_type_auct;
	short  player_with_initiative;
	static std::vector <std::string> auction_log;
	short log_counter;
	Player* players_auct[3];
	short agree_to_play_on_current_terms;

	enum {
		NO_DOUBLE = 1,
		DOUBLE_THE_STAKE,
		DURH,
		MISERY,
		FIVE_OPTIONS_TO_CHOSE,
		SIX_OPTIONS_TO_CHOSE,
		NUMBER_OF_PLAYERS = 3,
		FIRST_FOUR,
		HEARTS = 1,
		TILES,
		PIKES,
		CLOVERS,
		WARSOW,
		DOUBLE_THE_WARSOW_STAKE,
		ALL_CARDS_IN_HAND = 8,
		ALL_CARDS_FOR_MISERY

	};

	//PUBLIC METHODS ORDERED BY THE SEQUENCE OF THE APPLICATION
public:
	Auction(Player*, short*, short &);
	void reset_private_variables();
	std::string first_auction_player_see_four_cards();
			short player_after_player_with_initiative(short);
			void auction_log_update(short, short, short = 100);
			static void read_auction_log(bool);
	bool player_see_eight_cards_decision_play_or_resign();
	void players_see_eight_cards_decision_contra_misery_durh();
	short get_auction_counter();
	short get_player_with_initiative();
	void player_picked_colour(short);

	
	
	
	// PRIVATE METHODS
private:
	
	void contra(short&);

	short subfunction(short);
	void breaking_colour_by_durh_or_misery(short&);
	
	
};


#endif 


