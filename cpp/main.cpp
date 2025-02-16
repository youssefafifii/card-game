#include "Game.h"

int main() {
    string player1Name, player2Name;
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Enter Player 2 name: ";
    cin >> player2Name;

    Game game(player1Name, player2Name);

    while (!game.checkGameEnd()) {

        game.playTurn();
    }

    game.determineWinner();

    return 0;

}
