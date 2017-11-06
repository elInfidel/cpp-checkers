#pragma once

#include "game_piece.h"
#include "../direction.h"

namespace draughts
{
    namespace model
    {
        // Represents a blue token on the board
        class checker_piece : public game_piece
        {
            // The current direction of this piece.
            direction curDir;
            // Whether or not this piece is a king
            bool isKing;
            // The character to represent a king piece.
            char kingView;
        public:
            checker_piece(int playerID, direction startDir, char standard, char king);
            ~checker_piece(void);

            // Sets this game piece to a king.
            void make_king(void);
            // Returns true if this piece is a king.
            bool is_king(void) const;
            // Retuns the direction of this piece.
            direction get_direction(void) const;
        };
    }
}