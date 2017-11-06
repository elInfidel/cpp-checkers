#pragma once

namespace draughts
{
    namespace model
    {
        // Represents a space on the board
        class game_piece
        {
            // The character representing this game piece.
            char view;
            // The player ID that owns this game piece.
            int playerID;

        protected:
            // Sets the character representing this game piece.
            void set_view(char newView);

        public:
            game_piece(int playerID, char view);
            ~game_piece(void);

            // Returns the character value of this token.
            char get_view() const;
            // Returns the player ID associated to this game piece.
            int get_id() const;
            // Sets the player ID associated to this game piece.
            void set_id(int newID);
        };
    }
}