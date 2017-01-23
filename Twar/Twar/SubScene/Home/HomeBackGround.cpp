/**
* @file		HomeBackground.cpp
* @brief	HomeBackgroundクラス実装
* @author	haga
*/

//------------------------------------------------------------------------------------------------------------//
//Includes
//------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "HomeBackground.h"
#include "Home.h"

//------------------------------------------------------------------------------------------------------------//
//Public functions
//------------------------------------------------------------------------------------------------------------//

HomeBackground::HomeBackground()
	: m_Pos({ 0.0f, 0.0f })
{
	GameLib::Instance().CreateVtx(sub_scene::Home::BACKGROUND_VTX,
		GameLib::Instance().GetWindowWidth(), GameLib::Instance().GetWindowHeight());
}

HomeBackground::~HomeBackground()
{
	// リソース解放はHomeシーンにて行う
}

void HomeBackground::Draw()
{
	GameLib::Instance().DrawXY(sub_scene::Home::BACKGROUND_TEX, sub_scene::Home::BACKGROUND_VTX, m_Pos.x, m_Pos.y);
}
