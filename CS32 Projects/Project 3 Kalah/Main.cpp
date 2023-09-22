#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

void doGameTests()
{
	BadPlayer bp1("Bart");
	BadPlayer bp2("Homer");
	Board b(3, 0);
	b.setBeans(SOUTH, 1, 2);
	b.setBeans(NORTH, 2, 1);
	b.setBeans(NORTH, 3, 2);
	Game g(b, &bp1, &bp2);
	bool over;
	bool hasWinner;
	Side winner;
	//    Homer
	//   0  1  2
	// 0         0
	//   2  0  0
	//    Bart
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
		g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

	g.move(SOUTH);
	//   0  1  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

	g.move(NORTH);
	//   1  0  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	cerr << g.beans(NORTH, POT) <<endl << g.beans(SOUTH, POT) << endl;
	cerr << g.beans(NORTH, 1) << endl << g.beans(NORTH, 2) << endl;
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

	g.move(SOUTH);
	//   1  0  0
	// 0         3
	//   0  0  1
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

	g.move(NORTH);
	//   0  0  0
	// 1         4
	//   0  0  0
	g.status(over, hasWinner, winner);
	assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
	assert(hasWinner && winner == SOUTH);
}

int main()
{
	Board board(6, 4); // playing the actual game
	SmartPlayer sp("Test");
	HumanPlayer hp("Wong");
	Game game(board, &sp, &hp);
	game.play();
}

//int main()
//{
//	//Board tests
//	Board a(6, 4);
//	assert(a.holes() == 6); // testing holes()
//	Side endSide;
//	int endHole;
//	assert(a.sow(NORTH, 4, endSide, endHole)); // testing sow
//	assert(a.totalBeans() == 48); // testing totalBeans
//	assert(endSide == NORTH);
//	assert(endHole == 0); // should end up in north pot
//	assert(a.beans(NORTH, 1) == a.beans(NORTH, 3)); // both should equal 5
//	assert(a.sow(SOUTH, 5, endSide, endHole)); // testing if it wraps around to the north side
//	assert(endSide == NORTH);
//	assert(endHole == 5); // should end up in north's 5th hole
//	assert(a.beans(NORTH, 5) == 5); // north's 5th hole should have 5 beans
//
//	//Player tests for HumanPlayer and BadPlayer
//	HumanPlayer hp("tinytony");
//	BadPlayer bp("leftmost");
//	assert(hp.name() == "tinytony"); // testing name()
//	assert(bp.name() == "leftmost");
//	int move = hp.chooseMove(a, NORTH);
//	assert(move == 1); // testing if input works
//	assert(bp.chooseMove(a, NORTH) == 1); // testing if bot chooses leftmost non-empty hole
//
//	//Game tests
//	HumanPlayer* hptr = &hp;
//	BadPlayer* bptr = &bp;
//	a.setBeans(SOUTH, 4, 1);
//	a.setBeans(NORTH, 1, 1);
//	Game game(a, hptr, bptr); // testing game constructor
//	game.display(); // testing display
//	assert(game.move(NORTH)); // testing additional move; bot moves twice
//	assert(game.move(SOUTH)); // testing capture and moveToPot
//	assert(game.beans(NORTH, 0) == 3 && game.beans(SOUTH, 0) == 7 && game.beans(SOUTH, 3) == 5 && game.beans(SOUTH, 5) == 0);
//	//testing if additional move and capture worked correctly
//	bool over = false, hasWinner = false;
//	Side s;
//	game.status(over, hasWinner, s);
//	assert(!over && !hasWinner); // test for status as well as beansInPlay
//}