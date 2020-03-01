#include "Auction.h"
#include <iostream>
#include "Text.h"
#include <stdlib.h>
#include <iomanip>
#include <vector>


short* Auction::pGameTypeAuction;
std::vector <std::string> Auction::auctionLog = {};


Auction::Auction(Player* players_adress, short* game_type_in_Run_class, short &player_who_has_started_the_auction)
	: PLAYER_WHO_HAS_STARTED_THE_AUCTION(player_who_has_started_the_auction)
{
	auctionCounter = 0;
	agreeToPlayOnCurrentTerms = 0;
	gameLeader = PLAYER_WHO_HAS_STARTED_THE_AUCTION;
	
	playerChoice = 0;
	pGameTypeAuction = game_type_in_Run_class;

	pPlayers[0] = &players_adress[0];
	pPlayers[1] = &players_adress[1];
	pPlayers[2] = &players_adress[2];
}

short Auction::getGameLeader() {
	return gameLeader;
}

void Auction::resetPrivateVariables() {
	auctionCounter = 0;
	gameLeader = 0;
	auctionLog.clear();
	
}


void Auction::changeIncomingGameRules(short which_player) {
	updateAuctionLog(which_player, 5 + playerChoice);
	gameLeader = which_player;
	auctionCounter = 0;
	*pGameTypeAuction = playerChoice;
}


std::string Auction::carryFirstAuction()
{
	short how_many_options_to_chose = 0;
	
	auctionCounter = 0;
	playerChoice = 0;
	sortPlayersCards(FIRST_FOUR);
	

	for (short i = 0; i < NUMBER_OF_PLAYERS; i++) {
		do {
			how_many_options_to_chose = auctionCounter > 0 ? 6 : 5;
			Text::show_first_auction_menu(pPlayers[i], auctionCounter);
			std::cin >> playerChoice;
			Text::cinCheck(playerChoice, how_many_options_to_chose);
			system("CLS");
		} while (playerChoice == 0);


		if (playerChoice == HEARTS || playerChoice == TILES || playerChoice == PIKES || playerChoice == CLOVERS) {
			changeIncomingGameRules(i);
			sortPlayersCards(ALL_CARDS_IN_HAND);
			return "COLOUR";
		} else if (playerChoice == WARSOW) {
			updateAuctionLog(i, auctionCounter);
			if (auctionCounter == 0) 
				doubleTheStakeForWarsowAndChangeGameLeader(i);
		} else if (playerChoice == DOUBLE_THE_WARSOW_STAKE) {
			updateAuctionLog(i, 3 + auctionCounter);
			doubleTheStakeForWarsowAndChangeGameLeader(i);
		}
	}
	sortPlayersCards(ALL_CARDS_IN_HAND);
	*pGameTypeAuction = playerChoice;
	return "WARSOW";
}

void Auction::sortPlayersCards(short how_many_cards_to_sort) {
	for (short i = 0; i < NUMBER_OF_PLAYERS; i++)
		pPlayers[i]->sortCards(how_many_cards_to_sort);
}

short Auction::getPlayerTurnsSequence(short whoseTurn) {
	return ((gameLeader + whoseTurn) % 3);
}



void Auction::updateAuctionLog(short who, short information, short additionalInformation)
{
	std::string log_line = Text::one_line_frame + "\t" + pPlayers[who]->getName() + " --> " + Text::log_message[information];
	if (additionalInformation != 100)
		log_line.append(Text::log_message[additionalInformation]);
	auctionLog.push_back(log_line);
}



void Auction::displayAuctionLog(bool all) {

	if (all == true) {
		short variable = auctionLog.size();
		for (short i = (variable - 7) ; i < variable; i++) {
			if (i >= 0)
				std::cout << auctionLog[i] << std::endl;
			else
				std::cout << Text::one_line_frame << std::endl;
		}
	}
	else {
			std::cout << auctionLog.back() << std::endl;
	}
}



