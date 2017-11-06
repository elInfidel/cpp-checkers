#pragma once

#include <string>

namespace draughts
{
    namespace model
    {
        // Represents a player of the game.
        class player
        {
            std::string name;
            int score;
            
        public:
            // Constructs a new player object with the given name.
            player(std::string name);
            ~player();

            // Returns the name of this player.
            std::string get_name(void) const;

            // Returns the current score of this player.
            int get_score(void) const;

            // Adds the given score to this players score.
            void operator+=(const int rhs);

            // Removes the given score from this players score.
            void operator-=(const int rhs);
        };
    }
}