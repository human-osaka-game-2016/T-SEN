/**
* @file  FieldManager.cpp
* @brief FieldManagerクラスの実装
* @author Matsuda
*/
#include "FieldManager.h"

FieldManager::FieldManager()
	: m_pOcean(new Ocean())
	, m_pSky(new Sky())
{
}

FieldManager::~FieldManager()
{
	delete m_pOcean;
	delete m_pSky;
}

void FieldManager::Control()
{
	m_pOcean->Control();
	m_pSky->Control();
}

void FieldManager::Draw()
{
	m_pOcean->Draw();
	m_pSky->Draw();
}
