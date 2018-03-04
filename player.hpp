#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {
private:
    Board *board;
    Side op_side;
	Side pl_side;
	Move *minimax(Node *n, int depth, Side pl_side);
	void calculateScores(Node *n, Board* b, Side s, int depth)
public:
    Player(Side side);
    ~Player();
    Move *doMove(Move *opponentsMove, int msLeft);
	vector<Move*>* getLegalMoves(Move *opponent, Side side);
	
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
