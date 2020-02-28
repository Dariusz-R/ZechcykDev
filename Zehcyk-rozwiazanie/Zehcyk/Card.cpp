//#ifndef CARD
//#define CARD

#include <iostream>
#include "Card.h"



short Card::card_counter = 0;
char Card::symbol_pattern[6] = { '9', 'J', 'D', 'K', '1', 'A' };
char Card::colour_pattern[4] = { '\3', '\4', '\6', '\5' };
short colour;

Card::Card() {

	colour = (((card_counter - (card_counter % 6)) / 6 ) + 1);

	symbol[0] = colour_pattern[(card_counter - (card_counter % 6))/6];
	symbol[1] = ' ';
	symbol[2] = symbol_pattern[card_counter % 6];
	symbol[3] = symbol[2] == '1' ? '0' : ' ';
	symbol[4] = 0;
	card_counter++;
}


//#endif




