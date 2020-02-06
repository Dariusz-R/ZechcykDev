//#ifndef CARD
//#define CARD

#include <iostream>
#include "Card.h"


using namespace std;

void Card::create_card(short i, char val, char sym, char col, short col2)
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





}

//#endif




