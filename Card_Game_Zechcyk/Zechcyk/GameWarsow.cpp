#include "GameWarsow.h"
#include "Run.h"
#include <iomanip>






GameWarsow::GameWarsow(Player* players_adress)
	: player_who_begins_the_game(getGameLeader()),
	player_who_lost_warsow(getGameLeaderAdress())
{
	basicStake = 1;
	thrown[0] = NULL;
	thrown[1] = NULL;
	thrown[2] = NULL;
	playerWithInitiative = player_who_begins_the_game;
	players_pointer[0] = &players_adress[0];
	players_pointer[1] = &players_adress[1];
	players_pointer[2] = &players_adress[2];
	valuesOfThrownCards[3-1] = { 0 };
	sum_of_points_from_current_trick = 0;
	
}

bool GameWarsow::checking_the_condition_which_depends_from_gametype(short i) {
	if (players_pointer[playerWithInitiative]->getTrickPoints() > 60) {
		player_who_lost_warsow = playerWithInitiative;
		return false;
	}
	else if (i = NUMBER_OF_CARDS_IN_PLAYER_HAND_BEFORE_THROWING - 1 && variableReplacedByReference == ANY_OF_PLAYERS) {
		player_who_lost_warsow = who_has_the_most_points();
	}
	return true;
}

void GameWarsow::show_info_about_game() {
	std::cout << "Warszawe przegral " << players_pointer[player_who_lost_warsow]->getName() << std::endl <<
		"PKT SZTYCHOWE " << players_pointer[player_who_lost_warsow]->getTrickPoints() << std::endl
		<< "PKT GRY ktore uzyskali pozostali gracze " << players_pointer[(player_who_lost_warsow + 1) % 3]->getGamePoints();
	system("pause");
}

void GameWarsow::sum_up_and_give_trick_points_to_player_who_won_trick() {
	sum_of_points_from_current_trick = valuesOfThrownCards[0] + valuesOfThrownCards[1] + valuesOfThrownCards[2];
	players_pointer[whoIsWinningTrick]->addTrickPoints(sum_of_points_from_current_trick);
}

void GameWarsow::game_log_update(short who, short situation)
{
	string log_line = "";
	short tab_counter = 0;
	log_line.append("\t*");
	tab_counter++;
	short number_of_spaces = 0;
	if (situation == 1) {

		for (short i = 0; i < NUMBER_OF_PLAYERS; i++) {
			if (thrown[getPlayersTurnsSequence(i)] != NULL) {
				log_line.append("\t");
				tab_counter++;
				log_line.append(players_pointer[getPlayersTurnsSequence(i)]->getName(), 0, 2);
				log_line.append(":  ");
				log_line.append(thrown[getPlayersTurnsSequence(i)]->symbol);
			}

		}

		number_of_spaces = 65 - log_line.size() - tab_counter * 7;
		log_line.append(number_of_spaces, ' ');
	}
	else if (situation == 2) {
		string sum = to_string(sum_of_points_from_current_trick);
		short log_size = Text::game_log_message[0].size() + players_pointer[who]->getName().size()
			+ Text::game_log_message[1].size() + sum.size() + Text::game_log_message[2].size();
		number_of_spaces = (54 - log_size - (54 - log_size) % 2) / 2;

		log_line.append(number_of_spaces, ' ');
		log_line.append(Text::game_log_message[0]);
		log_line.append(players_pointer[who]->getName());
		log_line.append(Text::game_log_message[1]);
		log_line.append(sum);
		log_line.append(Text::game_log_message[2]);
		(sum.size() == 2) ? number_of_spaces++ : number_of_spaces += 2;
		log_line.append(number_of_spaces, ' ');
	}


	log_line.append("*");
	game_log.push_back(log_line);
}


short GameWarsow::who_has_the_most_points()
{
	short who = ANY_OF_PLAYERS;
	who = (	players_pointer[0]->getTrickPoints() > players_pointer[1]->getTrickPoints()) ? 0 : 1;
	who = (players_pointer[who]->getTrickPoints() > players_pointer[2]->getTrickPoints()) ? who : 2;
	return who;
}


void GameWarsow::distribute_game_points() {
		players_pointer[(player_who_lost_warsow + 1) % 3]->addGamePoints(basicStake * 2 ^ (getGamePointsMultiplier() - 1));
		players_pointer[(player_who_lost_warsow + 2) % 3]->addGamePoints(basicStake * 2 ^ (getGamePointsMultiplier() - 1));
	}

















