#include "player.hpp"
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    board = new Board();
    pl_side = side;
    if (side == BLACK)
        op_side = WHITE;
    else 
        op_side = BLACK;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */	
	//int depth = 1
	int depth = 2;
	if(testingMinimax)
		depth = 2;
	if(opponentsMove != nullptr)
		board->doMove(opponentsMove, op_side);
	vector<Move*>* next = board->getLegalMoves(pl_side); 
	
	if((*next).size() > 0)
	{
		Move *bestmove = minimax(next, board, depth, pl_side)->move;
		if(bestmove != nullptr)
			board->doMove(bestmove, pl_side);
		return bestmove;
	}
	else
		return nullptr;
}

/*
void Player::calculateScores(Node *n, Board* b, Side s, int depth, int originaldepth)
{
	if(depth == 0)
		return;
	vector<Move*>* next_moves = b->getLegalMoves(s);
	for(unsigned int i = 0; i < next_moves->size(); i++)
	{
		Board * newBoard = b->copy();
		Move* m = (*next_moves).at(i);
		newBoard->doMove(m, s);
		Node *child = new Node((*next_moves).at(i));
		
		double score = newBoard->getScore(pl_side);
		
		if(!testingMinimax)
		{
			int sign = 1;
			if(s != pl_side)
				sign = -1;
			score += b->getLegalMoves(pl_side)->size();
			if(b->isCorner(m))
				score += 10 * sign;
			else if(b->isAdToCorner(m))
				score -= 7 * sign;
			else if(b->isEdge(m))
				score += 2 * sign;
		}
		
		child->score = score;
		if(originaldepth == depth)
			child->original_move = (*next_moves).at(i);
		else
			child->original_move = n->original_move;
		
		n->addNextMove(child);
		calculateScores(child, newBoard, getOppositeSide(s), depth - 1, originaldepth);
		delete newBoard;
	}
	delete next_moves;
}*/
Node *Player::minimax(vector<Move*>* moves, Board* b, int depth, Side side)
{
	if(depth == 1)
	{
		Node* best_move = nullptr;
		for(unsigned int i = 0; i < (*moves).size(); i++)
		{
			Board *copy = b->copy();
			copy->doMove((*moves).at(i), side);
			int score = copy->getScore(pl_side);
			if(best_move == nullptr)
			{
				best_move = new Node((*moves).at(i));
				best_move->score = score;
			}
			else if(side == op_side && score < best_move->score)
			{
				best_move->move = (*moves).at(i);
				best_move->score = score;
			}
			else if(side == pl_side && score > best_move->score)
			{
				best_move->move = (*moves).at(i);
				best_move->score = score;
			}
			delete copy;
		}
		return best_move;
	}
	Node *best_move = nullptr;
	for(unsigned int i = 0; i < (*moves).size(); i++)
	{
		Board *copy = b->copy();
		copy->doMove((*moves).at(i), side);
		vector<Move*>* next = board->getLegalMoves(pl_side); 
		if((*next).size() == 0)
			return new Node((*moves).at(i));
		Node *n = minimax(copy->getLegalMoves(getOppositeSide(side)), copy, depth - 1, getOppositeSide(side));
		int score = n->score;
		if(best_move == nullptr)
		{
			best_move = new Node((*moves).at(i));
			best_move->score = score;
		}
		else if(side == op_side && score < best_move->score)
		{
			best_move->move = (*moves).at(i);
			best_move->score = score;
		}
		else if(side == pl_side && score > best_move->score)
		{
			best_move->move = (*moves).at(i);
			best_move->score = score;
		}
		delete copy;
	}
	return best_move;
}

/*
Node *Player::minimax(Node *n, Board* b, int depth, Side side)
{
	if(depth == 1)
	{
		Board *copy = b->copy();
		copy->doMove(n->move, side);
		n->score = b->getScore(pl_side);
		delete copy;
		//std::cerr << "op(" << n->move->x << ", " << n->move->y << ")";
		return n;
	}
	
	Node *best_move = nullptr;
	Board *copy = b->copy();
	if(n->move != nullptr)
		copy->doMove(n->move, side);
	vector<Move*>* next = b->getLegalMoves(getOppositeSide(side));
	std::cerr << (*next).size() << std::endl;
	if(side == pl_side)
	{
		for(unsigned int i = 0; i < (*next).size(); i++)
		{
			
			Move *move = (*next).at(i);
			std::cerr << "op(" << move->x << ", " << move->y << ")";
			Node *m = minimax(new Node((*next).at(i)), b, depth - 1, getOppositeSide(side));
			if(best_move == nullptr)
				best_move = m;
			else if(m!= nullptr && m->score < best_move->score)
				best_move = m;
		}
	}
	else
	{
		for(unsigned int i = 0; i < (*next).size(); i++)
		{
			Move *move = (*next).at(i);
			std::cerr << "pl(" << move->x << ", " << move->y << ")";
			Node *m = minimax(new Node((*next).at(i)), b, depth - 1, getOppositeSide(side));
			if(best_move == nullptr)
				best_move = m;
			else if(m!= nullptr && m->score > best_move->score)
				best_move = m;
		}
	}
	std::cerr << std::endl;
	delete copy;
	n->score = best_move->score;
	n->move = best_move->move;
	return n;
}*/
/*
Node *Player::minimax(Node *n, int depth, Side side)
{
	vector<Node*> next = n->next_moves;
	if(next.size() == 0 || depth == 0)
		return n;
	
	Node *best_move = nullptr;
	//if(!testingMinimax || (side == pl_side && testingMinimax))
	if(side == pl_side)
	{
		for(unsigned int i = 0; i < next.size(); i++)
		{
			Node * m = minimax(next.at(i), depth - 1, getOppositeSide(side));
			if(best_move == nullptr)
				best_move = m;
			else if(m != nullptr && m->score > best_move->score)
				best_move = m;
		}
		return best_move;
	}
	else
	{
		for(unsigned int i = 0; i < next.size(); i++)
		{
			Node * m = minimax(next.at(i), depth - 1, getOppositeSide(side));
			if(best_move == nullptr)
				best_move = m;
			else if(m != nullptr && m->score < best_move->score)
				best_move = m;
		}
		return best_move;
	}
}
*/
/*
 * Get opposite side
 */
Side Player::getOppositeSide(Side this_side)
{
    if (this_side == BLACK)
    {
         return WHITE;
    }
    else
    {
         return BLACK;
    }
}
