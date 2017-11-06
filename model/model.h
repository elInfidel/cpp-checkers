#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <sstream>
#include <map>
#include <thread>
#include <chrono>

#include "player.h"
#include "board.h"
#include "checker_board.h"

#pragma once

namespace draughts
{
    namespace model
    {
        class model
        {
            static std::unique_ptr<model> instance;

            // Used to maintain unique IDs for player objects.
            static int playerIDCounter;

            // A list of all players added into the game.
            std::map<int, player> players;

            // The two playing player IDs and the ID of the currently moving player respectively
            int player_one, player_two, cur_player;

            // The score that must be achieved to win the game.
            const int WIN_SCORE = 12;

            // The game board.
            std::unique_ptr<board> game;

            model(void);
            bool player_exists(const std::string&);

            public:
            void start_game(int, int);
            char get_token(int,int);
            void make_move(int, int, int, int, int);

            void add_player(const std::string&);
            int get_player_score(int);
            int get_current_player(void);
            std::string get_player_name(int);
            std::map<int, std::string> get_player_list(void) const;
            int get_winner();
            int get_width();
            int get_height();
            static model * get_instance(void);
            static void delete_instance(void);
            virtual ~model(void);
        };
    }
}
