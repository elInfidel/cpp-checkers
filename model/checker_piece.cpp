#include "checker_piece.h"

draughts::model::checker_piece::checker_piece(int playerID, direction startDir, char standard, char king)
: game_piece(playerID, standard)
{
    this->curDir = startDir;
    this->kingView = king;
    this->isKing = false;
}

draughts::model::checker_piece::~checker_piece(void)
{

}

void draughts::model::checker_piece::make_king()
{
    isKing = true;
    set_view(kingView);
    curDir = direction::BOTH;
}

bool draughts::model::checker_piece::is_king(void) const
{
    return isKing;
}

draughts::direction draughts::model::checker_piece::get_direction(void) const
{
    return curDir;
}