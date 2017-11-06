#pragma once

#include <memory>
#include "checker_piece.h"

namespace draughts
{
    namespace model
    {
        // Represents a single space on the board.
        struct board_space 
        {
            // An empty space character for when a token isn't available.
            const static char EMPTY_SPACE = ' ';

            // A smart pointer containing reference to the token on this space. If one exists.
            std::shared_ptr<checker_piece> cur_piece;
        };

        // Represents the game board and the current positions of all tokens.
        class board
        {
        protected:
            // The width & height of the game board.
            const static int BOARD_WIDTH = 8;
            const static int BOARD_HEIGHT = 8;

            // The 2D array representing our game board
            board_space data[BOARD_HEIGHT][BOARD_WIDTH];

        public:
            board(void);
            ~board(void);

            // Returns the width of the game board.
            int get_width() const;
            // Returns the height of the game board.
            int get_height() const;
            // Returns the token at a given position on the board.
            char get_pos(int x,int y);
            // Attempt to move a player's piece from start X,Y to end X,Y.
            virtual void make_move(int id, int startX, int startY, int endX, int endY) = 0;
            // Resets the game board, returning all pieces to their starting positions.
            virtual void reset() = 0;
        };
    }
}