#include "stdafx.h"
#include "GameEntity.h"


GameEntity::GameEntity()
{

}

GameEntity::~GameEntity()
{

}

void GameEntity::Initialize(int row, int col, int color)
{
	m_row = row;
	m_currentRow = row;
	m_col = col;
	m_currentCol = col;
	m_color = color;
}

void GameEntity::Reset()
{
	m_currentCol = m_col;
	m_currentRow = m_row;
}
