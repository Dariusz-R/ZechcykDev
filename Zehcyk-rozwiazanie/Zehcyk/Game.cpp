#include <iostream>
#include <string>
#include "Game.h"
#include "Text.h"



short Game::gameLeader;
short Game::gamePointsMultiplier;
std::vector <std::string> Game::game_log;
std::vector <std::string> Game::trick_log;
std::string Game::current_trick_log = "9\r\t\t\t\t\t\t\t\t*\r\t*        ";

// PUBLIC METHODS ORDERED CHRONOLOGICALLY:
void Game::setGameLeader(short which_player) {
	gameLeader = which_player;
}

short Game::getGameLeader() {
	return gameLeader;
}

short& Game::getGameLeaderAdress() {
	return gameLeader;
}

void Game::setGamePointsMultiplier(short which_player) {
	gameLeader = which_player;
}

short Game::getGamePointsMultiplier() {
	return gamePointsMultiplier;
}

void Game::read_trick_log() {

	if (!trick_log.empty())
	{
		std::cout << Text::frames[3];
		std::cout << trick_log.back() << std::endl;
	}
	std::cout << Text::frames[4];
	std::cout << current_trick_log << std::endl;
}

void Game::read_game_log() {

		if (!game_log.empty())
		{
			if (game_log.size() == 1)
				std::cout << std::endl << game_log.end()[-1];
			else {
				std::cout << std::endl << game_log.end()[-2];
				std::cout << std::endl << game_log.end()[-1];
			}
		}
}

void Game::playGame() {
	for (int i = 0; i < NUMBER_OF_CARDS_IN_PLAYER_HAND_BEFORE_THROWING; i++) {
		 playerWhoWonTheTrick = playTrick();
		if (checking_the_condition_which_depends_from_gametype(i) == false)
			break;
	}
	distribute_game_points();
	clear_players_hands();
	show_info_about_game();
}

// PROTECTED METHODS ORDERED CHRONOLOGICALLY:

short Game::playTrick()
{
	whoIsWinningTrick = ANY_OF_PLAYERS;
	thrown[0] = {};
	thrown[1] = {};
	thrown[2] = {};


	runThrowingCardMechanism(gameLeader);
	whoIsWinningTrick = gameLeader;
	runThrowingCardMechanism(getPlayersTurnsSequence(1));
	whoIsWinningTrick = compareTwoCards(gameLeader, getPlayersTurnsSequence(1));
	runThrowingCardMechanism(getPlayersTurnsSequence(2));
	whoIsWinningTrick = compareTwoCards(whoIsWinningTrick, getPlayersTurnsSequence(2));

	sumPointsAndGiveThemToTheNewGameLeader();
	
	updateGameLog(whoIsWinningTrick, 2);
	removeThrownCardsFromPlayersHands();
	gameLeader = whoIsWinningTrick;

	return whoIsWinningTrick;
}

short Game::getPlayersTurnsSequence (short which_after_player_with_initiative) {
	return ((gameLeader + which_after_player_with_initiative) % 3);
}

void Game::runThrowingCardMechanism(short id_player) {
	if (id_player == gameLeader)
		thrown[gameLeader] = players_pointer[gameLeader]->whichCardPlayerThrow();
	else
		thrown[id_player] = players_pointer[id_player]->whichCardPlayerThrow(checkWhichOfHisCardsPlayerCanThrow(id_player));

	updateTrickLog(id_player);
	EvaluateCard(thrown[id_player], valuesOfThrownCards[id_player]);
	system("CLS");
}

