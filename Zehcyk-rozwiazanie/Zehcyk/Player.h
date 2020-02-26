#ifndef PLAYER
#define PLAYER

#include <iostream>
#include "Card.h"
#include <vector>




class Player
{   //PRIVATE DATA MEMBERS
    std::string name;
    std::string name_shortcut;
    short  trick_points, game_points ;
    std::vector <const Card*> player_cards;
    short last_thrown_card_iterator;
    short const SORT_LIKE_FOR_MISERY;

    //PUBLIC METHODS ORDERED CHRONOLOGICALLY
    // METHODS DIVIDED IN THREE PHASES:
    // 1 - begining
    // 2 - auction
    // 3 - game

public:
    // USED IN PHASE 1:
    Player();
    void name_player(short);
    std::string get_name();
    void take_card( Card const *);
    // USED IN PHASE 1 AND 2:
    void sort_cards(short);
    // USED IN PHASE 2 AND 3:
    void show(short, std::string);
    void throw_out_all_remain_cards();
    void add_game_points(short);
    short get_game_points();
    // USED IN PHASE 3:
    Card const* which_card_I_throw(std::vector<short> = {});
    void show_me_what_I_can_throw(std::vector<short>);
    std::vector<short> how_many_card_in_thrown_colour_i_have(short);
    Card const* share_card(short);
    bool do_I_have_queen_and_king_in_one_colour();
    bool do_I_want_to_meld();
    void add_trick_points(short);
    short get_trick_points();
    std::string get_name_shortcut();
    void reset_trick_points();
    void erase_thrown_card();

};

#endif