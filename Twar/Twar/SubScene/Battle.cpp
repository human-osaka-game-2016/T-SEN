/**
* @file Battle.cpp
* @brief Battleクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "Light/Light.h"
#include "../GameData/GameDataManager.h"
#include "../GameData/GameTimer.h"
#include "../Field/FieldManager.h"
#include "../CameraController/CameraController.h"
#include "../Thread/TestThread.h"
#include "Battle.h"

namespace sub_scene
{

	Battle::Battle(GameDataManager* pGameDataManager, GameTimer* pGameTimer)
	{
		GameLib::GetInstance().LoadTexEx(1, "../Resouce//Load.png", 255, 0, 0, 0, false);
		m_pThread = new TestThread();
		m_pThread->CreateTestThread(GameLib::GetInstance().GetTex(1));
		m_pLight = new Light(GameLib::GetInstance().GetDevice(), D3DXVECTOR3{ 0, 0, 0 });
		m_pCameraController = new CameraController();
		m_pGameDataManager = pGameDataManager;
		m_pGameTimer = pGameTimer;
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
			ShipManager::BATTLESHIP,
			ShipManager::CRUISER,
			ShipManager::DESTROYER,
			ShipManager::BATTLESHIP,
			ShipManager::CRUISER,
			ShipManager::DESTROYER
		};

		char ally = 6, enemy = 6;
		m_pShipManager->Create(&ally, &enemy, shipID);

		m_pThread->DeleteTestThread();

	}


	Battle::~Battle()
	{
		delete m_pShipManager;
		delete m_pThread;
		delete m_pFieldManager;
		delete m_pCameraController;
		delete m_pLight;
	}


	SUBSCENE_ID Battle::Control()
	{

		m_pFieldManager->Control();
		m_pCameraController->Control();
		m_pShipManager->Control();

		return SUBSCENE_ID::BATTLE;
	}

	void sub_scene::Battle::Draw()
	{
		m_pCameraController->TransformView(m_pShipManager->GetPlayerPos());
		m_pShipManager->Draw();
		m_pFieldManager->Draw();
	}
}