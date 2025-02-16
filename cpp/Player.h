#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
using namespace std;

class Player {
    string name;
    int score;

public:
    Player(string n, int s = 0) : name(n), score(s) {}

    void incrementScore(int points) { score += points; }
    int getScore() const { return score; }
    string getName() const { return name; }

    void displayScore() const {
        cout << name << " Score: " << score << endl;
    }
};
#endif
