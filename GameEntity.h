#pragma once
class GameEntity
{
private:
	int m_row;
	int m_col;
	int m_color;

	int m_currentRow;
	int m_currentCol;

public:
	GameEntity();
	~GameEntity();

	void Initialize(int row, int col, int color);
	void Reset();

	int GetRow() { return m_currentRow; };
	int GetCol() { return m_currentCol; };
	int GetColor() { return m_color; };

	void Translate(int row, int col) { m_currentRow += row; m_currentCol += col; };

};