bool Auction::confirmThatGameLeaderWantToPlayAfterHeSawAllHisCards()
{
	short decision = 0;

	do
	{
		system("CLS");
		Text::readText(Text::log_frames, 0, 1);
		displayAuctionLog(true);
		pPlayers[gameLeader]->show(8, "AUCTION");
		Text::readText(Text::A_8, 0, 1);
		std::cin >> decision;
		Text::cinCheck(decision, 2);
		system("CLS");

		if (decision == 1) {
			updateAuctionLog(gameLeader, 9, 5 + *pGameTypeAuction);
			auctionCounter++;
			return true;
		}
		else if (decision == 2) {
			system("CLS");
			Text::readText(Text::log_message, 17, 1);
			std::cout << pPlayers[gameLeader]->getName();
			Text::readText(Text::log_message, 18, 1);
			for (short i = 0; i < 3; i++) {
				pPlayers[i]->throwOutAllRemainInHandCards();
			}
			return false;
		}
	} while (decision != 1 && decision != 2);
}



void Auction::carrySecondAuction()
{
	short wasAgreementMade = false;

	short i = 1;
	do {

		switch (subfunction(getPlayerTurnsSequence(i)))
		{
		case NO_DOUBLE:
			agreeToPlayOnCurrentTerms++;
			updateAuctionLog(getPlayerTurnsSequence(i), 18);
			if (agreeToPlayOnCurrentTerms == 2 || (agreeToPlayOnCurrentTerms == 1 && gameLeader == getPlayerTurnsSequence(i))) {
				system("pause");
				system("CLS");
				wasAgreementMade = true;
			}
			i++;
			break;
		case DOUBLE_THE_STAKE:
			if (*pGameTypeAuction == 7 || *pGameTypeAuction == 8)
				updateAuctionLog(getPlayerTurnsSequence(i), 9 + auctionCounter, 9 + *pGameTypeAuction);
			else updateAuctionLog(getPlayerTurnsSequence(i), 9 + auctionCounter, 5 + *pGameTypeAuction);
			auctionCounter++;
			agreeToPlayOnCurrentTerms = 0;
			if (i == 0) {
				i = 1;
			}
			else i = 0;
			break;
		case DURH:
			updateAuctionLog(getPlayerTurnsSequence(i), 16);
			changeGameRulesForMiseryOrDurh(i);
			*pGameTypeAuction = 7;
			break;
		case MISERY:
			updateAuctionLog(getPlayerTurnsSequence(i), 17);
			changeGameRulesForMiseryOrDurh(i);
			sortPlayersCards(ALL_CARDS_FOR_MISERY);
			*pGameTypeAuction = 8;
			break;
		}
	} while (auctionCounter < 6 && wasAgreementMade == false);
}

short Auction::getAuctionCounter() {
	return auctionCounter;
}

//PRIVATE METHODS************************************************************************************************************************************

void Auction::doubleTheStakeForWarsowAndChangeGameLeader(short& who) {
	gameLeader = who;
	auctionCounter++;
}



short Auction::subfunction(short who) {
	short choice = 0;
	short howManyOptions = 0;

	do {
		system("CLS");
		std::cout << Text::frames[1];
		displayAuctionLog(true);
		pPlayers[who]->show(8, "AUCTION");
		std::cout << Text::frames[6];
	
		std::cout << Text::auction_text[5];
		switch (auctionCounter) {
		case 1:
			std::cout << Text::auction_text[6];
			break;
		case 2:
			std::cout << Text::auction_text[7];
			break;
		case 3:
			std::cout << Text::auction_text[8];
			break;
		case 4:
			std::cout << Text::auction_text[9];
			break;
		case 5:
			std::cout << Text::auction_text[10];
			break;
		default:
			std::cout << "Bledna wartosc auction_counter" << std::endl;
			system("pause");
			break;
		}
		if (*pGameTypeAuction != 7 && *pGameTypeAuction != 8) {
			std::cout << Text::auction_text[11];
			std::cout << Text::auction_text[12];
			howManyOptions = 4;
		}
		else if (*pGameTypeAuction != 7) {
			std::cout << Text::auction_text[11];
			howManyOptions = 3;
		}
		else howManyOptions = 2;
		std::cout << Text::frames[9];
		std::cout << Text::frames[10];
		std::cin >> choice;
		Text::cinCheck(choice, howManyOptions);
	} while (choice == 0);
	return choice;
}



void Auction::changeGameRulesForMiseryOrDurh(short& who) {

	gameLeader = getPlayerTurnsSequence(who);
	agreeToPlayOnCurrentTerms = 0;
	auctionCounter = 1;
	who = 1;
}