#include "player.hpp"
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
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
    if(opponentsMove != nullptr)
		board.doMove(opponentsMove, op_side);
	
	vector<Move*> legal_moves;
    for(int x = 0; x < 8; x++)
    {
		for(int y = 0; y < 8; y++)
		{
			Move* m = new Move(x, y);
			if(board.checkMove(m, pl_side))
				legal_moves.push_back(m);
		}
	}
	
	
	
	
	Move *bestmove = minimax(head, 2, op_side);
	if(bestmove != nullptr)
		board.doMove(bestmove, pl_side);
	return bestmove;
	/*
    vector<Move*> legal_moves;
    for(int x = 0; x < 8; x++)
    {
		for(int y = 0; y < 8; y++)
		{
			Move* m = new Move(x, y);
			if(board.checkMove(m, pl_side))
			{
				legal_moves.push_back(m);
				if(board.isCorner(m))
				{
					board.doMove(m, pl_side);
					return m;
				}
			}
		}
	}
	
	if(legal_moves.size() > 0)
	{
		Move* bestmove = nullptr;
		int max_moves = -1;
		for(unsigned int i = 0; i < legal_moves.size(); i++)
		{
			Board *copy = board.copy();
			copy->doMove(legal_moves[i], pl_side);
			int pl_moves = 0;
			for(int x = 0; x < 8; x++)
			{
				for(int y = 0; y < 8; y++)
				{
					Move* m = new Move(x, y);
					if(copy->checkMove(m, pl_side))
					{
						pl_moves++;
						if(board.isCorner(m))
							pl_moves += 10;
						else if(board.isEdge(m))
							pl_moves += 2;
						else if(board.isAdToCorner(m))
							pl_moves -= 7;
					}
				}
			}
			if(pl_moves > max_moves)
			{
				max_moves = pl_moves;
				bestmove = legal_moves[i];
			}
			delete copy;
		}
			
		if(bestmove != nullptr)
		{
			board.doMove(bestmove, pl_side);
			return bestmove;
		}
		else
			return nullptr;
	}
	else
		return nullptr;
	*/
}

Move *Player::minimax(Node *n, int depth, Side side)
{
	
	vector<Node*>* next = n->next_moves;
	if(next->size() == 0 || depth <= 0)
	{
		return n->score *
	}
	
	int max_score = -1000000000;
	for(int i = 0; i < next->size(); i++)
	{
		max_score = max(max_score, -1 * minimax(next[i], depth - 1, )
	}
}
