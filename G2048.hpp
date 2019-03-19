#pragma once
#include"util.hpp"

class Game2048{
public:

    //enum moveType {UP, DOWN, RIGHT, LEFT};
    Game2048(int boardSize);
    bool move(int m);      //returns 0 if game over, 1 if more moves are possible
    vector<int> getGameState() {return _board;}     //retuns boards state
    int evaluate() const {return _points;}          //returns points
    void printBoard();
private:
    int _bsize;     //board size
    vector<int> emptyFieldNumbers ();
    int _points;
    vector<int> _board;
};
