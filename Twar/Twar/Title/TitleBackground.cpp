/**
* @file		TitleBackground.cpp
* @brief	TitleBackgroundクラス実装
* @author	haga
*/

#include "GameLib/GameLib.h"
#include "TitleCommonDeclaration.h"
#include "TitleBackground.h"

TitleBackground::TitleBackground()
{
	GameLib::Instance().CreateVtx(title_scene::BACKGROUND,1600.f,900.f);
}

TitleBackground::~TitleBackground()
{
}

// 描画関数
void TitleBackground::Draw()
{
	GameLib::Instance().DrawXY(title_scene::TITLE_BACKGROUND, title_scene::BACKGROUND, 0.0f, 0.0f);
}