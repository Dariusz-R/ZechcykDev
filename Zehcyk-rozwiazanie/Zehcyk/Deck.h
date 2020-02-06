//#ifndef DECK
//#define DECK

#include <iostream>


using namespace std ;

class Deck
{
    char symbol[4] ;
    short colour ;
    short   value ;

    public:
    void create_deck();
    void shuffle_deck();

};

//#endif