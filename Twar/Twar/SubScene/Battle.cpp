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
#include "../Effect/EffectManager.h"
#include "../Collision/CollisionManager.h"
#include "Battle.h"

namespace sub_scene
{

Battle::Battle(GameDataManager* pGameDataManager, GameTimer* pGameTimer)
	:SubScene(pGameDataManager, pGameTimer)
{
	GameLib::Instance().CreateVtx(LOAD_THREAD_VTX, 1600.f, 900.f);
	GameLib::Instance().LoadTexEx(LOAD_THREAD_TEX, "../Resouce//tsenload3.png", 255, 0, 0, 0, false);
	LoadingThread::CreateThread(LOAD_THREAD_TEX, LOAD_THREAD_VTX);

	/**@todo  ここの数値は仮置き*/
	GameLib::Instance().LoadTex(EXPLOSION_TEX, "../Resouce/Effect.dds");
	GameLib::Instance().CreateVtx(EXPLOSION_VTX, 100.f, 100.f);
	GameLib::Instance().SetVtxUV(EXPLOSION_VTX, 0.0f, 0.25f, 0.0f, 0.25f);
	EffectManager::Instance().RegisterID(EffectManager::EXPLOSION, EXPLOSION_TEX, EXPLOSION_VTX);
	
	m_pLight = new Light(GameLib::Instance().GetDevice(), D3DXVECTOR3{ 0, 0, 0 });
	m_pMonsterManager = new MonsterManager(pGameDataManager);
	m_pFieldManager = new FieldManager();
	m_pShipManager = new ShipManager();


	ShipManager::SHIP_ID shipID[12] =
	{
		ShipManager::DESTROYER,
		ShipManager::CRUISER,
		ShipManager::BATTLESHIP,
		ShipManager::DESTROYER,
		ShipManager::CRUISER,
		ShipManager::BATTLESHIP,
		ShipManager::DESTROYER,
		ShipManager::CRUISER,
		ShipManager::BATTLESHIP,
		ShipManager::DESTROYER,
		ShipManager::CRUISER,
		ShipManager::DESTROYER
	};

	char ally = 3, enemy = 3;
	m_pShipManager->Create(&ally, &enemy, shipID);
	LoadingThread::DiscardThread();
}


Battle::~Battle()
{
	EffectManager::Instance().ReleaseID();
	delete m_pLight;
	delete m_pFieldManager;
	delete m_pMonsterManager;
	delete m_pShipManager;
}


SUBSCENE_ID Battle::Control()
{
	m_rGameLib.GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	//m_rGameLib.GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	//m_rGameLib.GetDevice()->SetRenderState(D3DRS_AMBIENT, 0x00555555);
	//m_rGameLib.GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	CollisionManager::Instance().ClearData();
	m_pFieldManager->Control();
	if(m_pMonsterManager->Control())
	{
		return SUBSCENE_ID::BATTLE_RESULT;
	}
	EffectManager::Instance().Control();
	m_pShipManager->Control();
	m_pShipManager->CameraTransform();
	GameLib::Instance().SetMousePosCenter();
	CollisionManager::Instance().CheckCollision();

	return SUBSCENE_ID::BATTLE;

}

void sub_scene::Battle::Draw()
{
	CameraController::GetInstance().TransformView(m_pShipManager->GetCameraPos(), m_pShipManager->GetLookAtPos(), m_pShipManager->GetAngle());
	m_pShipManager->Draw();
	
	m_pMonsterManager->Draw();
	m_pFieldManager->Draw();
	EffectManager::Instance().Draw();
}

}
