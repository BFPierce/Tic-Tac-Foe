#include "stdafx.h"
#include "GameBoard.h"

GameBoard::GameBoard(void)
	:m_rows{ 9 }, m_cols { 6 }, m_grid{ NULL }
{
	AllocateMemory();
}

GameBoard::~GameBoard(void)
{

}

int GameBoard::GetBoardColor(int row, int col)
{
	if (row < m_rows && row >= 0 && col < m_cols && col >= 0)
		return m_grid[row][col];
	else
		return -1;
}

void GameBoard::SetBoardColor(int row, int col, int index)
{
	if (row < m_rows && row >= 0 && col < m_cols && col >= 0)
		m_grid[row][col] = index;
}

void GameBoard::AllocateMemory()
{
	m_grid = new int*[m_rows];

	for (int i = 0; i < m_rows; i++)
	{
		m_grid[i] = new int[m_cols];
	}
}

void GameBoard::Initialize(void)
{
	// Setup the game board
	for (int row = 0; row < m_rows; row++)
	{
		for (int col = 0; col < m_cols; col++)
		{
			m_grid[row][col] = 0;
		}
	}

	// DEBUG: Assign a random color to the grid
	/*
	for (int row = 0; row < m_rows; row++)
	{
		for (int col = 0; col < m_cols; col++)
		{
			m_grid[row][col] = (rand() % 4);
		}
	}
	*/
}