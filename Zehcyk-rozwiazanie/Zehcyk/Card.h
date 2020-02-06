#ifndef CARD
#define CARD
#include <iostream>

using namespace std;

class Card
{
    public:
    char symbol[5];
    short   value, sort_value, colour ;

public:

    void create_card(int, char, char, char, short);
};

#endif