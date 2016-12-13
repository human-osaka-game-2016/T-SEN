/**
* @file Battle.cpp
* @brief Battleクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "Light/Light.h"
#include "../GameData/GameDataManager.h"
#include "../GameData/GameTimer.h"
#include "../Thread/LoadingThread.h"
#include "../Field/FieldManager.h"
#include "../CameraController/CameraController.h"
#include "../Monster/MonsterManager.h"
#include "../Ship/ShipManager.h"
#include "Battle.h"

namespace sub_scene
{

Battle::Battle(GameDataManager* pGameDataManager, GameTimer* pGameTimer)
	:SubScene(pGameDataManager, pGameTimer)
{
	GameLib::Instance().CreateVtx(99, 1600.f, 900.f);
	GameLib::Instance().LoadTexEx(99, "../Resouce//tsenload3.png", 255, 0, 0, 0, false);
	LoadingThread::CreateThread(99,99);
	m_pLight = new Light(GameLib::Instance().GetDevice(), D3DXVECTOR3{ 0, 0, 0 });
	m_pMonsterManager = new MonsterManager(pGameDataManager);
	m_pFieldManager = new FieldManager();
	m_pShipManager = new ShipManager();


	ShipManager::SHIP_ID shipID[12] =
	{
		ShipManager::BATTLESHIP,
		ShipManager::CRUISER,
		ShipManager::DESTROYER,
		ShipManager::BATTLESHIP,
		ShipManager::CRUISER,
		ShipManager::DESTROYER,
		ShipManager::DESTROYER,
		ShipManager::CRUISER,
		ShipManager::DESTROYER,
		ShipManager::BATTLESHIP,
		ShipManager::CRUISER,
		ShipManager::DESTROYER
	};

	char ally = 1, enemy = 1;
	m_pShipManager->Create(&ally, &enemy, shipID);
	LoadingThread::DiscardThread();
}


Battle::~Battle()
{
	delete m_pLight;
	delete m_pFieldManager;
	delete m_pMonsterManager;
	delete m_pShipManager;
}


SUBSCENE_ID Battle::Control()
{
	m_pFieldManager->Control();
	m_pMonsterManager->Control();
	m_pShipManager->Control();
	m_pShipManager->CameraTransform();
	//GameLib::Instance().SetMousePosCenter();
	return SUBSCENE_ID::BATTLE;
}

void sub_scene::Battle::Draw()
{
	m_pShipManager->Draw();
	m_pMonsterManager->Draw();
	m_pFieldManager->Draw();
	CameraController::GetInstance().TransformView(m_pShipManager->GetCameraPos(), m_pShipManager->GetLookAtPos(), m_pShipManager->GetAngle());
	
	
}

}
