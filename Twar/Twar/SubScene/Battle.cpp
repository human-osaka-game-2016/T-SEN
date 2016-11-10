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
#include "Battle.h"

namespace sub_scene
{

	Battle::Battle(GameDataManager* pGameDataManager,FieldManager* pFieldManager, GameTimer* pGameTimer)
{
	m_pLight = new Light(GameLib::GetInstance().GetDevice(), D3DXVECTOR3{ 0, 0, 0 });
	m_pCameraController = new CameraController();
	m_pGameDataManager = pGameDataManager;
	m_pFieldManager = pFieldManager;
	m_pGameTimer = pGameTimer;
	m_pFieldManager = new FieldManager();
}


Battle::~Battle()
{
	delete m_pFieldManager;
	delete m_pCameraController;
}


SUBSCENE_ID Battle::Control()
{
	m_pCameraController->Control();
	m_pFieldManager->Control();

	return SUBSCENE_ID::BATTLE;
}

void sub_scene::Battle::Draw()
{
	m_pFieldManager->Draw();
}

}