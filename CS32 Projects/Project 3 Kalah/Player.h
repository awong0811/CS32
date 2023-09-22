#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Board.h"
#include "Side.h"
#include <iostream>
//========================================================================
// Timer t;                 // create and start a timer
// t.start();               // restart the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

#include <chrono>
using namespace std;
class Timer
{
public:
	Timer()
	{
		start();
	}
	void start()
	{
		m_time = std::chrono::high_resolution_clock::now();
	}
	double elapsed() const
	{
		std::chrono::duration<double, std::milli> diff =
			std::chrono::high_resolution_clock::now() - m_time;
		return diff.count();
	}
private:
	std::chrono::high_resolution_clock::time_point m_time;
};

// Advance jumpy timer only after jumpInterval calls to elapsed
class JumpyTimer
{
public:
	JumpyTimer(int jumpInterval)
		: m_jumpInterval(jumpInterval), m_callsMade(0)
	{
		actualElapsed();
	}
	double elapsed()
	{
		m_callsMade++;
		if (m_callsMade == m_jumpInterval)
		{
			m_lastElapsed = m_timer.elapsed();
			m_callsMade = 0;
		}
		return m_lastElapsed;
	}
	double actualElapsed()
	{
		m_lastElapsed = m_timer.elapsed();
		return m_lastElapsed;
	}
private:
	Timer m_timer;
	int m_jumpInterval;
	int m_callsMade;
	int m_lastElapsed;
};

//========================================================================

class Player
{
public:
	Player(std::string name);
	std::string name() const;
	virtual bool isInteractive() const;
	virtual int chooseMove(const Board& b, Side s) const = 0;
	virtual ~Player();

private:
	std::string mname;
};

class HumanPlayer : public Player
{
public:
	HumanPlayer(std::string name);
	virtual bool isInteractive() const;
	virtual int chooseMove(const Board& b, Side s) const;
};

class BadPlayer : public Player
{
public:
	BadPlayer(std::string name);
	virtual int chooseMove(const Board& b, Side s) const;
};

class SmartPlayer : public Player
{
public:
	SmartPlayer(std::string name);
	virtual int chooseMove(const Board& b, Side s) const;
private:
	int eval(const Board& b, Side s) const; // evaluation function
	void chooseMove(const Board& b, Side s, int depth, int& bestHole, int& value, double timeLimit, JumpyTimer& timer, unsigned long& result) const; // chooseMove helper that does all the actual work
};

#endif
