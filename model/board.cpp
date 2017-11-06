#include "board.h"

#include <iostream>
#include <stdexcept>

draughts::model::board::board()
{
}

draughts::model::board::~board(void) { }

int draughts::model::board::get_width() const
{
    return BOARD_WIDTH;
}

int draughts::model::board::get_height() const
{
    return BOARD_HEIGHT;
}

char draughts::model::board::get_pos(int x,int y)
{
    // Return the token in the requested position or an empty space character otherwise.
    game_piece* ptr = data[y-1][x-1].cur_piece.get();
    return (ptr) ? ptr->get_view() : board_space::EMPTY_SPACE;
}