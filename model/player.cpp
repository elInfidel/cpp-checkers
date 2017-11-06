#include "player.h"

draughts::model::player::player(std::string name) : name(name), score(0) {}
draughts::model::player::~player() {}

std::string draughts::model::player::get_name(void) const
{
    return name;
}

int draughts::model::player::get_score(void) const
{
    return score;
}

void draughts::model::player::operator+=(const int rhs)
{
    this->score += rhs;
}

void draughts::model::player::operator-=(const int rhs)
{
    this->score -= rhs;
}