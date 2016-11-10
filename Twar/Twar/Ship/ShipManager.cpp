#include "ShipManager.h"


//ShipManager::ShipManager(BATTLE_TYPE BattleType)
ShipManager::ShipManager()
{
	/*
	switch (BattleType)
	{
	case PLAYERvsENEMY:
		break;
	case PLAYERvsENEMYvsMONSTER:
		break;
	case PLAYERandALLYvsMONSTER:
		break;
	}
	*/
	templatePos[0] = { -250, 0, -500 };
	templatePos[1] = { -150, 0, -500 };
	templatePos[2] = {  -50, 0, -500 };
	templatePos[3] = {   50, 0, -500 };
	templatePos[4] = {  150, 0, -500 };
	templatePos[5] = {  250, 0, -500 };
	templatePos[6] = { -250, 0,  500 };
	templatePos[7] = { -150, 0,  500 };
	templatePos[8] = {  -50, 0,  500 };
	templatePos[9] = {   50, 0,  500 };
	templatePos[10] = { 150, 0,  500 };
	templatePos[11] = { 250, 0,  500 };
	m_BattleShip.LoadFbx("fbx/kongou.fbx");
	m_Cruiser.LoadFbx("fbx/kongou.fbx");
	m_Destroyer.LoadFbx("fbx/kongou.fbx");
}


ShipManager::~ShipManager()
{
	for (char i = 0; i < m_ArmyCount; i++)
	{
		delete m_Army[i];
	}
	for (char i = 0; i < m_EnemyCount; i++)
	{
		delete m_Enemy[i];
	}
}

void ShipManager::Control()
{
	for (char i = 0; i < m_ArmyCount; i++)
	{
		m_Army[i]->Control();
	}
	for (char i = 0; i < m_EnemyCount; i++)
	{
		m_Enemy[i]->Control();
	}
}

void ShipManager::Draw()
{
	for (char i = 0; i < m_ArmyCount; i++)
	{
		m_Army[i]->Draw();
	}
	for (char i = 0; i < m_EnemyCount; i++)
	{
		m_Enemy[i]->Draw();
	}
}

void ShipManager::Create(char* army, char* enemy, SHIP_ID* shipID)
{
	m_ArmyCount = *army;
	m_EnemyCount = *enemy;

	for (char i = 0; i < m_ArmyCount; i++)
	{
		Ship* tmp = NULL;

		switch (shipID[i])
		{
		case BATTLESHIP:
			tmp = new BattleShip(&templatePos[i]);
			tmp->m_pFbx = m_BattleShip.m_pModel;
//			tmp->m_pFbx->m_pModel = m_BattleShip.m_pModel;

			break;
		case CRUISER:
			tmp = new Cruiser(&templatePos[i]);
			tmp->m_pFbx = m_Cruiser.m_pModel;
			break;
		case DESTROYER:
			tmp = new Destroyer(&templatePos[i]);
			tmp->m_pFbx = m_Destroyer.m_pModel;
			break;
		case NONE:
			continue;
			break;
		}

		if (i == 0)
		{
			tmp->m_Attr = Ship::PLAYER;
		}
		else
		{
			tmp->m_Attr = Ship::ALLY;
		}
		m_Army.push_back(tmp);
	}

	for (char i = 0; i < m_EnemyCount; i++)
	{
		Ship* tmp = NULL;

		switch (shipID[i + 6])
		{
		case BATTLESHIP:
			tmp = new BattleShip(&templatePos[i + 6]);
			tmp->m_pFbx = m_BattleShip.m_pModel;
			break;
		case CRUISER:
			tmp = new Cruiser(&templatePos[i + 6]);
			tmp->m_pFbx = m_Cruiser.m_pModel;
			break;
		case DESTROYER:
			tmp = new Destroyer(&templatePos[i + 6]);
			tmp->m_pFbx = m_Destroyer.m_pModel;
			break;
		case NONE:
			continue;
			break;
		}
		tmp->m_Attr = Ship::ENEMY;
		m_Enemy.push_back(tmp);
	}
}