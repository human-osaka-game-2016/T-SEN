/**
* @file Scene.h
* @brief シーンの基底クラス
* @author haga
*/
#include "GameLib/GameLib.h"
#include "Scene.h"

Scene::Scene():
m_pGameLib(&GameLib::GetInstance())
{
}

Scene::~Scene()
{
}
