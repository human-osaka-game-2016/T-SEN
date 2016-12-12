/**
	@file ShipManager.cpp
	@brief ShipManagerクラスcpp
	@author kawaguchi
*/

#include "Fbx/FbxRelated.h"
#include "ShipManager.h"
#include "../Bullet/BulletManager.h"

ShipManager::ShipManager()
	: m_BattleShip(new FbxRelated)
	, m_Cruiser(new FbxRelated)
	, m_Destroyer(new FbxRelated)
	, m_pBulletManager(new BulletManager())
{
	//	仮置き
	m_TemplatePos[0] = { -250.f, -4.f, -500.f };
	m_TemplatePos[1] = { -150.f, -4.f, -500.f };
	m_TemplatePos[2] = {  -50.f, -4.f, -500.f };
	m_TemplatePos[3] = {   50.f, -4.f, -500.f };
	m_TemplatePos[4] = {  150.f, -4.f, -500.f };
	m_TemplatePos[5] = {  250.f, -4.f, -500.f };
	m_TemplatePos[6] = { -250.f, -4.f,  500.f };
	m_TemplatePos[7] = { -150.f, -4.f,  500.f };
	m_TemplatePos[8] = {  -50.f, -4.f,  500.f };
	m_TemplatePos[9] = {   50.f, -4.f,  500.f };
	m_TemplatePos[10] = { 150.f, -4.f,  500.f };
	m_TemplatePos[11] = { 250.f, -4.f,  500.f };

	if (!m_BattleShip->LoadFbx("fbx/kongou.fbx"))
	{
		// 読み込み失敗したらエラー
		MessageBox(0, "FBXファイルの読み込みに失敗しました。", NULL, MB_OK);
	}
	if (!m_Cruiser->LoadFbx("fbx/kongou.fbx"))
	{
		// 読み込み失敗したらエラー
		MessageBox(0, "FBXファイルの読み込みに失敗しました。", NULL, MB_OK);
	}
	if (!m_Destroyer->LoadFbx("fbx/kongou.fbx"))
	{
		// 読み込み失敗したらエラー
		MessageBox(0, "FBXファイルの読み込みに失敗しました。", NULL, MB_OK);
	}
	BulletManager::BULLET_ID bulletID[3] =
	{
		BulletManager::APBULLET,
	};
	char bullet = 1;
	m_pBulletManager->Create(&bullet, bulletID);
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
	delete m_BattleShip;
	delete m_Cruiser;
	delete m_Destroyer;
	delete m_pBulletManager;
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
	m_pBulletManager->Control(GetPlayerPos(),GetAngle());
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
	m_pBulletManager->Draw();
}

void ShipManager::Create(char* army, char* enemy, SHIP_ID* shipID)
{
	m_ArmyCount = *army;
	m_EnemyCount = *enemy;
	int EnemyShipIDStartPoint = 6;

	for (char i = 0; i < m_ArmyCount; i++)
	{
		Ship* tmp = nullptr;

		switch (shipID[i])
		{
		case BATTLESHIP:
			tmp = new BattleShip(&m_TemplatePos[i]);
			tmp->m_pFbx = m_BattleShip->m_pModel;
			break;
		case CRUISER:
			tmp = new Cruiser(&m_TemplatePos[i]);
			tmp->m_pFbx = m_Cruiser->m_pModel;
			break;
		case DESTROYER:
			tmp = new Destroyer(&m_TemplatePos[i]);
			tmp->m_pFbx = m_Destroyer->m_pModel;
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

	for (char i = EnemyShipIDStartPoint; i < m_EnemyCount + EnemyShipIDStartPoint; i++)
	{
		Ship* tmp = nullptr;

		switch (shipID[i])
		{
		case BATTLESHIP:
			tmp = new BattleShip(&m_TemplatePos[i]);
			tmp->m_pFbx = m_BattleShip->m_pModel;
			break;
		case CRUISER:
			tmp = new Cruiser(&m_TemplatePos[i]);
			tmp->m_pFbx = m_Cruiser->m_pModel;
			break;
		case DESTROYER:
			tmp = new Destroyer(&m_TemplatePos[i]);
			tmp->m_pFbx = m_Destroyer->m_pModel;
			break;
		case NONE:
			continue;
			break;
		}
		tmp->m_Attr = Ship::ENEMY;
		m_Enemy.push_back(tmp);
	}
}

