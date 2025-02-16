#ifndef CARD_H
#define CARD_H
#include <iostream>
using namespace std;

class Card {
protected:
    bool faceUp;
    int location;
    int number;

public:
    Card(bool fU = false, int l = 0, int n = 0) : faceUp(fU), location(l), number(n) {}
    virtual ~Card() {}

    virtual void display() const {
        cout << (faceUp ? "" + to_string(number) : "*") << " ";
    }

    bool isFaceUp() const { return faceUp; }
    void reveal() { faceUp = true; }
    void hide() { faceUp = false; }
    int getNumber() const { return number; }
};
#endif
