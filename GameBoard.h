#pragma once

class GameBoard
{

public:
	GameBoard(void);
	~GameBoard(void);	

	int GetRowCount() { return m_rows; };
	int GetColCount() { return m_cols; };

	int GetBoardColor(int row, int col);
	void SetBoardColor(int row, int col, int index);

	void Initialize(void);

private:
	
	void AllocateMemory(void);
	int m_rows, m_cols;
	int** m_grid;

};