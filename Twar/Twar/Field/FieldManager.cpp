/**
* @file  FieldManager.cpp
* @brief FieldManagerクラスの実装
* @author Matsuda
*/
#include "FieldManager.h"

FieldManager::FieldManager()
{
	m_Ocean = new Ocean();
	m_Sky = new Sky();
}

FieldManager::~FieldManager()
{
	delete m_Ocean;
	delete m_Sky;
}

void FieldManager::Control()
{
	m_Ocean->Control();
	m_Sky->Control();
}

void FieldManager::Draw()
{
	m_Ocean->Draw();
	m_Sky->Draw();
}
