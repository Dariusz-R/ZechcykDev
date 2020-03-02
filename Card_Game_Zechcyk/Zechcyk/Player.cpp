#include "Text.h"
#include <iostream>
#include "Player.h"
#include <windows.h>
#include <vector>
//#include <stdlib.h>
//#include <sstream>
#include <string>
#include "Auction.h"
#include <iomanip>
#include "GameWarsow.h"



// METHODS DIVIDED IN THREE PHASES:
// 1 - begining
// 2 - auction
// 3 - game

//INSIDE PHASES  METHODS ORDERED CHRONLOGICALLY


// USED IN PHASE 1:

Player::Player()
:SORT_LIKE_FOR_MISERY(9)
{
	std::string name = "";
	trickPoints = 0; 
	gamePoints = 0;
	lastThrownCardIterator = 8;
}

void Player::namePlayer(short textLineNumber) {
	std::string nameToPass = "";
	bool incorrectName = true;
	do {
		Text::readText(Text::start_menu, textLineNumber, 1);
		std::getline(std::cin >> std::ws, nameToPass, '\n');
		if (nameToPass.size() < 15)
			incorrectName = false;
		else {
			system("CLS");
			std::cout << std::endl;
			Text::readText(Text::start_menu, 9, 1);
			std::cout << std::endl << std::endl << "                    ";
			system("Pause");
			system("CLS");
		}

	} while (incorrectName == true);
	name.append(nameToPass);
	nameShortcut.append(nameToPass, 0, 2);
}

std::string Player::getName() {
	return name;
}

void Player::takeCardFromTheDeck(const Card* cardToTake) {
	playerCards.push_back(cardToTake);
}

// USED IN PHASE 1 AND 2:

void Player::sortCards(short how_many_cards)
{
	short sort_value[8] = {0,0,0,0,0,0,0,0};
	bool misery = false;

	if ( how_many_cards == SORT_LIKE_FOR_MISERY) {
		how_many_cards = 8;
		misery = true;
	}

	for (short i = 0; i < how_many_cards; i++) {
		switch (playerCards[i]->colour) {
		case 1:
			break;
		case 2:
			sort_value[i] += 20;
			break;
		case 3:
			sort_value[i] += 40;
			break;
		case 4:
			sort_value[i] += 60;
			break;
		default:
			std::cout << "BLAD SORTOWANIA" << std::endl << std::endl;
			break;
		}
		switch (playerCards[i]->symbol[2]) {
		case '9':
			break;
		case 'J':
			sort_value[i] += 2;
			break;
		case 'D':
			sort_value[i] += 3;
			break;
		case 'K':
			sort_value[i] += 4;
			break;
		case '1':
			if (misery == true) sort_value[i] += 1;
			else sort_value[i] += 5;
			break;
		case 'A':
			sort_value[i] += 6;
			break;
		default:
			std::cout << "BLAD2 PODCZAS SORTOWANIA" << std::endl << std::endl;
			break;
		}
	}

	bool swapped;

	for (short i = 0; i < how_many_cards - 1; i++)
	{
		swapped = false;
		for (short j = 0; j < how_many_cards - i - 1; j++)
		{
			if (sort_value[j] > sort_value[j + 1])
			{
				std::swap(sort_value[j], sort_value[j + 1]);
				std::swap(playerCards[j], playerCards[j + 1]);
				swapped = true;
			}
		}
		if (swapped == false)
			break;
	}
}

// USED IN PHASE 2 AND 3:

void Player::show(short how_many, std::string when)
{

	std::cout << "\t\t\t\t\t\t\t\t*\r\t*";
	std::cout << std::setw(27 + name.size() / 2) << name << std::endl;
	std::cout << Text::frames[0] << Text::frames[5];
	std::cout << "\t\t\t\t\t\t\t\t*\r\t*     ";

	for (short i = 0; i < 8; i++) {
		if (i < how_many)
			std::cout << playerCards[i]->symbol << "  ";
		else std::cout << "      ";
	}
	std::cout << std::endl;
	
	 if (when == "GAME"){
		std::cout << "\t\t\t\t\t\t\t\t*\r\t*      ";
		for (short i = 0; i < 8; i++)
		{
			i < how_many ? std::cout << i + 1 << "     " : std::cout << "      ";
		}
		std::cout << std::endl;
	 }
	 std::cout << Text::frames[9];

}

