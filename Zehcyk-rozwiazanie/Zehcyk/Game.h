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
	short valuesOfThrownCards[3];

	short gameLeader;
	short variableReplacedByReference;
	short whoIsWinningTrick;
	short playerWhoWonTheTrick;

	static std::vector <std::string> game_log;
	static std::vector <std::string> trick_log;

	short basicStake; 

	enum {
		ANY_OF_PLAYERS = 4,
		NUMBER_OF_PLAYERS = 3,
		NUMBER_OF_CARDS_IN_PLAYER_HAND_BEFORE_THROWING = 8,
		NO_ANSWER_YET = 2
	};

private:

	static short gameLeader;
	static short gamePointsMultiplier;

	//METHODS
public:
	void playGame();
	static void read_trick_log();
	static void read_game_log();

	static void setGameLeader(short);
	static short getGameLeader();
	static short & getGameLeaderAdress();

	static void setGamePointsMultiplier(short);
	static short getGamePointsMultiplier();
	
protected: // ORDERED CHRONLOGICALLY

  //void play_game(short); 
  //{
		short playTrick();
		//{
			short getPlayersTurnsSequence(short);
			void runThrowingCardMechanism(short id_player);
			//{
				virtual std::vector <short> checkWhichOfHisCardsPlayerCanThrow(short);
				void updateTrickLog(short who);
				virtual void EvaluateCard(Card const*, short&);
			//}
			virtual short compareTwoCards(short, short);
			virtual void sumPointsAndGiveThemToTheNewGameLeader();
			virtual void updateGameLog(short, short = 1);
			void removeThrownCardsFromPlayersHands();
		//}
		virtual bool checking_the_condition_which_depends_from_gametype(short) = 0;
		virtual void distribute_game_points();
		void clear_players_hands();
		virtual void show_info_about_game() = 0;
  //}
	

};
#endif