/**
* @file		TitleLogo.cpp
* @brief	TitleLogoクラス実装
* @author	haga
*/
#include "GameLib/GameLib.h"
#include "../Scene/TitleScene.h"
#include "TitleLogo.h"

/**@todo 現在数値は仮置きのもの*/
TitleLogo::TitleLogo()
	: m_PosX(800.0f)
	, m_PosY(280.0f)
{
	float logoWidth  = 1024.f;
	float logoHeight = 512.f;
	GameLib::Instance().CreateVtx(TitleScene::LOGO_VTX, logoWidth, logoHeight);
}

TitleLogo::~TitleLogo()
{
	//　リソース解放はTitleSceneのデストラクタで一括で行う
}

void TitleLogo::Control()
{
	/**@todo	光るエフェクトなどが決まっていないので、決まり次第実装*/
}

void TitleLogo::Draw()
{
	GameLib::Instance().DrawXYCenterPos(TitleScene::LOGO_TEX, TitleScene::LOGO_VTX, m_PosX, m_PosY);
}
