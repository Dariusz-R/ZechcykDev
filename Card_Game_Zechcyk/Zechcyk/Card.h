#ifndef CARD
#define CARD
#include <iostream>



class Card
{
    static short card_counter;
    static short values_pattern[6];
    static char symbol_pattern[6];
    static char colour_pattern[4];
    public:
    char symbol[5];
    short colour ;

public:
    Card();

};

#endif