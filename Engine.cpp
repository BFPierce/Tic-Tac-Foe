#include "stdafx.h"
#include "Engine.h"

Engine::Engine(void)
{
	// Setup the first update
	m_nextUpdate = clock();
	m_nextDrawUpdate = clock();

	// Colors used for drawing the game pieces
	m_colors[0] = RGB(0, 0, 0);
	m_colors[1] = RGB(0, 77, 201);
	m_colors[2] = RGB(214, 0, 24);
	m_colors[3] = RGB(165, 165, 165);
}

Engine::~Engine(void) 
{

}

void Engine::SetupGame()
{
	m_gameBoard.Initialize();
	m_computerPlayer.Initialize(0, 0, 1);
	m_humanPlayer.Initialize(0, 5, 2);

	SetupLevel();
}

void Engine::SetupLevel()
{
	int rows = m_gameBoard.GetRowCount();
	int cols = m_gameBoard.GetColCount();

	srand(time(NULL));

	for (int i = 4; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			// 25% chance to set a block to null space
			if (rand() % 4 == 0)
			{
				m_gameBoard.SetBoardColor(i, j, 3);
			}
		}
	}
}

void Engine::Update(HWND window)
{	
	LONGLONG currentTime = clock();
	
	// Check for main update 
	if (currentTime > m_nextUpdate)
	{
		UpdateEntities();		
		UpdateAI();
		UpdateBoard();

		// If we're behind drop an update
		if (m_nextUpdate < currentTime)
			m_nextUpdate = currentTime + m_updateWidth;

		RedrawWindow(window, NULL, NULL, RDW_INVALIDATE);
	}

	// Check for draw update
	/*
	if (currentTime > m_nextDrawUpdate)
	{
		RedrawWindow(window, NULL, NULL, RDW_INVALIDATE);

		// If we're behind drop an update
		if (m_nextDrawUpdate < currentTime)
			m_nextDrawUpdate = currentTime + m_drawWidth;
	}
	*/
}

void Engine::UpdateEntities()
{
	if (isValidMove(m_computerPlayer.GetRow() + 1, m_computerPlayer.GetCol()))
	{
		m_computerPlayer.Translate(1, 0);		
	}
	else
	{
		m_gameBoard.SetBoardColor(m_computerPlayer.GetRow(), m_computerPlayer.GetCol(), m_computerPlayer.GetColor());
		m_computerPlayer.Reset();
	}

	if (isValidMove(m_humanPlayer.GetRow() + 1, m_humanPlayer.GetCol()))
	{
		m_humanPlayer.Translate(1,0);		
	}
	else
	{
		m_gameBoard.SetBoardColor(m_humanPlayer.GetRow(), m_humanPlayer.GetCol(), m_humanPlayer.GetColor());
		m_humanPlayer.Reset();		
	}
}

void Engine::UpdateBoard()
{
	int rows = m_gameBoard.GetRowCount();
	int cols = m_gameBoard.GetColCount();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (m_gameBoard.GetBoardColor(i, j) != 0
				&& m_gameBoard.GetBoardColor(i, j) != 3)
			{

				COLORREF center = m_colors[m_gameBoard.GetBoardColor(i, j)];

				bool entitiesCleared = false;

				//Check up/down
				if (m_colors[m_gameBoard.GetBoardColor(i - 1, j)] == center &&
					m_colors[m_gameBoard.GetBoardColor(i + 1, j)] == center)
				{
					m_gameBoard.SetBoardColor(i - 1, j, 0);
					m_gameBoard.SetBoardColor(i + 1, j, 0);
					entitiesCleared = true;
				}

				//Check left diag
				if (m_colors[m_gameBoard.GetBoardColor(i - 1, j - 1)] == center &&
					m_colors[m_gameBoard.GetBoardColor(i + 1, j + 1)] == center)
				{
					m_gameBoard.SetBoardColor(i - 1, j - 1, 0);
					m_gameBoard.SetBoardColor(i + 1, j + 1, 0);
					entitiesCleared = true;
				}

				//Check left right
				if (m_colors[m_gameBoard.GetBoardColor(i, j - 1)] == center &&
					m_colors[m_gameBoard.GetBoardColor(i, j + 1)] == center)
				{
					m_gameBoard.SetBoardColor(i, j - 1, 0);
					m_gameBoard.SetBoardColor(i, j + 1, 0);
					entitiesCleared = true;
				}

				//check right diag
				if (m_colors[m_gameBoard.GetBoardColor(i - 1, j + 1)] == center &&
					m_colors[m_gameBoard.GetBoardColor(i + 1, j - 1)] == center)
				{
					m_gameBoard.SetBoardColor(i - 1, j + 1, 0);
					m_gameBoard.SetBoardColor(i + 1, j - 1, 0);
					entitiesCleared = true;
				}

				if (entitiesCleared)
					m_gameBoard.SetBoardColor(i, j, 0);
			}
		}
	}
}

