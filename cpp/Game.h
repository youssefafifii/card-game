#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "Player.h"
#include <iostream>

using namespace std;

class Game {
private:
    Deck *deck;
    Player *player1, *player2;
    bool turn;

public:
    Game(const string& n1, const string& n2) : player1(new Player(n1)), player2(new Player(n2)), turn(false) {
        deck = new Deck(4, 4);
        deck->displayGrid();
    }

    ~Game() {
        delete deck;
        delete player1;
        delete player2;
    }

    void playTurn() {
    Player* currentPlayer = (turn ? player2 : player1);
    cout << currentPlayer->getName() << "'s turn. Choose two cards to flip:" << endl;
    int x1, y1, x2, y2;
    cout << "Enter coordinates for the first card (row and column) from 1 to 4 : ";
    cin >> x1 >> y1;
    x1--; y1--;
    cout << "Enter coordinates for the second card (row and column) from 1 to 4 : ";
    cin >> x2 >> y2;
    x2--; y2--;

    Card* card1 = deck->selectCard(x1, y1);
    Card* card2 = deck->selectCard(x2, y2);

    if (card1 != nullptr && card2 != nullptr && card1 != card2 && !card1->isFaceUp() && !card2->isFaceUp()) {
        card1->reveal();
        card2->reveal();
        deck->displayGrid();
        cout<<  "Player 1 Score:" << player1->getScore()  << endl;
        cout<<  "Player 2 Score:" << player2->getScore()  << endl;


         if (card1->getNumber() == 7 || card2->getNumber() == 7) {
                if (card1->getNumber() == 7 && card2->getNumber() == 7) {
                    cout << "Double Bonus Cards! Choose +2 points or +1 point and another turn (Enter '2' for points, '1' for turn): ";
                    int choice;
                    cin >> choice;
                    if (choice == 2) {
                        currentPlayer->incrementScore(2);
                    } else {
                        currentPlayer->incrementScore(1);
                        turn = !turn;
                    }
                } else {
                    cout<<"You gained 1 score using Bonus Card"<<endl;
                    currentPlayer->incrementScore(1);

            } }else if (card1->getNumber() == 8 || card2->getNumber() == 8) {
                if (card1->getNumber() == 8 && card2->getNumber() == 8) {
                    cout << "Double Penalty Cards! Choose to lose 2 points or lose 1 point and skip next turn (Enter '2' for points, '1' for skip): ";
                    int choice;
                    cin >> choice;
                    if (choice == 2) {
                        currentPlayer->incrementScore(-2);
                    } else {
                        cout<<"You lost 1 score using Penalty Card"<<endl;

                        currentPlayer->incrementScore(-1);
                        turn = !turn;
                    }
                } else {
                    cout<<"You lost 1 score using Penalty Card"<<endl;

                    currentPlayer->incrementScore(-1);
                }
            }



        if (card1->getNumber() == card2->getNumber()) {
            cout << "It's a match!" << endl;
            currentPlayer->incrementScore(1);


        } else {
            if(card1->getNumber() == 7 ||card1->getNumber() == 8  ){
                card2->hide();
            }else if(card2->getNumber() == 7 ||card2->getNumber() == 8){
            card1->hide();
            }
            else{

            cout << "No match. Cards will be flipped back." << endl;
            card1->hide();
            card2->hide();
            }
        }
        turn = !turn;
     }else {
        cout << "Invalid input or cards already flipped. Try again." << endl;
    }

    }
    bool checkGameEnd() {
        for (const auto& row : deck->getCards()) {
            for (const auto& card : row) {
                if (!card->isFaceUp()) return false;
            }
        }
        return true;
    }

    void determineWinner() {
        player1->displayScore();
        player2->displayScore();

        if (player1->getScore() > player2->getScore()) {
            cout << player1->getName() << " wins!" << endl;
        } else if (player2->getScore() > player1->getScore()) {
            cout << player2->getName() << " wins!" << endl;
        } else {
            cout << "It's a tie!" << endl;
        }
    }
};

#endif
