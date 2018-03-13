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
    op_side = getOppositeSide(side);
}

/*
 * Destructor for the player.
 */
Player::~Player() {
	delete board;
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
	
	int depth = 5;
	if(testingMinimax)
		depth = 2;
	if(opponentsMove != nullptr)
		board->doMove(opponentsMove, op_side);
	vector<Move*>* next = board->getLegalMoves(pl_side); 
	
	if(next->size() > 0)
	{
		int alpha = -1000000;
		int beta = 10000000;
		Move *bestmove = minimax(next, board, depth, pl_side, alpha, beta);
		if(bestmove != nullptr)
			board->doMove(bestmove, pl_side);
		return bestmove;
	}
	else
	{
		delete next;
		return nullptr;
	}
}


Move *Player::minimax(vector<Move*>* moves, Board* b, int depth, Side side, int alpha, int beta)
{
	if(depth == 1)
	{
		Move *bestmove = nullptr;
		for(unsigned int i = 0; i < moves->size(); i++)
		{
			Move* m = moves->at(i);
			Board *copy = b->copy();
			copy->doMove(m, side);
			
			int score = copy->getScore(pl_side);		
			if(!testingMinimax)
			{
				score += copy->advancedScore(m, copy, side, pl_side);
				score += copy->getNumberOfLegalMoves(pl_side); 
			}
			delete copy;
			if(bestmove == nullptr)
			{
				bestmove = m;
				bestmove->score = score;
			}
			else if(side == op_side && score < bestmove->score)
			{
				bestmove = m;
				bestmove->score = score;
			}
			else if(side == pl_side && score > bestmove->score)
			{
				bestmove = m;
				bestmove->score = score;
			}
			//std::cerr << "depth: " << depth << " (" << alpha << "," << beta << ")" << std::endl;
		}
		
		for(unsigned int i = 0; i < moves->size(); i++)
		{
			if(moves->at(i) != bestmove)
				delete moves->at(i);
		}
		delete moves;
		return bestmove;
	}
	
	Move *bestmove = nullptr;
	for(unsigned int i = 0; i < moves->size(); i++)
	{
		Move* m = moves->at(i);
		Board *copy = b->copy();
		copy->doMove(m, side);
		vector<Move*>* next = copy->getLegalMoves(getOppositeSide(side)); 
		if(next->size() == 0)
		{
			delete next;
			return m;
		}	
		Move *n = minimax(next, copy, depth - 1, getOppositeSide(side), alpha, beta);
		int score = n->score;
		delete n;
		if(!testingMinimax)
			score += copy->advancedScore(m, copy, side, pl_side);
		if(bestmove == nullptr)
		{
			bestmove = m;
			bestmove->score = score;
		}
		else if(side == op_side && score < bestmove->score)
		{
			bestmove = m;
			bestmove->score = score;
		}
		else if(side == pl_side && score > bestmove->score)
		{
			bestmove = m;
			bestmove->score = score;
		}
		
		//std::cerr << "depth: " << depth << " (" << alpha << "," << beta << ")" << std::endl;
		if(side == pl_side && score > alpha)
			alpha = score;
		else if(side == op_side && score < beta)
			beta = score;
		
		delete copy;
		if(beta <= alpha)
		{
			//std::cerr << "BREAK depth: " << depth << " (" << alpha << "," << beta << ")" << std::endl;
			break;
		}
	}
	for(unsigned int i = 0; i < moves->size(); i++)
	{
		if(moves->at(i) != bestmove)
			delete moves->at(i);
	}
	delete moves;
	return bestmove;
}

/*
 * Get opposite side
 */
Side Player::getOppositeSide(Side this_side)
{
    if (this_side == BLACK)
         return WHITE;
    else
         return BLACK;
}