void Engine::UpdateAI()
{
	// Give a random direction to the computer player
	srand(time(NULL));

	if (rand() % 2)
	{
		if(isValidMove(m_computerPlayer.GetRow(), m_computerPlayer.GetCol() + 1))
			m_computerPlayer.Translate(0, 1);
	}
	else
	{
		if(isValidMove(m_computerPlayer.GetRow(), m_computerPlayer.GetCol() - 1))
			m_computerPlayer.Translate(0, -1);
	}
}

void Engine::ProcessInput(WPARAM wParam, HWND window)
{

	switch (wParam)
	{
		case VK_LEFT:
		{
			if (isValidMove(m_humanPlayer.GetRow(), m_humanPlayer.GetCol() - 1))
			{
				m_humanPlayer.Translate(0, -1);
			}
			break;
		}
		case VK_RIGHT:
		{
			if (isValidMove(m_humanPlayer.GetRow(), m_humanPlayer.GetCol() + 1))
			{
				m_humanPlayer.Translate(0, 1);
			}
			break;
		}
		case VK_DOWN:
		{
			if (isValidMove(m_humanPlayer.GetRow() + 1, m_humanPlayer.GetCol()))
			{
				m_humanPlayer.Translate(1, 0);
			}
			break;
		}
	}

	RedrawWindow(window, NULL, NULL, RDW_INVALIDATE);
}

bool Engine::isValidMove(int row, int col)
{
	if (row >= m_gameBoard.GetRowCount())
		return false;

	if (col >= m_gameBoard.GetColCount())
		return false;

	if (m_gameBoard.GetBoardColor(row, col) != 0)
		return false;

	if (row == m_humanPlayer.GetRow() && col == m_humanPlayer.GetCol())
		return false;

	if (row == m_computerPlayer.GetRow() && col == m_computerPlayer.GetCol())
		return false;

	return true;
}


//================================================================================================
// Graphics Code - Possible refactor here
//================================================================================================
void Engine::Render(HDC hdc)
{
	HBRUSH br;
	HPEN pn;


	// Render the board
	for (int row = 0; row < m_gameBoard.GetRowCount(); row++)
	{
		for (int col = 0; col < m_gameBoard.GetColCount(); col++)
		{
			br = CreateSolidBrush(m_colors[m_gameBoard.GetBoardColor(row, col)]);
			pn = CreatePen(PS_ALTERNATE, 1, RGB(167, 167, 167));

			SelectObject(hdc, br);
			SelectObject(hdc, pn);

			Rectangle(hdc, 
				col * m_blockWidth, 
				row * m_blockWidth,
				col * m_blockWidth + m_blockWidth,
				row * m_blockWidth + m_blockWidth);

			DeleteObject(br);
			DeleteObject(pn);
		}
	}

	// Render the human player
	br = CreateSolidBrush(m_colors[m_humanPlayer.GetColor()]);
	pn = CreatePen(PS_ALTERNATE, 1, RGB(255, 255, 255));

	SelectObject(hdc, br);
	SelectObject(hdc, pn);

	Rectangle(hdc,
		m_humanPlayer.GetCol() * m_blockWidth,
		m_humanPlayer.GetRow() * m_blockWidth,
		m_humanPlayer.GetCol() * m_blockWidth + m_blockWidth,
		m_humanPlayer.GetRow() * m_blockWidth + m_blockWidth);

	DeleteObject(br);
	DeleteObject(pn);

	// Render the computer player
	br = CreateSolidBrush(m_colors[m_computerPlayer.GetColor()]);
	pn = CreatePen(PS_ALTERNATE, 1, RGB(255, 255, 255));

	SelectObject(hdc, br);
	SelectObject(hdc, pn);

	Rectangle(hdc,
		m_computerPlayer.GetCol() * m_blockWidth,
		m_computerPlayer.GetRow() * m_blockWidth,
		m_computerPlayer.GetCol() * m_blockWidth + m_blockWidth,
		m_computerPlayer.GetRow() * m_blockWidth + m_blockWidth);

	DeleteObject(br);
	DeleteObject(pn);
}

