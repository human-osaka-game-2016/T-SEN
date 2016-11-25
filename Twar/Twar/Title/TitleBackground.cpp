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
	// ウィンドウサイズ(クライアント領域)を求めて背景のサイズにする
	float cliantWidthSize = static_cast<float>( GameLib::Instance().GetWindowWidth() );
	float cliantHeightSize = static_cast<float>( GameLib::Instance().GetWindowHeight() );
	GameLib::Instance().CreateVtx(title_scene::BACKGROUND, cliantWidthSize, cliantHeightSize);
}

TitleBackground::~TitleBackground()
{
}

// 描画関数
void TitleBackground::Draw()
{
	// 0.0f2つはxy座標のこと
	GameLib::Instance().DrawXY(title_scene::TITLE_BACKGROUND, title_scene::BACKGROUND, 0.0f, 0.0f);
}
