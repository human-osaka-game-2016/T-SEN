#include "FieldManager.h"


FieldManager::FieldManager()
{
}


FieldManager::~FieldManager()
{
}

void FieldManager::Control()
{
	m_Ocene->Control();
	m_Sky->Control();
}

void FieldManager::Draw()
{
	m_Ocene->Draw();
	m_Sky->Draw();
}