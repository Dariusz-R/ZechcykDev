#ifndef PLAYER
#define PLAYER

#include <iostream>
#include "Card.h"
#include <vector>


using namespace std;

class Player
{
    public:
    string name ;
    short player_number, trick_points, game_points ;
    vector<Card> player_cards ;


    public :
    void name_players(short number) ;
    void who_plays(short number) ;
    void take_card(Card) ;
    void sort_cards() ;
    void show(short, short) ;
    int choice_game_type(short&) ;
    bool ask_or_not () ;
    short other_player_asked(short&, short&) ;
    vector <short> which_card_you_may_throw(Card&);
    Card compare_two(Card&, Card&);
    Card which_card_you_throw(short[],short);
    Card which_card_you_throw(short[], short, Card&, string&);
    Card which_card_you_throw(short[], short, Card&, Card&, string&);
    void destroy_thrown_card(short[], short);

    //void show_player_atribute(string, short)
};

#endif