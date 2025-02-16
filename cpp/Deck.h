#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include "StandardCard.h"
#include "BonusCard.h"
#include "PenaltyCard.h"
#include <vector>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;
#include <windows.h>

void clearScreen() {
    COORD topLeft = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}
class Deck {
private:
    vector<vector<Card*>> cards;
    int rows;
    int columns;

public:
    Deck(int r, int c) : rows(r), columns(c) {
        cards.resize(rows, vector<Card*>(columns, nullptr));

        vector<int> cardNumbers;
        int numPairs = (rows * columns) / 2;
        for (int i = 1; i <= numPairs; ++i) {
            cardNumbers.push_back(i);
            cardNumbers.push_back(i);
        }

        std::mt19937 g(static_cast<unsigned int>(time(nullptr)));
        shuffle(cardNumbers.begin(), cardNumbers.end(), g);

        int index = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                int num = cardNumbers[index++];
                if (num == 7) {
                    cards[i][j] = new BonusCard(false, i * columns + j, num);
                } else if (num == 8) {
                    cards[i][j] = new PenaltyCard(false, i * columns + j, num);
                } else {
                    cards[i][j] = new StandardCard(false, i * columns + j, num);
                }
            }
        }
    }

    ~Deck() {

        for (auto &row : cards) {
            for (auto &card : row) {
                delete card;
            }
        }
    }

    vector<vector<Card*>>& getCards() { return cards; }

    Card* selectCard(int x, int y) {
        if (x >= 0 && x < rows && y >= 0 && y < columns) {
            return cards[x][y];
        }
        return nullptr;
    }

    void displayGrid() const {
        clearScreen();

        for (const auto &row : cards) {
            for (const auto &card : row) {
                card->display();
            }
            cout << endl;
        }
    }
};

#endif
