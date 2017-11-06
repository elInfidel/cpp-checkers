#include "game_piece.h"

draughts::model::game_piece::game_piece(int playerID, char view) : view(view), playerID(playerID) 
{

}

draughts::model::game_piece::~game_piece(void) 
{ 

}

char draughts::model::game_piece::get_view() const
{
    return view;
}

int draughts::model::game_piece::get_id() const
{
    return playerID;
}

void draughts::model::game_piece::set_view(char newView)
{
    view = newView;
}

void draughts::model::game_piece::set_id(int newID)
{
    playerID = newID;
}