#include "checker_board.h"
#include "../direction.h"
#include "checker_piece.h"

draughts::model::checker_board::checker_board(int firstPlayer, int secondPlayer) :firstPlayer(firstPlayer), secondPlayer(secondPlayer)
{
    reset();
}

draughts::model::checker_board::~checker_board()
{

}

void draughts::model::checker_board::make_move(int id, int startX, int startY, int endX, int endY)
{
    // Ensure given coordinates are within acceptable range.
    bool xOutOfBounds = (startX < 1 || startX > BOARD_WIDTH || endX < 1 || endX > BOARD_WIDTH);
    bool yOutOfBounds = (startY < 1 || startY > BOARD_HEIGHT || endY < 1 || endY > BOARD_HEIGHT);
    if(xOutOfBounds || yOutOfBounds)
        throw std::runtime_error("Error: Your input coordinates must be within the bounds of the board!");
    
    // Obtain the offset coords to reach into array.
    int aX = startX-1;
    int aY = startY-1;
    int bX = endX-1;
    int bY = endY-1;

    // Obtain the pieces at given coords and any extra data if required.
    checker_piece* pieceToMove = data[aX][aY].cur_piece.get();
    checker_piece* pieceAtTarget = data[bX][bY].cur_piece.get();

    // Ensure there is a piece to move at start coords
    // and that there is no piece at the end coords.
    if(!pieceToMove || pieceAtTarget)
        throw std::runtime_error((!pieceToMove)?"Error: No piece at your starting coords!":"Error: A piece exists where you want to move!");
    
    direction dir = pieceToMove->get_direction();
        
    // Enforce player moving their own piece.
    if(pieceToMove->get_id() != id)
        throw std::runtime_error("Error: You can only move your own pieces!");

    // Check the player is moving in a legal direction.
    if(aY < bY && dir == direction::UP && dir != direction::BOTH)
        throw std::runtime_error("Error: You can only move upwards with this piece!");
    else if(aY > bY && dir == direction::DOWN && dir != direction::BOTH)
        throw std::runtime_error("Error: You can only move downwards with this piece!");

    // Calculate any removed pieces if existing.
    bool isValid = false;
    if(dir == direction::UP || dir == direction::BOTH)
    {
        if(bounds_check(aX - 1, aY - 1))
        {
            checker_piece* topLeft = data[aX - 1][aY - 1].cur_piece.get();
            if(topLeft && (bX == aX - 2 && bY == aY - 2 && bounds_check(aX - 2, aY - 2))) // Jump move
            {
                // We already know the target move location is free so jump the piece.
                data[aX - 1][aY - 1].cur_piece = nullptr;
                isValid = true;
            }
            else if(bX == aX - 1 && bY == aY - 1) // Standard move
                isValid = true;
        }
        else if(bounds_check(aX + 1, aY - 1)) // Top right
        {
            checker_piece* topRight = data[aX + 1][aY - 1].cur_piece.get();
            if(topRight && (bX == aX + 2 && bY == aY - 2 && bounds_check(aX + 2, aY - 2)))
            {
                // We already know the target move location is free so jump the piece.
                data[aX + 2][aY - 2].cur_piece = nullptr;
                isValid = true;
            }
            else if(bX == aX + 1 && bY == aY - 1) // Standard move
                isValid = true;
        }
    }

    if(dir == direction::DOWN || dir == direction::BOTH)
    {
        if(bounds_check(aX - 1, aY + 1))
        {
                checker_piece* bottomLeft = data[aX - 1][aY + 1].cur_piece.get();
                if(bottomLeft && (bX == aX - 2 && bY == aY + 2 && bounds_check(aX - 2, aY + 2))) // Jump move
                {
                    // We already know the target move location is free so jump the piece.
                    data[aX - 2][aY + 2].cur_piece = nullptr;
                    isValid = true;
                }
                else if(bX == aX - 1 && bY == aY + 1) // Standard move
                    isValid = true;
        }
        else if(bounds_check(aX + 1, aY + 1)) // Bottom right
        {
            checker_piece* bottomRight = data[aX + 1][aY + 1].cur_piece.get();
            if(bottomRight && (bX == aX + 2 && bY == aY + 2 && bounds_check(aX + 2, aY + 2)))
            {
                // We already know the target move location is free so jump the piece.
                data[aX + 2][aY + 2].cur_piece = nullptr;
                isValid = true;
                
            }
            else if(bX == aX + 1 && bY == aY + 1) // Standard move
                isValid = true;
        }
    }

    if(!isValid)
        throw std::invalid_argument("Error: Invalid move!");

    // Move piece
    data[bX][bY].cur_piece = data[aX][aY].cur_piece;
    data[aX][aY].cur_piece = nullptr;

    // King check.
    int kingRow = (dir == direction::UP) ? 0 : BOARD_HEIGHT - 1;
    if(bY == (kingRow))
        pieceToMove->make_king();
}

void draughts::model::checker_board::reset()
{
    // Clear the board
    for(int x = 0; x < BOARD_WIDTH; ++x)
    {
        for(int y = 0; y < BOARD_HEIGHT; ++y)
        {
            data[x][y].cur_piece = nullptr;
        }
    }

    // Set player one pieces
    for(int x = 0; x < BOARD_WIDTH; ++x)
    {
        for(int y = 1; y < 4; ++y)
        {
            if(x % 2 == (y % 2 == 0) ? 1 : 0)
            data[x][BOARD_HEIGHT - y].cur_piece = std::make_shared<checker_piece>(firstPlayer, direction::UP, 'o', 'O');
        }
    }

    // Set player two tokens
    for(int x = 0; x < BOARD_WIDTH; ++x)
    {
        for(int y= 0; y < 3; ++y)
        {
            if(x % 2 == (y % 2 == 0) ? 1 : 0)
            data[x][y].cur_piece = std::make_shared<checker_piece>(secondPlayer, direction::DOWN, 'x', 'X');
        }
    }
}

bool draughts::model::checker_board::bounds_check(int x, int y) const
{
    if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT)
        return true;
    else
        return false;
}