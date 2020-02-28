#ifndef AUCTION
#define AUCTION

#include "Player.h"

class Auction
{
	short const PLAYER_WHO_HAS_STARTED_THE_AUCTION;

	// PRIVATE DATA MEMBERS
	short playerChoice;
	void sortPlayersCards(short);
	short auctionCounter;
	static short *pGameTypeAuction;
	short  gameLeader;
	static std::vector <std::string> auctionLog;
	Player *pPlayers[3];
	short agreeToPlayOnCurrentTerms;

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
	void resetPrivateVariables();
	std::string carryFirstAuction();
			short getPlayerTurnsSequence(short);
			void updateAuctionLog(short, short, short = 100);
			static void displayAuctionLog(bool);
	bool confirmThatGameLeaderWantToPlayAfterHeSawAllHisCards();
	void carrySecondAuction();
	short getAuctionCounter();
	short getGameLeader();
	void changeIncomingGameRules(short);

	
	
	
	// PRIVATE METHODS
private:
	
	void doubleTheStakeForWarsowAndChangeGameLeader(short&);

	short subfunction(short);
	void changeGameRulesForMiseryOrDurh(short&);
	
	
};


#endif 


