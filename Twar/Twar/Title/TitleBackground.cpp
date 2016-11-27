﻿/**
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
	GameLib::Instance().CreateVtx(title_enum::BACKGROUND_VTX, cliantWidthSize, cliantHeightSize);
}

TitleBackground::~TitleBackground()
{
	//　リソース解放はTitleSceneのデストラクタで一括で行う
}

// 描画関数
void TitleBackground::Draw()
{
	// 0.0f2つはxy座標のこと
	GameLib::Instance().DrawXY(title_enum::BACKGROUND_TEX, title_enum::BACKGROUND_VTX, 0.0f, 0.0f);
}
