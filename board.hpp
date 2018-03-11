#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include "common.hpp"


class Board {

private:
    bitset<64> black;
    bitset<64> taken;

    bool occupied(int x, int y);
    bool get(Side side, int x, int y);
    void set(Side side, int x, int y);
    bool onBoard(int x, int y);

public:
    Board();
    ~Board();
    Board *copy();

    bool isDone();
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    bool isCorner(Move *m);
    bool isAdToCorner(Move *m);
    bool isEdge(Move *m);
	bool adjacentEdges(Move *m);
	bool isDiaToCorner(Move *m);
	bool inner_corners(Move *m);
    void doMove(Move *m, Side side);
    int count(Side side);
    int countBlack();
    int countWhite();
	int getScore(Side side);
	int advancedScore(Move *m, Board* b, Side s, Side pl_side);
    void setBoard(char data[]);
	vector<Move*>* getLegalMoves(Side side);
	
};

#endif
