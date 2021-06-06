#include <iostream>

#include "Board.h"
#include "Game.h"
#include "Player.h"

#include "HumanPlayer.h"

int main() {

    Player* p = new HumanPlayer();
    Game game(p, 3, 3);

    game.play();

    return 0;
}
