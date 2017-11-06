#pragma once

#include "board.h"

namespace draughts
{
    namespace model
    {
        class checker_board : public board
        {
            // the player going first and the player going second.
            int firstPlayer, secondPlayer;
            
            bool bounds_check(int x, int y) const;

        public:
            checker_board(int firstPlayer, int secondPlayer);
            ~checker_board();

            // Implemented from board.h
            virtual void make_move(int id, int startX, int startY, int endX, int endY);
            virtual void reset();
        };
    }
}