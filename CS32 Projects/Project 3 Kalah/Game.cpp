#include "Game.h"
#include <iostream>
Game::Game(const Board& b, Player* south, Player* north) : mBoard(b)
{
	mSouth = south;
	mNorth = north;
}

void Game::display() const
{ // creates the display line by line
	std::string Nname = mNorth->name(), Sname = mSouth->name();
	int spaceLength = Nname.length() + 12; // stores North's name's length to figure out how much to space the numbers away from the left side
	for (int i = 0; i < spaceLength + 3*(mBoard.holes()/2 - 1); i++)
		std::cout << " ";
	std::cout << Nname << std::endl; // end of line 1
	for (int i = 0; i < spaceLength-2; i++)
		std::cout << " ";
	for (int i = 0; i < mBoard.holes(); i++)
	{
		std::cout << "  " << i + 1;
	}
	std::cout << std::endl; // end of line 2
	for (int i = 0; i < spaceLength; i++)
		std::cout << " ";
	for (int i = 0; i < mBoard.holes()-1; i++)
		std::cout << "---";
	std::cout << "-" << std::endl; // end of line 3
	for (int i = 0; i < spaceLength - 2; i++)
		std::cout << " ";
	for (int i = 0; i < mBoard.holes(); i++)
	{
		std::cout << "  " << mBoard.beans(NORTH, i + 1);
	}
	std::cout << std::endl; // end of line 4
	std::cout << Nname << "'s pot  " << mBoard.beans(NORTH, 0) << "  ";
	for (int i = 0; i < mBoard.holes(); i++)
		std::cout << "   ";
	std::cout << "  " << mBoard.beans(SOUTH, 0) << "  " << Sname << "'s pot" << std::endl; //end of line 5
	for (int i = 0; i < spaceLength - 2; i++)
		std::cout << " ";
	for (int i = 0; i < mBoard.holes(); i++)
	{
		std::cout << "  " << mBoard.beans(SOUTH, i + 1);
	}
	std::cout << std::endl; // end of line 6
	for (int i = 0; i < spaceLength; i++)
		std::cout << " ";
	for (int i = 0; i < mBoard.holes() - 1; i++)
		std::cout << "---";
	std::cout << "-" << std::endl; // end of line 7
	for (int i = 0; i < spaceLength - 2; i++)
		std::cout << " ";
	for (int i = 0; i < mBoard.holes(); i++)
	{
		std::cout << "  " << i + 1;
	}
	std::cout << std::endl; // end of line 8
	for (int i = 0; i < spaceLength + 3 * (mBoard.holes() / 2 - 1); i++)
		std::cout << " ";
	std::cout << Sname << std::endl; // end of line 1
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
{ // checks the status of the game to see if it's over or not
	if (mBoard.beansInPlay(NORTH) == 0 && mBoard.beansInPlay(SOUTH) == 0)
	{ // game over...
		over = true;
		if (mBoard.beans(SOUTH, 0) == mBoard.beans(NORTH, 0))
			hasWinner = false; // tie
		else
		{
			hasWinner = true;
			if (mBoard.beans(SOUTH, 0) > mBoard.beans(NORTH, 0))
				winner = SOUTH;
			else
				winner = NORTH; // assign the winner
		}
	}
	else
		over = false; // there are still beans in play, not over...
}

bool Game::move(Side s)
{
	Side opponent;
	if (s == NORTH)
		opponent = SOUTH;
	else
		opponent = NORTH; // set the opponent
	Side endSide; // keeping track of your endHole and endSide to see if you get additional turns
	int endHole;
	if (mBoard.beansInPlay(s) == 0)
	{ // if no more beans on your side, end the game
		for (int i = 1; i <= mBoard.holes(); i++)
			mBoard.moveToPot(opponent, i, opponent); // move all of opponent's beans to opponent's side
		display();
		std::cout << "Game over!" << std::endl;
		return false;
	}
	if (s == NORTH)
		mBoard.sow(NORTH, mNorth->chooseMove(mBoard, NORTH), endSide, endHole);
	else // make the move
		mBoard.sow(SOUTH, mSouth->chooseMove(mBoard, SOUTH), endSide, endHole);
	if (endSide == s && endHole == POT)
	{ // ended in own pot, additional turn by recursive call
		display();
		std::cout << "You get an additional move!" << std::endl;
		move(s);
		return true;
	}
	if (endSide == s && mBoard.beans(s, endHole) == 1 && mBoard.beans(opponent, endHole) != 0)
	{ // capturing
		mBoard.moveToPot(SOUTH, endHole, s);
		mBoard.moveToPot(NORTH, endHole, s);
		display();
		std::cout << "Captured!" << std::endl;
		return true;
	}
	display(); // default, nothing special happens
	std::cout << "A move was made!" << std::endl;
	return true;
}

void Game::play()
{
	std::cout << "Welcome to Kalah!" << std::endl;
	display();
	std::cout << "The game has started. " << mSouth->name() << " goes first!" << std::endl;
	bool over = false, hasWinner = false;
	Side winner;
	for (int turns = 0; !over; turns++)
	{
		status(over, hasWinner, winner); //check status at the beginning of every round
		if (over)
			break; // if the game is over, no need to make south and north choose a move
		move(SOUTH); // south and north take their turns; south goes first
		move(NORTH);
		if (turns % 5 == 0)
		{
			system("pause"); // after a number of turns, pause
		}
	}
	if (!hasWinner)
		std::cout << "It's a tie!" << std::endl;
	else if (winner == SOUTH)
		std::cout << mSouth->name() << " is the winner!" << std::endl;
	else
		std::cout << mNorth->name() << " is the winner!" << std::endl;
}

int Game::beans(Side s, int hole) const
{ // returns # of beans in a certain hole
	if (hole < POT || hole > mBoard.holes())
		return -1;
	return mBoard.beans(s, hole);
}
