//
// Created by Mitchell on 6/6/2021.
//

#ifndef FLOODIT_AI_GAME_H
#define FLOODIT_AI_GAME_H

#include "Player.h"
#include "BoardSimple.h"
#include "Board.h"

class Game
{
private:
    Board *board;
    int moveCount;
    Player *player;
    int maxMoves;

public:
    Game(Board *b, Player *p, int totalMoves = 100);

    Game(Player *p, int width = 20, int height = 20, int colourCount = 6, int totalMoves = 100, int seed = -1);

    int play();
};

/* == Game::Game ==
 * Initialises a game of FloodIt to be played with a given pointer to Board and Player.
 *
 * totalMoves - the max number of moves a player can make before DNF'ing
 */
Game::Game(Board *b, Player *p, int totalMoves)
{
    board = b;
    player = p;
    moveCount = 0;
    maxMoves = totalMoves;
}

/* == Game::Game ==
 * Initialises a game of FloodIt to be played with a given pointer Player and the properties of the board.
 *
 * totalMoves - the max number of moves a player can make before DNF'ing
 */
Game::Game(Player *p, int width, int height, int colourCount, int totalMoves, int seed)
{
    board = new Board(seed, colourCount, width, height);

    player = p;
    moveCount = 0;
    maxMoves = totalMoves;
}

/* == Game::play ==
 * Drives the game of FloodIt between the player and the board.
 *
 * Returns the number of moves the game took to play.
 * Returns -1 if there was an error (DNF).
 * -- Player makes invalid move.
 * -- Max number of moves exceeded.
 */
int Game::play()
{
    moveCount = 0;
    bool won = false;

    while (!won)
    {
        if (player->displayBoard) board->print();
        // If the move count was exceeded, DNF
        if (moveCount == maxMoves) return -1;

        // Prepare for getting the move by initialising to an invalid move
        int colour = -1, row = -1, col = -1;
        BoardSimple b(board);

        // If the player reports an error, DNF
        if (!player->getMove(b, colour, row, col)) return -1;

        // If the board reports an error making the move, DNF
        if (!board->makeMove(row, col, colour)) return -1;

        // If we made it here, all is good.
        moveCount++; // Increment the move count
        won = board->checkWin(); // Check if the game has finished
    }

    return moveCount;
}

#endif //FLOODIT_AI_GAME_H
