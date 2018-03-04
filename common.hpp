#ifndef __COMMON_H__
#define __COMMON_H__

#include <vector>
using namespace std;
enum Side { 
    WHITE, BLACK
};

class Move {
   
public:
    int x, y;
    Move(int x, int y) {
        this->x = x;
        this->y = y;        
    }
    ~Move() {}

    int getX() { return x; }
    int getY() { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
};

class Node {
public:
	Move* move;
	double score;
	vector<Node*> next_moves;
	Move* original_move;
	Node()
	{
		original_move = nullptr;
		move = nullptr;
		score = 0;
	}
	Node(Move *m)
	{
		move = m;
		original_move = nullptr;
		score = 0;
	}
	void addNextMove(Node *next)
	{
		next_moves.push_back(next);
	}
	~Node()
	{
		delete move;
	}
};
#endif
