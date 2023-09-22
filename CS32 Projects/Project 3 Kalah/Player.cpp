#include "Player.h"
#include <iostream>
#include <vector>


Player::Player(std::string name) : mname(name)
{
	
}

std::string Player::name() const
{
	return mname;
}

bool Player::isInteractive() const
{ // returns false by default
	return false;
}

Player::~Player()
{
}

HumanPlayer::HumanPlayer(std::string name) : Player(name)
{
}

bool HumanPlayer::isInteractive() const
{ // only the human player isInteractive() returns true
	return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
	int move = 0;
	for (;;) // wait until user enters a valid move
	{
		std::cin >> move; // takes in user's move
		if (move > 0 && move <= b.holes())
			if (b.beans(s, move) !=0) // checks for valid move
			return move;
	}
}

BadPlayer::BadPlayer(std::string name) : Player(name)
{
}

int BadPlayer::chooseMove(const Board& b, Side s) const
{
	for (int i = 1; i < b.holes(); i++)
	{ // starting at hole #1, find the leftmost non-empty hole
		if (b.beans(s, i) != 0)
			return i;
	}
	return b.holes();
}

SmartPlayer::SmartPlayer(std::string name) : Player(name)
{
}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
	int depth = 10; // maximum depth allowed
	double timeLimit = 4990;  // 4.99 seconds; allow 10 ms for wrapping up
	JumpyTimer timer(1000); // timer::elapsed only gets called once every 1000 calls to JumpyTimer::elapsed

	int bestHole; // prepares bestHole to be passed by reference to helper function
	for (int i = 1; i <= b.holes(); i++)
		if (b.beans(s, i) != 0)
		{ // find the first non-empty hole; that's the default choice if helper does not find a better hole
			bestHole = i;
			break;
		}
	int value; // prepares value to be passed by reference to helper function

	unsigned long result = 0; // # of calls made to recursive helper function
	chooseMove(b, s, depth, bestHole, value, timeLimit, timer, result); // call the helper function on the current board state to pick a move
	std::cout << timer.actualElapsed() << " ms" << std::endl; // print the time it took; should be capped at 4990 ms
	std::cout << result / 1000000.0 << " million calls" << std::endl; // print the # of calls
	return bestHole;
}

int SmartPlayer::eval(const Board& b, Side s) const
{ // assigns a value to the board state
	if (b.beansInPlay(NORTH) == 0 || b.beansInPlay(SOUTH) == 0)
	{ // if the game has ended...
		if (b.beans(SOUTH, POT) + b.beansInPlay(SOUTH) 
			> b.beans(NORTH, POT) + b.beansInPlay(NORTH))
			return 1000000; // +infinity because south wins
		else if (b.beans(NORTH, POT) + b.beansInPlay(NORTH)
			> b.beans(SOUTH, POT) + b.beansInPlay(SOUTH))
			return -1000000; // -infinity because north wins
	}
	return b.beans(SOUTH, POT) - b.beans(NORTH, POT); // difference between the pots
}

void SmartPlayer::chooseMove(const Board& b, Side s, int depth, int& bestHole, int& value, double timeLimit, JumpyTimer& timer, unsigned long& result) const
{
	Side opponent;
	if (s == NORTH)
		opponent = SOUTH;
	else opponent = NORTH; // determine who the opponent is

	result++; // increment # of calls every time the helper function is called
	if (b.beansInPlay(s) == 0)
	{ // if no more beans in play on a certain side...
		bestHole = -1; // there is no hole to choose
		value = eval(b, s); // evaluate the current state
		return;
	}
	if (depth == 0)
	{ // maximum depth reached, don't go any deeper...
		bestHole = -1; // no hole to choose
		value = eval(b, s); // evaulate the current state
		return;
	}
	else if (timeLimit <= 0)
	{ // maximum time reached, don't go any deeper...
		return;
	}

	if (s == NORTH)
		value = 9999; // default value
	else
		value = -9999;

	for (int i = b.holes(); i >= 1; i--)
	{ // loop through the holes 
		if (b.beans(s, i) == 0) // if a hole is empty, skip it
			continue;
		Board copy1(b); // make a copy so you can "make" your moves without affecting the real board
		int endHole; // make an endHole and endSide to track where you end with a move
		Side endSide;
		int h2; // make a bestHole #2 and value #2 for the recursive calls 
		int v2;
		double thisBranchTimeLimit = timeLimit / i; // ALLOCATE REMAINING TIME LIMIT EQUALLY AMONG REMAINING BRANCHES
		double startTime = timer.elapsed(); // SAVE BRANCH START TIME
		
		// EXPLORE THIS BRANCH
		copy1.sow(s, i, endSide, endHole); // make the move and determine its value
		if (endSide == s && endHole == 0) // end in own pot
			chooseMove(copy1, s, depth-1, h2, v2, timeLimit, timer, result); // pass it the board copy and h2 and v2 so it can choose its next additional move and evaluate that board state
		else if (endSide == s && copy1.beans(s, endHole == 1) && copy1.beans(opponent, endHole) != 0)
		{ // capture
			copy1.moveToPot(NORTH, endHole, s);
			copy1.moveToPot(SOUTH, endHole, s);
			chooseMove(copy1, opponent, depth - 1, h2, v2, timeLimit, timer, result); // pass it the board copy and h2 and v2 with the opponent parameter so it can evaluate all the possible moves opponent can make in response
		}
		else
			chooseMove(copy1, opponent, depth - 1, h2, v2, timeLimit, timer, result); // pass it the board copy and h2 and v2 with the opponent parameter so it can evaluate all the possible moves opponent can make in response

		timeLimit -= (timer.elapsed() - startTime); // ADJUST REMAINING TIME
		if (timeLimit <= 0)
			timeLimit = 0; // no more time left...


		if (s == NORTH && v2 < value)
		{ // for north, we want the least valued board state
			bestHole = i; // store the desired hole into bestHole
			value = v2;
		}
		else if (v2 > value)
		{ // for south, we want the greatest valued board state
			bestHole = i; // store the desired hole into bestHole
			value = v2;
		}
	}
	return;
}