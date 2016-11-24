#include "ShipManager.h"

ShipManager::ShipManager()
{
	RECT movebleRange { 0, 0, 1600, 900 };
	ClipCursor(&movebleRange);
	SetCursorPos(800, 450);
	ShowCursor(false);

	m_TemplatePos[0] = { -250, -4, -500 };
	m_TemplatePos[1] = { -150, -4, -500 };
	m_TemplatePos[2] = {  -50, -4, -500 };
	m_TemplatePos[3] = {   50, -4, -500 };
	m_TemplatePos[4] = {  150, -4, -500 };
	m_TemplatePos[5] = {  250, -4, -500 };
	m_TemplatePos[6] = { -250, -4,  500 };
	m_TemplatePos[7] = { -150, -4,  500 };
	m_TemplatePos[8] = {  -50, -4,  500 };
	m_TemplatePos[9] = {   50, -4,  500 };
	m_TemplatePos[10] = { 150, -4,  500 };
	m_TemplatePos[11] = { 250, -4,  500 };
	if (!m_BattleShip.LoadFbx("fbx/kongou.fbx"))
	{
		// 読み込み失敗したらエラー
		MessageBox(0, "FBXファイルの読み込みに失敗しました。", NULL, MB_OK);
	}
	if (!m_Cruiser.LoadFbx("fbx/tama3.fbx"))
	{
		// 読み込み失敗したらエラー
		MessageBox(0, "FBXファイルの読み込みに失敗しました。", NULL, MB_OK);
	}
	if (!m_Destroyer.LoadFbx("fbx/kongou.fbx"))
	{
		// 読み込み失敗したらエラー
		MessageBox(0, "FBXファイルの読み込みに失敗しました。", NULL, MB_OK);
	}
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
	ShowCursor(true);
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
			tmp = new BattleShip(&m_TemplatePos[i]);
			tmp->m_pFbx = m_BattleShip.m_pModel;
			break;
		case CRUISER:
			tmp = new Cruiser(&m_TemplatePos[i]);
			tmp->m_pFbx = m_Cruiser.m_pModel;
			break;
		case DESTROYER:
			tmp = new Destroyer(&m_TemplatePos[i]);
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
			tmp = new BattleShip(&m_TemplatePos[i + 6]);
			tmp->m_pFbx = m_BattleShip.m_pModel;
			break;
		case CRUISER:
			tmp = new Cruiser(&m_TemplatePos[i + 6]);
			tmp->m_pFbx = m_Cruiser.m_pModel;
			break;
		case DESTROYER:
			tmp = new Destroyer(&m_TemplatePos[i + 6]);
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