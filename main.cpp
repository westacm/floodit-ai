#include <iostream>

#include "Board.h"
#include "Game.h"
#include "Player.h"

#include "HumanPlayer.h"
#include "BasicAI.h"

int main() {

    Player* p = new HumanPlayer();
    Game game(p, 5, 5, 6, 100, 100);

    int m = game.play();

    if(m == -1) std::cout << "Error with game! Exiting.\n";
    else std::cout << "Game finished in " << m << " moves.\n";

    return 0;
}
