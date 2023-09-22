#ifndef BOARD_H
#define BOARD_H

#include "Side.h"
#include <stdlib.h>
#include <vector>

class Board {
public:
	Board(int nHoles, int nInitialBeansPerHole);
	Board(const Board& b); // copy constructor
	int holes() const;
	int beans(Side s, int hole) const;
	int beansInPlay(Side s) const;
	int totalBeans() const;
	bool sow(Side s, int hole, Side& endSide, int& endHole);
	bool moveToPot(Side s, int hole, Side potOwner);
	bool setBeans(Side s, int hole, int beans);

private:
	int mnHoles;
	std::vector<int> north;
	std::vector<int> south;
};



#endif
