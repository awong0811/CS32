#include "Board.h"
#include "Side.h"


Board::Board(int nHoles, int nInitialBeansPerHole) : mnHoles(nHoles)
{ // Board constructor
	if (nHoles <= 0)
		nHoles = 1;
	if (nInitialBeansPerHole < 0)
		nInitialBeansPerHole = 0;
	north.push_back(0);
	south.push_back(0); // each pot starts out with 0
	for (int i = 0; i < nHoles; i++)
	{ // each hole starts with nInitialBeansPerHole of beans
		north.push_back(nInitialBeansPerHole);
		south.push_back(nInitialBeansPerHole);
	}
}

Board::Board(const Board& b)
{ // copy constructor
	mnHoles = b.holes();
	north = b.north;
	south = b.south;
}

int Board::holes() const
{ // return # of holes on each side
	return mnHoles;
}

int Board::beans(Side s, int hole) const
{ // returns # of beans in a specified hole on a particular side
	if (hole < 0 || hole > mnHoles)
		return -1;
	else if (s == 0)
	{
		return north[hole];
	}
	else
	{
		return south[hole];
	}
}

int Board::beansInPlay(Side s) const
{ // returns total # of beans in the holes on a specified side
	int sum = 0;
	for (int i = 1; i <= mnHoles; i++)
		if (s == NORTH)
			sum += north[i];
		else
			sum += south[i];
	return sum;
}

int Board::totalBeans() const
{ // returns total # of beans on the board
	return north[POT] + south[POT] + beansInPlay(NORTH) + beansInPlay(SOUTH);
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{ // picks up the beans in a hole and sows them
	if (hole <= POT || hole > mnHoles)
		return false; // invalid hole
	if (beans(s, hole) == 0)
			return false; // invalid hole

	int i = hole; // to keep track of what hole we are on
	int numBeans = beans(s, hole); //store the number of beans before we set to 0
	if (s == NORTH) // set the hole to 0 and determine the hole that we start dropping beans in
	{	
		north[i] = 0;
		i--;
	}
	else
	{
		south[i] = 0;
		i++;
	}
	bool sowingNorth = s==NORTH; // tells us if we're on the north or south side
	for (; numBeans > 0; numBeans--) // while we still have beans to sow...
	{
		if (!sowingNorth && i == mnHoles + 1)
		{ // if we have reached south's pot...
			i = mnHoles; // reset i to start at the rightmost hole
			sowingNorth = true; // reset sowingNorth because we will be sowing on the north side
			if (s == NORTH) // if we are team NORTH
			{
				numBeans++; // offset because we are skipping south's pot
			}
			else // then we must be team SOUTH
			{
				south[0]++; // add to your own pot
				if (numBeans == 1)
				{ // if this is out last bean, record the endSide and endHole
					endSide = SOUTH;
					endHole = 0;
				}
			}
		}
		else if (sowingNorth && i == 0)
		{ // if we are at north's pot...
			i = 1; // reset i to start at the leftmost hole
			sowingNorth = false; // reset sowingNorth because we will be sowing on south's side
			if (s == SOUTH) // if we are team SOUTH
			{
				numBeans++; // offset because we are skipping north's pot
			}
			else // then we must be team NORTH
			{
				north[0]++; // add to your own pot
				if (numBeans == 1)
				{ // check for last bean
					endSide = NORTH;
					endHole = 0;
				}
			}
		}
		else if (sowingNorth) // on the north side
		{
			north[i]++; // add to the hole
			if (numBeans == 1)
			{ // check for last bean
				endSide = NORTH;
				endHole = i;
			}
			i--; // move left			
		}
		else // on the south side
		{
			south[i]++; // add to the hole
			if (numBeans == 1)
			{ // check for last bean
				endSide = SOUTH;
				endHole = i;
			}
			i++; // move right
		}
	}

	return true;
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{ // move all the beans in a specified hole to potOwner's pot
	if (hole <= POT || hole > mnHoles)
		return false;
	int move = beans(s, hole);
	if (s == NORTH)
		north[hole] = 0;
	else
		south[hole] = 0;
	if (potOwner == NORTH)
		north[POT] += move;
	else
		south[POT] += move;
	return true;
}

bool Board::setBeans(Side s, int hole, int beans)
{ // set the # of beans in a certain hole to the desired #
	if (hole < POT || hole > mnHoles)
		return false;
	if (s == NORTH)
		north[hole] = beans;
	else
		south[hole] = beans;
	return true;
}

