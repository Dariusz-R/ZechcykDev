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
	
	string temp_string, temp_string_2;

	Player* players_auct[3];
	
public:
	void contra(short&);
	void history_actualization(short, short, short = 100);
	string read_auction_log();
	void set_game_type_auct(short);
	short get_game_type_auct();
	void reset_game_type_auct();
	void set_temp_string(string);
	string get_temp_string();
	void reset_temp_string();
	void set_temp_string_2(string);
	string get_temp_string_2();
	void reset_temp_string_2();
	void set_player_with_initiative(short);
	short get_player_with_initiative();
	void reset_player_with_initiative();
	short game_type_auction_four_cards();
	short game_type_auction_eight_cards();
	void share_players(Player*);
	bool ask_or_not();
	//short which_gametype();
	short get_auction_counter();
	void increment_auction_counter();
	void reset_auction_counter();

	
};


#endif 


