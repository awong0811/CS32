#include "History.h"
#include "globals.h"
History::History(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;
	for (int r = 0; r < m_rows; r++)
		for (int c = 0; c < m_cols; c++)
			m_grid[r][c] = 0;
}

bool History::record(int r, int c)
{
	if (r <= 0 || c <= 0 || r > m_rows || r > m_cols)
		return false;
	else
		m_grid[r-1][c-1]++;
	return true;
}


void History::display() const
{
	clearScreen();
	char displayGrid[MAXROWS][MAXCOLS];
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			if (m_grid[i][j] == 0)
				displayGrid[i][j] = '.';
			else if (m_grid[i][j] > 26)
				displayGrid[i][j] = 'Z';
			else
				displayGrid[i][j] = 64 + m_grid[i][j];
		}
	}

	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
			cout << displayGrid[i][j];
		cout << endl;
	}
	cout << endl;
}
