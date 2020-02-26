//#ifndef CARD
//#define CARD

#include <iostream>
#include "Card.h"




char Card::symbol_pattern[6] = { '9', 'J', 'D', 'K', '1', 'A' };
char Card::colour_pattern[4] = { '\3', '\4', '\6', '\5' };
short colour;

Card::Card(short which) {

	colour = (((which - (which % 6)) / 6 ) + 1);

	symbol[0] = colour_pattern[(which - (which % 6))/6];
	symbol[1] = ' ';
	symbol[2] = symbol_pattern[which % 6];
	symbol[3] = symbol[2] == '1' ? '0' : ' ';
	symbol[4] = 0;
}


//#endif




