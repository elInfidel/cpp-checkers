#include "model.h"
#include <random>

std::unique_ptr<draughts::model::model> draughts::model::model::instance = nullptr;

int draughts::model::model::playerIDCounter = 0;

draughts::model::model::model(void) {}
draughts::model::model::~model(void) {}

draughts::model::model* draughts::model::model::get_instance(void)
{
    if(instance == nullptr)
    {
        instance = std::unique_ptr<model>(new model);	
    }
    return instance.get();    
}

int draughts::model::model::get_player_score(int playernum)
{
    int score = 0;

    auto iterator = players.find(playernum);
    if (iterator != players.end())
      score = iterator->second.get_score();

    return score;
}

void draughts::model::model::start_game(int plr1, int plr2)
{
    // Build our random generator.
    std::default_random_engine gen;
    std::uniform_int_distribution<int> dist(0,10);
    int result = dist(gen);

    std::cout << "Random result: " << result << std::endl;

    // Assign game players based on input parameters.
    player_one = plr1;
    player_two = plr2;
    
    // Decide on starting player.
    if(result < 5)
        cur_player = player_one;
    else
        cur_player = player_two;

    std::cout << "First player: " << cur_player << std::endl;

    // Create the game board.
    game = std::unique_ptr<board>(new checker_board(cur_player, (cur_player == player_one) ? player_two : player_one));
}

int draughts::model::model::get_winner()
{
    int p1Score = players.at(player_one).get_score();
    int p2Score = players.at(player_two).get_score();

    // Decide if someone has won the game.
    if(p1Score >= WIN_SCORE)
        return p1Score;
    else if(p2Score >= WIN_SCORE)
        return p2Score;

    return -1;
}

std::string draughts::model::model::get_player_name(int id)
{
    std::string name;

    // Find any player with the given name.
    auto iterator = players.find(id);
    if (iterator != players.end())
        name = iterator->second.get_name();

    return name;
}

char draughts::model::model::get_token(int x ,int y)
{
    return game.get()->get_pos(x, y);
}

void draughts::model::model::make_move(int playernum,
        int startx, int starty, int endx, int endy)
{
    // Move on the board and switch players.
    game.get()->make_move(playernum, startx, starty, endx, endy);
    cur_player = (cur_player == player_one) ? player_two : player_one;
}

void draughts::model::model::add_player(const std::string& p)
{
    // Increment the player ID counter and add new player with name 'p'.
    int newID = ++playerIDCounter;
    players.insert(std::pair<int,draughts::model::player>(newID, player(p)));
}

bool draughts::model::model::player_exists(const std::string& pname)
{
    // Check for the existance of given player name.
    for (auto const& pair : players)
    {
        if(pair.second.get_name() == pname)
            return true;
    }

    return false;
}

int draughts::model::model::get_current_player(void)
{
    return cur_player;
}

std::map<int, std::string> draughts::model::model::get_player_list(void) const
{
    std::map<int, std::string> nameslist;

    // Iterate all players and add them to list.
    for (auto const& pair : players)
    {
        nameslist[pair.first] = pair.second.get_name();
    }

    return nameslist;
}

void draughts::model::model::delete_instance(void)
{
    // Deletes the instance of the model.
    instance.reset(nullptr);
}


int draughts::model::model::get_width()
{
    return game.get()->get_width();
}

int draughts::model::model::get_height()
{
    return game.get()->get_height();
}

