#pragma once
#include "GameBoard.h"
#include "GameEntity.h"

#include "time.h"
#include <vector>

class Engine
{
private:
	GameBoard m_gameBoard;
	GameEntity m_computerPlayer;
	GameEntity m_humanPlayer;

	int m_playerScore;
	int m_computerScore;

	COLORREF m_colors[4];

	int m_blockWidth{ 65 };

	LONGLONG m_nextUpdate{ 0 };
	DWORD m_updateWidth{ 800 };

	LONGLONG m_nextDrawUpdate{ 0 };
	DWORD m_drawWidth{ 100 };

	void UpdateEntities();
	void UpdateBoard();
	void UpdateAI();

	void SetupLevel();

	bool isValidMove(int row, int col);

public:
	Engine(void);
	~Engine(void);

	void SetupGame();
	void Update(HWND);
	void ProcessInput(WPARAM, HWND);

	void Render(HDC);

	int GetWindowHeight() { return m_gameBoard.GetRowCount() * m_blockWidth + 4 * m_blockWidth; };
	int GetWindowWidth() { return m_gameBoard.GetColCount() * m_blockWidth + 4 * m_blockWidth; };
	

};

