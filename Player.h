//
// Created by Mitchell on 6/6/2021.
//

#ifndef FLOODIT_AI_PLAYER_H
#define FLOODIT_AI_PLAYER_H

#include "BoardSimple.h"

class Player {
private:
    std::string name;
public:
    // Flag to display the board every turn (false for AI, true for human player)
    bool displayBoard = false;

    Player(std::string n): name(n) {}
    virtual ~Player() {}

    /* == Player::getMove ==
     * Gets a move from the user with the given board.
     *
     * Returns row, col, and colour in the given pass-by-reference variables.
     * Should return true if the get move was successful, and false if it encountered an error.
     */
    virtual bool getMove(BoardSimple board, int& colour, int& row, int& col) = 0;

    /* Getters */
    std::string getPlayerName() { return name; }
};

#endif //FLOODIT_AI_PLAYER_H
