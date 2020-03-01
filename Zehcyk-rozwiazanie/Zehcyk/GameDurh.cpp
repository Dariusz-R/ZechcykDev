
#include <iostream>
#include "GameDurh.h"
#include "Text.h"


GameDurh::GameDurh(Player* players_adress)
	:player_who_chose_durh(getGameLeader()),
	was_durh_successful(variableReplacedByReference)
{
	basicStake = 8;
	thrown[0] = NULL;
	thrown[1] = NULL;
	thrown[2] = NULL;
	variableReplacedByReference = NO_ANSWER_YET;
	gameLeader = player_who_chose_durh;
	players_pointer[0] = &players_adress[0];
	players_pointer[1] = &players_adress[1];
	players_pointer[2] = &players_adress[2];
	valuesOfThrownCards[3-1] = { 0 };
}

bool GameDurh::checking_the_condition_which_depends_from_gametype(short i) {
	if (playTrick() != player_who_chose_durh) {
		was_durh_successful = false;
		return false;
	}
	return true;
}

void GameDurh::show_info_about_game() {
	if (was_durh_successful == false)
		std::cout << "Durha przegral " << players_pointer[player_who_chose_durh]->getName() << std::endl;
	else std::cout << "Durha wygral " << players_pointer[player_who_chose_durh]->getName() << std::endl;
	system("pause");
}





void GameDurh::game_log_update(short who, short situation)
{
	std::string log_line = "";
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
		short log_size = Text::game_log_message[0].size() + players_pointer[who]->getName().size();
		number_of_spaces = (54 - log_size - (54 - log_size) % 2) / 2;

		log_line.append(number_of_spaces, ' ');
		log_line.append(Text::game_log_message[0]);
		log_line.append(players_pointer[who]->getName());
		log_line.append(number_of_spaces, ' ');
	}


	log_line.append("*");
	game_log.push_back(log_line);
}