void Game::updateTrickLog(short who)
{
		std::string thrown_card_symbol[3];
		for (short i = 0; i < NUMBER_OF_PLAYERS; i++) 
			thrown_card_symbol[i] = (thrown[getPlayersTurnsSequence(i)] == NULL) ? "     " : thrown[getPlayersTurnsSequence(i)]->symbol;

		current_trick_log = "9\r" + Text::one_line_frame + "        "
			+ players_pointer[getPlayersTurnsSequence(0)]->getNameShortcut() + ": " + thrown_card_symbol[0] + "      "
			+ players_pointer[getPlayersTurnsSequence(1)]->getNameShortcut() + ": " + thrown_card_symbol[1] + "      "
			+ players_pointer[getPlayersTurnsSequence(2)]->getNameShortcut() + ": " + thrown_card_symbol[2] ;
		if (thrown_card_symbol[0] != "     " && thrown_card_symbol[1] != "     " && thrown_card_symbol[2] != "     ") {
			current_trick_log[0] = whoIsWinningTrick;
			trick_log.push_back(current_trick_log);
			current_trick_log.clear();
		}
}

std::vector<short> Game::checkWhichOfHisCardsPlayerCanThrow(short id_player) {
	std::vector <short> values_of_the_player_cards_in_colour, player_cards_in_colour, player_cards_winning;
	player_cards_in_colour = players_pointer[id_player]->checkHowManyCardsInThrownCardColourPlayerHave(thrown[gameLeader]->colour);
	if (!player_cards_in_colour.empty()) {

		for (short i = 0; i < player_cards_in_colour.size(); i++) {
			values_of_the_player_cards_in_colour.push_back(0);
			EvaluateCard(players_pointer[id_player]->shareCard(player_cards_in_colour[i]), values_of_the_player_cards_in_colour[i]);
			if (values_of_the_player_cards_in_colour[i] > valuesOfThrownCards[whoIsWinningTrick]) {
				player_cards_winning.push_back(player_cards_in_colour[i]);
			}

		}
		if (!player_cards_winning.empty())
			return player_cards_winning;
		else
			return player_cards_in_colour;
	}
	else
		return {};


}

void Game::EvaluateCard(Card const* card_to_evaluate, short& conteiner) {

	switch (card_to_evaluate->symbol[2]) {
	case '9':
		conteiner = 0;
		break;
	case 'J':
		conteiner = 2;
		break;
	case 'D':
		conteiner = 3;
		break;
	case 'K':
		conteiner = 4;
		break;
	case '1':
		conteiner = 10;
		break;
	case 'A':
		conteiner = 11;
		break;
	default:
		std::cout << "BLEDNE CZYTANIE SYMBOLU PRZY EWALUACJI";
		break;
	}

}

short Game::compareTwoCards(short id_player, short id2_player)
{
	if (thrown[id_player]->colour == thrown[id2_player]->colour) {

		if (valuesOfThrownCards[id_player] < valuesOfThrownCards[id2_player])
			return id2_player;
		else
			return id_player;

	}
	else
		return id_player;
}

void Game::sumPointsAndGiveThemToTheNewGameLeader() {
	;
}

void Game::updateGameLog(short who, short situation) {
	std::string log_line = "";
	log_line = "9\r" + Text::one_line_frame + players_pointer[who]->getName() + Text::game_log_message[0] + Text::game_log_message[1] +
		Text::game_log_message[2];
	game_log.push_back(log_line);
}

void Game::removeThrownCardsFromPlayersHands() {
	for (short i = 0; i < NUMBER_OF_PLAYERS; i++)
		players_pointer[i]->eraseThrownCardFromPlayerHand();
}

void Game::distribute_game_points() {
	if (variableReplacedByReference == true)
		players_pointer[gameLeader]->addGamePoints(basicStake * 2 ^ (gamePointsMultiplier - 1));
	else {
		players_pointer[(gameLeader + 1) %3]->addGamePoints(basicStake * 2 ^ (gamePointsMultiplier - 1));
		players_pointer[(gameLeader + 2) %3]->addGamePoints(basicStake * 2 ^ (gamePointsMultiplier - 1));
	}
}

void Game::clear_players_hands() {
	for (short i = 0; i < NUMBER_OF_PLAYERS; i++)
		players_pointer[i]->throwOutAllRemainInHandCards();
}