//#ifndef CARD
//#define CARD

#include <iostream>
#include "Card.h"


using namespace std;

char Card::symbol_pattern[6] = { '9', 'J', 'D', 'K', '1', 'A' };
char Card::colour_pattern[4] = { '\3', '\4', '\6', '\5' };
short colour;

Card::Card(short which) {

	colour = (((which - (which % 6)) / 6 ) + 1);

	symbol[0] = colour_pattern[(which - (which % 6))/6];
	symbol[1] = ' ';
	symbol[2] = symbol_pattern[which % 6];
	if (symbol[2] == '1') { symbol[3] = '0'; }
	else { symbol[3] = ' '; }
	symbol[4] = 0;
}

/*void Card::create_card(short i, char val, char sym, char col, short col2)
{
	if ((i > 23) || (i < 0))
		cout << "Error, cards were not created." << endl;

	symbol[4] = 0;
	symbol[0] = col;
	symbol[1] = ' ';
	symbol[2] = sym;
	if (sym == '1')
		symbol[3] = '0';
	else
		symbol[3] = ' ';

	value = val;
	colour = col2;

	switch (col)
	{
	case '\3':
		sort_value = value;
		break;

	case '\4':
		sort_value = value + 20;
		break;

	case '\6':
		sort_value = value + 30;
		break;

	case '\5':
		sort_value = value + 40;
		break;
	default:
		cout << "Cos sie zepsulo podczas tworzenia kart";
	}




	
}*/

//#endif




