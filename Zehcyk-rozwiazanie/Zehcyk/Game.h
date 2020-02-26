#ifndef GAME
#define GAME

#include <iostream>
#include "Player.h"



class Game
{

	static std::string current_trick_log;
	// MEMBER VARIABLES
protected:
	
	Card const* thrown[3];
	Player* players_pointer[3];
	short values_of_thrown_cards[3];

	short player_with_initiative;
	short variable_replaced_by_reference;
	short who_is_winning_trick;
	short player_who_won_the_trick;

	static std::vector <std::string> game_log;
	static std::vector <std::string> trick_log;

	short basic_stake; 

	enum {
		ANY_OF_PLAYERS = 4,
		NUMBER_OF_PLAYERS = 3,
		NUMBER_OF_CARDS_IN_PLAYER_HAND_BEFORE_THROWING = 8,
		NO_ANSWER_YET = 2
	};

private:

	static short important_player;
	static short game_points_multiplier;

	//METHODS
public:
	void play_game();
	static void read_trick_log();
	static void read_game_log();

	static void set_important_player(short);
	static short get_important_player();
	static short & get_important_player_adress();

	static void set_game_points_multiplier(short);
	static short get_game_points_multiplier();
	
protected: // ORDERED CHRONLOGICALLY

  //void play_game(short); 
  //{
		short play_trick();
		//{
			short queue_of_throwing(short);
			void player_throws_card_then_it_is_evaluated(short id_player);
			//{
				virtual std::vector <short> what_player_can_throw(short);
				void trick_log_update(short who);
				virtual void card_evaluation(Card const*, short&);
			//}
			virtual short compare_two_cards(short, short);
			virtual void sum_up_and_give_trick_points_to_player_who_won_trick();
			virtual void game_log_update(short, short = 1);
			void remove_thrown_cards_from_players_hands();
		//}
		virtual bool checking_the_condition_which_depends_from_gametype(short) = 0;
		virtual void distribute_game_points();
		void clear_players_hands();
		virtual void show_info_about_game() = 0;
  //}
	

};
#endif