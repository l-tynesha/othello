#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {
private:
    Side op_side;
	Side pl_side;
	Node *minimax(vector<Move*>* moves, Board *b, int depth, Side pl_side);
	Side getOppositeSide(Side this_side);
public:
    Player(Side side);  
    ~Player();
    Move *doMove(Move *opponentsMove, int msLeft);
	Board *board;
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
