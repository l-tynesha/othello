#ifndef __COMMON_H__
#define __COMMON_H__

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
	int score;
	vector<Node*> next_moves;
	Node()
	{
		move = nullptr;
	}
	Node(Move *m)
	{
		move = m;
	}
	void addNextMove(Move *next)
	{
		next_moves.push_back(next);
	}
	~Node()
	{
		delete move;
	}
};

class Tree {
public:
	Node* head;
	Tree()
	{
		head = nullptr;
	}
	~Tree
	{
		deleteTree(head);
	}
	void deleteTree(Node *head)
	{
		for(int i = 0; i < next_moves.size(); i++)
		{
			deleteTree(next_moves[i]);
		}
		delete head;
	}
	void addNode(Move *m, int score)
	{
		
	}
}
#endif