void Player::throwOutAllRemainInHandCards() {
	playerCards.clear();
}

void Player::addGamePoints(short points) {
	gamePoints += points;
}

short Player::getGamePoints() {
	return gamePoints;
}

// USED IN PHASE 3:

Card const* Player::whichCardPlayerThrow(std::vector<short> whatMayIThrow)
{
	if (playerCards.size() != 1)
	{

		do
		{
			lastThrownCardIterator = 0;
			Text::showGame(this, whatMayIThrow);
			std::cin >> lastThrownCardIterator;
			lastThrownCardIterator--;
			Text::cinCheck(lastThrownCardIterator, playerCards.size(), whatMayIThrow);
			system("CLS");
		} while (lastThrownCardIterator == -1);
		return playerCards[lastThrownCardIterator];
	}
	else
	{
		show(playerCards.size(), "GAME");
		std::cout << "Ostatnia Twoja karta zostanie rzucona\n\n";
		system("PAUSE");
		return playerCards[0];
	}
}

void Player::showMeWhatICanThrow(std::vector<short> whatMayPlayerThrow)
{
	if (whatMayPlayerThrow.empty()) {
		std::cout << Text::frames[7];
	}
	else {
		std::string whatMayIThrowTextForPlayer = "";
		for (short i = 0; i < whatMayPlayerThrow.size(); i++) {
			whatMayIThrowTextForPlayer.append("   ");
			whatMayIThrowTextForPlayer.append(std::to_string(whatMayPlayerThrow[i]+1));
		}

		std::cout << Text::frames[8];
		std::cout << "\t\t\t\t\t\t\t\t*\r\t*";
		if (whatMayPlayerThrow.size() % 2 == 1)
			std::cout << std::setw(27 + 4 * (whatMayPlayerThrow.size() / 2)) << whatMayIThrowTextForPlayer << std::endl;
		else {
			std::cout << std::setw(25 + 2 * whatMayPlayerThrow.size()) << whatMayIThrowTextForPlayer << std::endl;
		}
		std::cout << Text::frames[0];
	}
}

std::vector <short> Player::checkHowManyCardsInThrownCardColourPlayerHave(short colour) {
	std::vector <short> iterators_of_cards_in_colour = {};
	for (short i = 0; i < playerCards.size(); i++) {
		if (playerCards[i]->colour == colour) {
			iterators_of_cards_in_colour.push_back(i);
		}
	}
	return iterators_of_cards_in_colour;
}

Card const* Player::shareCard(short i) {
	return playerCards[i];
}

bool Player::checkIfPlayerHaveAKingAndQueenInOneColour() {
	if (playerCards[lastThrownCardIterator]->symbol[2] == 'D' && (lastThrownCardIterator + 1) < playerCards.size()) {
		if (playerCards[lastThrownCardIterator + 1]->symbol[2] == 'K' && playerCards[lastThrownCardIterator]->colour == playerCards[lastThrownCardIterator + 1]->colour)
			return true;
	}
	else if (playerCards[lastThrownCardIterator]->symbol[2] == 'K' && (lastThrownCardIterator - 1) > 0) {
		if (playerCards[lastThrownCardIterator - 1]->symbol[2] == 'D' && playerCards[lastThrownCardIterator]->colour == playerCards[lastThrownCardIterator - 1]->colour)
			return true;
	}
	return false;
}

bool Player::askPlayerIfHeWantToMeld() {

	system("CLS");
	short yes_or_no = 3;
	std::cout << " CHcesz zameldowac?" << std::endl;
	std::cin >> yes_or_no;
	Text::cinCheck(yes_or_no, 2);

	if (yes_or_no == 2)
		return false;
	if (yes_or_no == 1)
		return true;
}

void Player::addTrickPoints(short points) {
	trickPoints += points;
}

short Player::getTrickPoints() {
	return trickPoints;
}

std::string Player::getNameShortcut() {
	return nameShortcut;
}

void Player::resetTrickPoints() {
	trickPoints = NULL;
}

void Player::eraseThrownCardFromPlayerHand()
{
	playerCards.erase(playerCards.begin() + lastThrownCardIterator);
}





















