/**
* @file Scene.cpp
* @brief Sceneクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "Scene.h"

Scene::Scene()
	: m_rGameLib(GameLib::Instance())
{
}

Scene::~Scene()
{
}
