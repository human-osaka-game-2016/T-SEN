/**
* @file Battle.cpp
* @brief Battleクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "Light/Light.h"
#include "../../GameData/GameDataManager.h"
#include "../../GameData/GameTimer.h"
#include "../../Thread/LoadingThread.h"
#include "Field/FieldManager.h"
#include "CameraController/CameraController.h"
#include "Monster/MonsterManager.h"
#include "Ship/ShipManager.h"
#include "Effect/EffectManager.h"
#include "Collision/CollisionManager.h"
#include "Battle.h"

namespace sub_scene
{

Battle::Battle(GameDataManager* pGameDataManager, GameTimer* pGameTimer)
	:SubScene(pGameDataManager, pGameTimer)
{
	GameLib::Instance().CreateVtx(LOAD_THREAD_VTX, 1600.f, 900.f);
	GameLib::Instance().LoadTexEx(LOAD_THREAD_TEX, "../Resouce/BattleScene/Thread/tsenLoad.png", 255, 0, 0, 0, false);
	LoadingThread::CreateThread(LOAD_THREAD_TEX, LOAD_THREAD_VTX);

	/**@todo  ここの数値は仮置き*/
	GameLib::Instance().LoadTex(EXPLOSION_TEX, "../Resouce/BattleScene/Effect/Effect.dds");
	GameLib::Instance().CreateVtx(EXPLOSION_VTX, 200.f, 200.f);
	EffectManager::Instance().RegisterID(EffectManager::EXPLOSION, EXPLOSION_TEX, EXPLOSION_VTX);
	
	m_pLight = new Light(GameLib::Instance().GetDevice(), D3DXVECTOR3{ 0, 0, 0 });
	m_pMonsterManager = new MonsterManager(pGameDataManager);
	m_pFieldManager = new FieldManager();
	m_pShipManager = new ShipManager();
	m_pCollisionManager = new CollisionManager(m_pShipManager, m_pMonsterManager, m_pShipManager->GetBulletManager());
	

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

	char ally = 2, enemy = 2;
	m_pShipManager->Create(&ally, &enemy, shipID);
	LoadingThread::DiscardThread();
}


Battle::~Battle()
{
	EffectManager::Instance().ReleaseID();
	delete m_pCollisionManager;
	delete m_pLight;
	delete m_pFieldManager;
	delete m_pMonsterManager;
	delete m_pShipManager;
}


SUBSCENE_ID Battle::Control()
{
	m_pCollisionManager->Control();
	m_pFieldManager->Control();
	m_pMonsterManager->Control();
	EffectManager::Instance().Control();
	m_pShipManager->Control();
	m_pShipManager->CameraTransform();
	GameLib::Instance().SetMousePosCenter();
	return SUBSCENE_ID::BATTLE;
}

void sub_scene::Battle::Draw()
{
	CameraController::GetInstance().TransformView(m_pShipManager->GetCameraPos(), m_pShipManager->GetLookAtPos(), m_pShipManager->GetAngle());
	m_pShipManager->Draw();
	EffectManager::Instance().Draw();
	m_pMonsterManager->Draw();
	m_pFieldManager->Draw();
}

}
